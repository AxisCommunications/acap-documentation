#include <axsdk/axaudio.h>
#include <syslog.h>
#include <glib/gstdio.h>
#include <gio/gio.h>
#include <math.h>

#define APP_NAME "audioApp"


static GMainLoop *loop = NULL;


typedef struct _ExampleData {
  AXAudioStream *stream;
  GFileOutputStream *output_stream;
  guint totalbytes;
  guint frames_received;
  GQueue *frame_queue;
  GMutex lock;
  guint64 timestamp;
} ExampleData;

/* Signals handling */
static void
handle_sigterm(int signo)
{
  g_main_loop_quit(loop);
}

static void
init_signals(void)
{
  struct sigaction sa;

  sa.sa_flags = 0;

  sigemptyset(&sa.sa_mask);
  sa.sa_handler = handle_sigterm;
  sigaction(SIGTERM, &sa, NULL);
  sigaction(SIGINT, &sa, NULL);
}

/* This function will get all existing frames in the queue and write to file */
static gboolean
frame_analyzer(gpointer data)
{
  ExampleData *example_data = data;
  AXAudioFrame *audio_frame = NULL;

  do {
  g_mutex_lock(&example_data->lock);
  audio_frame = g_queue_pop_head(example_data->frame_queue);
  g_mutex_unlock(&example_data->lock);

    if (audio_frame != NULL) {
      example_data->timestamp = ax_audio_frame_get_timestamp(audio_frame);
      example_data->totalbytes += ax_audio_frame_get_size(audio_frame);

      /* write frame to file */
      g_output_stream_write_all((GOutputStream*) example_data->output_stream,
                                ax_audio_frame_get_data(audio_frame),
                                ax_audio_frame_get_size(audio_frame), NULL,
                                NULL, NULL);

      ax_audio_frame_free(audio_frame);
    }
  } while (audio_frame);

  return TRUE;
}

/* This function is run in an separate thread that will get audio frames and
 * put them into a queue */
static gpointer
frame_retriever(gpointer data)
{
  ExampleData *example_data = data;
  AXAudioFrame * audio_frame = NULL;
  GError *error = NULL;

  while (TRUE) {
    example_data->frames_received++;

    /* read numaudio_frames frames of audio data */
    audio_frame = ax_audio_stream_get_frame(example_data->stream, &error);

    if (!audio_frame) {
      /* nothing to read, this is an error */
      syslog(LOG_WARNING,
              "Failed to get audio frame got error code: %d and error message: %s",
              error->code, error->message);
      g_error_free(error);
      return NULL;
    } else {
      /* add frame to queue */
      g_mutex_lock(&example_data->lock);
      g_queue_push_tail(example_data->frame_queue, audio_frame);
      g_mutex_unlock(&example_data->lock);
    }
  }
}


static AXAudioFrame *
generate_sine(gint length, gint frequency, guint sound_level)
{
  guint frame_rate = 16000;
  guint sample_per_sin =  frame_rate / frequency;
  AXAudioFrame *frame = ax_audio_frame_new();
  gint16 *data = g_malloc0(sizeof(gint16) * frame_rate * length);
  gint i = 0;

  for (;i < (frame_rate * length); i++) {
    data[i] = sin((2 * G_PI / ((sample_per_sin)) * i)) * sound_level;
  }
  ax_audio_frame_set_data(frame, (gpointer)data, sizeof(gint16)* frame_rate * length, (GFreeFunc)&g_free, NULL);

  return frame;
}

gint
main(gint argc, gchar *argv[])
{
  GError *error = NULL;
  AXAudioStream * stream = NULL;
  ExampleData *example_data = NULL;
  GFile *file = NULL;
  GFileOutputStream *output_stream = NULL;
  guint analyser_source_id;
  GThread *frame_th = NULL;
  AXAudioFrame *frame = NULL;
  AXAudioOutput *output = NULL;

#if !GLIB_CHECK_VERSION(2,36,0)
  g_type_init();
#endif
  init_signals();
  loop = g_main_loop_new(NULL, FALSE);

  openlog(APP_NAME, LOG_PID, LOG_LOCAL4);

  syslog(LOG_INFO, "Starting %s", APP_NAME);

  /* play a generated tone of 400 Hz for 2 seconds */
  frame = generate_sine(2, 400, 15000);

  output = ax_audio_open_output_pcm_16(-1, 16000, AX_AUDIO_CHANNEL_MONO, &error);
  if (output == NULL) {
    syslog(LOG_WARNING, "Failed to open playback, code: %d and error message: %s",
           error->code, error->message);
    goto error_out;
  }

  if (!ax_audio_output_play_pcm_16(output, frame, &error)) {
    syslog(LOG_WARNING, "Failed to play, code: %d and error message: %s",
            error->code, error->message);
    goto error_out;
  }

  if (!ax_audio_output_close_pcm_16(output, &error)) {
    syslog(LOG_WARNING, "Failed to close playback, code: %d and error message: %s",
            error->code, error->message);
    goto error_out;
  }

  /* open up a raw audio stream */
  stream = ax_audio_open_pcm_16_stream(1, 16000, AX_AUDIO_CHANNEL_MONO, &error);
  if (stream == NULL) {
    syslog(LOG_WARNING, "Failed with error code: %d and error message: %s",
            error->code, error->message);
    goto error_out;
  }

  /* setting up for saving stream to file */
  file = g_file_new_for_path("/tmp/raw_audio.raw");
  output_stream = g_file_replace(file, NULL, FALSE, G_FILE_CREATE_NONE, NULL,
                                 NULL);

  syslog(LOG_INFO,
          "RAW audio stream with bit depth: %d and samplerate: %d is setup",
          ax_audio_stream_get_bit_depth(stream),
          ax_audio_stream_get_samplerate(stream));

  /* initialize data structure */
  example_data = g_malloc(sizeof *example_data);
  example_data->stream = stream;
  example_data->output_stream = output_stream;
  example_data->frames_received = 0;
  example_data->totalbytes = 0;
  example_data->frame_queue = g_queue_new();
  g_mutex_init(&example_data->lock);

  /* start a timeout source that will analyze audio frames each 500 ms */
  analyser_source_id = g_timeout_add(500, frame_analyzer, example_data);

  /* start a threads that retrieves audio frames */
  frame_th = g_thread_new("frame retriver", frame_retriever, example_data);

  /* start the main loop */
  g_main_loop_run(loop);

  syslog(LOG_INFO,
         "Totally %d bytes of audio data was received by %s. The timestamp "
         "of the latest retrived frame was: %" G_GUINT64_FORMAT "\n",
         example_data->totalbytes, APP_NAME, example_data->timestamp);


  /* close analyzer source */
  g_source_remove(analyser_source_id);

  /* unref the main loop when the main loop has been quit */
  g_main_loop_unref(loop);

  g_thread_unref(frame_th);

  /* free */
  g_output_stream_close((GOutputStream*) output_stream, NULL, NULL);
  g_object_unref(output_stream);
  g_mutex_clear(&example_data->lock);
  g_queue_free(example_data->frame_queue);
  g_free(example_data);

  error_out:

  if (error != NULL) {
    g_error_free(error);
  }
  if (frame != NULL) {
    ax_audio_frame_free(frame);
  }

  ax_audio_stream_close(stream, NULL);
  syslog(LOG_INFO, "Quitting %s", APP_NAME);

  return 0;
}
