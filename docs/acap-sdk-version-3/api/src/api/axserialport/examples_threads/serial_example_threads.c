/******************************************************************************
*
* FILE NAME  : serial_example.c
*
* DESCRIPTION: An example application using the serialport API.
*              This example uses gthreads for reading and writing.
*
*              /NOTE/
*              This program requires a serial loopback
*              cable in order to function properly.
*
* Copyright (C) 2012- Axis Communications AB, LUND, SWEDEN
*
******************************************************************************/

/****************** INCLUDE FILES SECTION ************************************/
#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <glib.h>
#include <glib/gprintf.h>

#include <axserialport.h>

#define APP_NAME "SerialExample"

G_LOCK_DEFINE(databuf);
/****************** TYPE DEFINITION SECTION **********************************/
typedef struct MyConfigAndData{
  AXSerialConfig *config;
  GIOChannel     *channel;
  GTimer         *timer;
  GArray         *databuf;
} MyConfigAndData;

/****************** LOCAL VARIABLE DECLARATION SECTION **********************/
static GMainLoop *loop = NULL;

/***************** FUNCTION DECLARATION SECTION ******************************/
static void   handle_sigterm(int signo);
static void   init_signals(void);
static void   read_loop(gpointer data);
static void   write_loop(gpointer data);
static gchar* iostatus2str(GIOStatus status);
static gsize  receive_data(GIOChannel *channel, gchar *data, guint size);
static gsize  send_data(GIOChannel *channel, gchar *data, guint size);

/*********************** FUNCTION DEFINITION *********************************/
static void
handle_sigterm(int signo)
{
  g_message("\n %s: Got SIGTERM\n", APP_NAME);
  g_main_loop_quit(loop);
}

/******************************************************************************/
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

/******************************************************************************/
static gchar* iostatus2str(GIOStatus status)
{
  switch(status) {
    case G_IO_STATUS_ERROR:
      return "G_IO_STATUS_ERROR";
    case G_IO_STATUS_NORMAL:
      return "G_IO_STATUS_NORMAL";
    case G_IO_STATUS_EOF:
      return "G_IO_STATUS_EOF";
    case G_IO_STATUS_AGAIN:
      return "G_IO_STATUS_AGAIN";
    default:
      return "Unknown GIOStatus!";
  }
}

/******************************************************************************/
static void
read_loop(gpointer data)
{
  MyConfigAndData *conf_data = data;
  GIOChannel      *channel   = conf_data->channel;
  GArray          *buf       = conf_data->databuf;
  guint ret;

  while(1) {
	G_LOCK(databuf);
    if(G_IO_IN == g_io_channel_get_buffer_condition(channel)){
      ret = receive_data(channel, buf->data, buf->len);
      syslog(LOG_INFO, " %s: %s: result: %d\n", APP_NAME, __FUNCTION__, ret);
	}
	G_UNLOCK(databuf);
  }
}

/******************************************************************************/
static void
write_loop(gpointer data)
{
  MyConfigAndData *conf_data = data;
  GIOChannel      *channel   = conf_data->channel;
  GArray          *buf       = conf_data->databuf;
  guint ret;

  while(1){
	G_LOCK(databuf);
    if(G_IO_OUT == g_io_channel_get_buffer_condition(channel)){
      ret = send_data(channel, buf->data, buf->len);
      if (ret != buf->len) {
        g_warning("%s: Wrote %d of %d bytes \n", APP_NAME, ret, buf->len);
	  }
    }
	G_UNLOCK(databuf);
  }
}

/******************************************************************************/
static gsize
receive_data(GIOChannel *channel, gchar *data, guint size)
{
  GError    *error      = NULL;
  guint      bytes_read = 0;
  GIOStatus  ret;

  /* Read incoming data */
  ret = g_io_channel_read_chars(channel, data, size, &bytes_read, &error);
  if(ret == G_IO_STATUS_NORMAL) { /* Read successful */
	g_message(" %s: %s() got %d bytes \n", APP_NAME, __FUNCTION__, bytes_read);
	syslog(LOG_INFO, " %s: %s() got %d bytes \n", APP_NAME, __FUNCTION__, bytes_read);
  }
  else { /* Error occured */
    g_message(" %s: error :\n", APP_NAME);
    if(error) { /* Report to stder and syslog */
      g_message(" %s: '%s'\n", APP_NAME, error->message);
      syslog(LOG_ERR, " %s: '%s'\n", APP_NAME, error->message);
      g_error_free(error); /* free error */
    }
  }

  return bytes_read;
}

/******************************************************************************/
static gsize
send_data(GIOChannel *channel, gchar *data, guint size)
{
  GError    *error         = NULL;
  guint      bytes_written = 0;
  GIOStatus  ret;

  ret = g_io_channel_write_chars(channel, data, size, &bytes_written, &error);
  if(ret == G_IO_STATUS_NORMAL){
    /* Flush the write buffer */
    ret = g_io_channel_flush(channel, &error);
  }

  /* Log the return status from g_io_channel_write_chars() */
  g_message(" %s: %s() wrote %d bytes, status:'%s'\n",
    APP_NAME, __FUNCTION__, bytes_written, iostatus2str(ret));

  if(error) { /* Report to stderr and syslog */
    g_message(" %s: '%s'", APP_NAME, error->message);
    syslog(LOG_ERR, " %s: '%s'", APP_NAME, error->message);
    g_error_free(error); /* free error */
  }

  return bytes_written;
}
/******************************************************************************
 *  main()
 ******************************************************************************/
int
main(int argc, char *argv[])
{
  gint  fd     = 0;
  gint  ret    = 0;
  gint  status = EXIT_SUCCESS;
  guint port0  = 0;
  GThread *read_thread      = NULL;
  GThread *write_thread     = NULL;
  AXSerialConfig *config    = NULL;
  GIOChannel     *iochannel = NULL;
  GError         *error     = NULL;
  gchar* readthread = "read";
  gchar* writethread= "write";
  MyConfigAndData conf_data;

  /* Initialization */
  init_signals();
#if !GLIB_CHECK_VERSION(2,36,0)
  g_thread_init(NULL);
#endif

  loop = g_main_loop_new(NULL, FALSE);

  /* Print some startup messages */
  g_message("\n %s: Starting!\n", APP_NAME);
  openlog(APP_NAME, LOG_PID, LOG_LOCAL4);
  syslog(LOG_INFO, "Starting!");

  /* Create a configuration for the first port (port0) */
  config = ax_serial_init(port0, &error);
  if(!config || error) {
    goto error_out;
  }

  /* Config example (product dependent) see product datasheet.
   *
   * Enable Port
   * RS485 4-Wire
   * Baudrate 19200
   * 8 Databits
   * 1 Stopbit
   * No Termination
   * No Bias
   */
  ax_serial_port_enable(config, AX_SERIAL_ENABLE, NULL);
  ax_serial_set_portmode(config, AX_SERIAL_RS485_4, NULL);
  ax_serial_set_baudrate(config, AX_SERIAL_B19200, NULL);
  ax_serial_set_databits(config, AX_SERIAL_DATABITS_8, NULL );
  ax_serial_set_stopbits(config, AX_SERIAL_STOPBITS_1, NULL);
  ax_serial_set_termination(config, AX_SERIAL_DISABLE, NULL);
  ax_serial_set_bias(config, AX_SERIAL_DISABLE, NULL);

  /* Syncronize (set) configuration */
  ret = ax_serial_sync_port_settings(config, &error);
  if(!ret) {
    goto error_out;
  }

  /* Get the file descriptor associated with the configured port. */
  fd = ax_serial_get_fd(config, &error);
  if(fd < 0) {
    goto error_out;
  }

  /* Create a GIOChannel from the fd */
  iochannel = g_io_channel_unix_new(fd);
  if(iochannel == NULL) {
    goto error_out;
  }

  /* Set IO Channel encoding to RAW (default is UTF-8) */
  if(G_IO_STATUS_NORMAL != g_io_channel_set_encoding(iochannel, NULL, &error)){
    goto error_out;
  }

  /* Prepare the MyConfigAndData struct */
  conf_data.config  = config;
  conf_data.channel = iochannel;
  conf_data.timer   = g_timer_new(); /* Create and start a timer */
#if !GLIB_CHECK_VERSION(2,36,0)
    read_thread  = g_thread_create((GThreadFunc) &read_loop, &conf_data, TRUE, &error);
#else
    read_thread  = g_thread_try_new(readthread, (GThreadFunc) &read_loop, &conf_data, &error);
#endif
  if(!read_thread || error){
    goto error_out;
  }
#if !GLIB_CHECK_VERSION(2,36,0)
  write_thread = g_thread_create((GThreadFunc) &write_loop, &conf_data, TRUE, &error);
#else
  write_thread = g_thread_try_new(writethread, (GThreadFunc) &write_loop, &conf_data, &error);
#endif
  if(!write_thread || error){
    goto error_out;
  }

  /* start the main loop */
  g_main_loop_run(loop);

  /* unref the main loop when the main loop has been quit */
  g_main_loop_unref(loop);

  /* Wait until threads finishes */
  g_thread_join(read_thread);
  g_thread_join(write_thread);

error_out:
  if(error) {
    /* Report error */
    g_critical("%s: '%s'", APP_NAME, error->message);
    syslog(LOG_ERR, "%s: '%s'", APP_NAME, error->message);
    /* free error */
    g_error_free(error);
    status = EXIT_FAILURE;
  }

  /* close the iochannels, no flush */
  if(iochannel != NULL) {
    g_io_channel_shutdown(iochannel, FALSE, &error);
    g_io_channel_unref(iochannel);
  }

  /* clean up and exit */
  ax_serial_cleanup(config);
  syslog(LOG_INFO, "Exiting!");
  g_message(" %s: bye!\n", APP_NAME);

  exit(status);
}

/* EOF */

