/*
 *   This example application controls a Pelco Spectra Mini PTZ camera
 *   (Pelco-D protocol) using the serial port API, axserialport.
 *
 *   Copyright (C) 2013- Axis Communications AB, LUND, SWEDEN
 */

#include <stdlib.h>
#include <unistd.h>
#include <syslog.h>
#include <glib.h>
#include <axsdk/axserialport.h>

#define APP_NAME "ACAP_Demo_serial"

/*
 * Pelco Spectra Mini configuration
 */
#define PELCO_DEVICE_ADDR 0x01
#define PELCO_DEVICE_BAUDRATE (AX_SERIAL_B2400)
#define PELCO_DEVICE_DATABITS (AX_SERIAL_DATABITS_8)
#define PELCO_DEVICE_STOPBITS (AX_SERIAL_STOPBITS_1)
#define PELCO_DEVICE_PARITY   (AX_SERIAL_PARITY_NONE)

/*
 * Pelco-D protocol types
 */
typedef enum{
 PELCO_SYNC_BYTE=0,
 PELCO_ADDR,
 PELCO_CMD1,
 PELCO_CMD2,
 PELCO_DATA1,
 PELCO_DATA2,
 PELCO_CHECKSUM,
 PELCO_CMD_LENGTH /* keep last */
}PelcoType;

typedef enum{
 CMD1_SENSE=7,
 CMD1_RESERVED1=6,
 CMD1_RESERVED2=5,
 CMD1_AUTOSCAN=4,
 CMD1_CAMERA_ON=3,
 CMD1_IRIS_CLOSE=2,
 CMD1_IRIS_OPEN=1,
 CMD1_FOCUS=0
}PelcoCmd1;

typedef enum{
 CMD2_FOCUS_FAR=7,
 CMD2_ZOOM_WIDE=6,
 CMD2_ZOOM_TELE=5,
 CMD2_DOWN=4,
 CMD2_UP=3,
 CMD2_LEFT=2,
 CMD2_RIGHT=1,
 CMD2_NA=0
}PelcoCmd2;

/*
 * Application specific structure
 */
typedef struct MyConfigAndData{
  AXSerialConfig *config;
  GIOChannel     *channel;
  GTimer         *timer;
  gpointer       data;
} MyConfigAndData;


static GMainLoop *loop = NULL;

/*
 * Function declaration
 */
static void handle_sigterm(int signo);
static void init_signals(void);
static gchar* iostatus2str(GIOStatus status);
static gboolean incoming_data(GIOChannel *channel, GIOCondition cond, gpointer data);
static gboolean send_pelco_cmd(gpointer data);

/*
 * The signal handler(s)
 */
static void
handle_sigterm(int signo)
{
  g_message("%s: Got SIGTERM", APP_NAME);
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

/*
 * This function converts a GIOStatus (enum)
 * to a text string.
 */
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

/*
 * This function handles incomming serial data.
 */
static gboolean
incoming_data(GIOChannel *channel, GIOCondition cond, gpointer data)
{
  MyConfigAndData *conf_data = data;
  GIOChannel*iochannel = conf_data->channel;
  GError *error = NULL;
  GIOStatus ret;
  guint bytes_read;
  gchar timestamp[2];
  gchar str[128];

  /* We have incoming data, read it! */
  ret = g_io_channel_read_chars(iochannel, timestamp, sizeof(timestamp), &bytes_read, &error);
  if (ret == G_IO_STATUS_NORMAL) {
    /* All OK! write the timestamp to stdout and syslog */
    guchar min = timestamp[0];
    guchar sec = timestamp[1];
    g_snprintf(str, 128, "%s() timestamp: %02u:%02u", __FUNCTION__, min, sec);
    g_message("%s", str);
    syslog(LOG_INFO, "%s", str);
  } else {
    g_message("%s: error :", APP_NAME);
    if (error) { /* Report error */
      g_message("%s", error->message);
      syslog(LOG_ERR, "%s", error->message);
      g_error_free(error); /* free error */
    }
  }

  /* Return FALSE if the event source should be removed */
  return TRUE;
}

/*
 * This function calculates the command checksum specified by the
 * Pelco-D protocol. The Checksum is calculated by performing an
 * 8 bit (modulo 256) sum of the payload bytes (bytes 2 through 6)
 * in the message.
 */
static gchar
calc_pelco_checksum(gchar *cmd)
{
  return ((cmd[PELCO_ADDR]  +
           cmd[PELCO_CMD1]  +
           cmd[PELCO_CMD2]  +
           cmd[PELCO_DATA1] +
           cmd[PELCO_DATA2]) % 256);
}

/*
 * This function sends the commands LEFT,UP,RIGHT,DOWN specified
 * by the Pelco-D protocol to a Pelco spectra mini PTZ camera
 * connected to the serial port.
 * The device addres is defined by PELCO_DEVICE_ADDR.
 */
static gboolean
send_pelco_cmd(gpointer data)
{
  MyConfigAndData  *conf_data = data;
  GIOChannel       *iochannel = conf_data->channel;
  GError           *error = NULL;
  GIOStatus        ret;
  guint            bytes_written;
  static guint     cmd_tick = 0;
  gchar            pelco_cmd[PELCO_CMD_LENGTH];

  /* Command Setup */
  pelco_cmd[PELCO_SYNC_BYTE] = 0xff; /* The synchronization byte (Sync Byte) is always 0xFF. */
  pelco_cmd[PELCO_ADDR]      = PELCO_DEVICE_ADDR; /* Device hardcoded address */
  pelco_cmd[PELCO_DATA1]     = 0x3f; /* PAN  SPEED: "high speed" */
  pelco_cmd[PELCO_DATA2]     = 0x3f; /* TILT SPEED: "high speed" */
  pelco_cmd[PELCO_CMD1]      = 0x9f & (1<<CMD1_SENSE | 1<<CMD1_AUTOSCAN | 1<<CMD1_CAMERA_ON) ;

  /*
   * Loop: LEFT(2s) -> UP(2s) -> RIGHT(2s) -> DOWN(2s)
   */
  switch(cmd_tick++ % 4){
    case 0:
     pelco_cmd[PELCO_CMD2]      = 0xfe & 1<<CMD2_LEFT ;
     g_message("Case0 : PAN LEFT");
     break;
    case 1:
     pelco_cmd[PELCO_CMD2]      = 0xfe & 1<<CMD2_UP ;
     g_message("Case1 : TILT UP");
     break;
    case 2:
     pelco_cmd[PELCO_CMD2]      = 0xfe & 1<<CMD2_RIGHT ;
     g_message("Case2 : PAN RIGTH");
     break;
    case 3:
     pelco_cmd[PELCO_CMD2]      = 0xfe & 1<<CMD2_DOWN ;
     g_message("Case3 : TILT DOWN");
     break;
    default:
     break;
  }

  //remove_me: pelco_cmd[PELCO_CHECKSUM]  = ((pelco_cmd[PELCO_ADDR]  + pelco_cmd[PELCO_CMD1]  + pelco_cmd[PELCO_CMD2]  + pelco_cmd[PELCO_DATA1] + pelco_cmd[PELCO_DATA2]) % 256);
  pelco_cmd[PELCO_CHECKSUM]  = calc_pelco_checksum(pelco_cmd);

  ret = g_io_channel_write_chars(iochannel, pelco_cmd, PELCO_CMD_LENGTH, &bytes_written, &error);
  if (ret == G_IO_STATUS_NORMAL) {
    /* Flush the write buffer */
    ret = g_io_channel_flush(iochannel, &error);
    /* Log the return status from g_io_channel_write_chars() */
    g_message("%s() wrote %d/%d bytes, status:'%s'",
      __FUNCTION__, bytes_written, PELCO_CMD_LENGTH, iostatus2str(ret));
  }

  if (error) { /* Report to stderr and syslog */
    g_message("%s", error->message);
    syslog(LOG_ERR, "%s", error->message);
    g_error_free(error); /* free error */
  }

  /* Return FALSE if the event source should be removed */
  return TRUE;
}

/*
 *  our main()
 */
int
main(int argc, char *argv[])
{
  gint  fd     = 0;
  gint  ret    = 0;
  gint  status = EXIT_FAILURE;
  guint port0  = 0;
  AXSerialConfig *config    = NULL;
  GIOChannel     *iochannel = NULL;
  GError         *error     = NULL;
  MyConfigAndData conf_data;

  /* Initialization */
  init_signals();
  loop = g_main_loop_new(NULL, FALSE);

  /* Print some startup messages */
  g_message("%s: Starting!", APP_NAME);
  openlog(APP_NAME, LOG_PID, LOG_LOCAL4);
  syslog(LOG_INFO, "Starting!");

  /* Create a configuration for the first port (port0) */
  config = ax_serial_init(port0, &error);
  if (!config) {
    goto error_out;
  }

  /* Config for Pelco Spectra Mini :
   *
   * Enable Port
   * RS485, 2400 Baud, 8 Databits, 1 Stopbit, No Termination, No Bias
   */
  ax_serial_port_enable(config, AX_SERIAL_ENABLE, NULL);
  ax_serial_set_portmode(config, AX_SERIAL_RS485, NULL);
  ax_serial_set_baudrate(config, AX_SERIAL_B2400, NULL);
  ax_serial_set_databits(config, AX_SERIAL_DATABITS_8, NULL);
  ax_serial_set_stopbits(config, AX_SERIAL_STOPBITS_1, NULL);
  ax_serial_set_termination(config, AX_SERIAL_DISABLE, NULL);
  ax_serial_set_bias(config, AX_SERIAL_DISABLE, NULL);

  /* Syncronize (set) configuration */
  ret = ax_serial_sync_port_settings(config, &error);
  if (!ret) {
    goto error_out;
  }

  /* Get the file descriptor associated with the configured port. */
  fd = ax_serial_get_fd(config, &error);
  if (fd < 0) {
    goto error_out;
  }

  /* Create a GIOChannel from the fd */
  iochannel = g_io_channel_unix_new(fd);
  if (!iochannel) {
    goto error_out;
  }

  /* Set IO Channel encoding to RAW (default is UTF-8) */
  if (G_IO_STATUS_NORMAL != g_io_channel_set_encoding(iochannel, NULL, &error)){
    goto error_out;
  }

  /* Prepare the conf_data structure */
  conf_data.config  = config;
  conf_data.channel = iochannel;
  conf_data.timer   = g_timer_new(); /* Create and start a timer */


  /* Add a watch that waits for incoming data, then calls 'incoming_data()'
   * when the conditions are met.
   */
  g_io_add_watch(iochannel,       /* GIOChannel */
                 G_IO_IN,         /* GIOCondition: On incoming data */
                 incoming_data,   /* The function to be called */
                 &conf_data       /* Data to pass to function */
  );

  /* Periodically call 'send_pelco_cmd()' every 2nd second */
  g_timeout_add(2000, send_pelco_cmd, &conf_data);

  /* start the main loop */
  g_main_loop_run(loop);

  /* unref the main loop when the main loop has been quit */
  g_main_loop_unref(loop);

  status = EXIT_SUCCESS;

error_out:
  if (error) {
    /* Report error */
    g_critical("%s", error->message);
    syslog(LOG_ERR, "%s", error->message);
    /* free error */
    g_error_free(error);
    status = EXIT_FAILURE;
  }

  /* close the iochannels, no flush */
  if (iochannel != NULL) {
    g_io_channel_shutdown(iochannel, FALSE, NULL);
    g_io_channel_unref(iochannel);
  }

  /* clean up and exit */
  ax_serial_cleanup(config);
  syslog(LOG_INFO, "Bye!");
  g_message("%s: bye!", APP_NAME);

  exit(status);
}

/* EOF */
