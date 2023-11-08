#include <glib.h>
#include <glib-object.h>
#include <axsdk/axparameter.h>
#include <glib/gprintf.h>
#include <syslog.h>
#include <signal.h>


#define APP_NAME "parameterApp"


static GMainLoop *loop = NULL;


static void
parameter_callback(const gchar *name, const gchar *value, gpointer data)
{
  syslog(LOG_INFO, "In Parameter callback");
}

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


gint
main(gint argc, gchar *argv[])
{
  AXParameter *parameter = NULL;
  GError *error = NULL;
  gchar *value = NULL;
  GList *list = NULL;
  GList *list_tmp = NULL;


  init_signals();

  openlog(APP_NAME, LOG_PID, LOG_LOCAL4);

  loop = g_main_loop_new(NULL, FALSE);

  syslog(LOG_INFO, "Starting %s", APP_NAME);

  /* New parameter instance is created */
  parameter = ax_parameter_new(APP_NAME, &error);
  if (parameter == NULL) {
    goto error_out;
  }

  /* Add parameter "Parameter" */
  if (!ax_parameter_add(parameter, "Parameter", "param", NULL, &error)) {
    if (error->code == AX_PARAMETER_PARAM_ADDED_ERROR) {
      /* parameter is already added. Nothing to care about */
      g_error_free(error);
      error = NULL;
    } else {
      goto error_out;
    }
  }

  /* Add parameter "ParameterTwo" */
  if (!ax_parameter_add(parameter, "ParameterTwo", "param_two", NULL, &error)) {
    if (error->code == AX_PARAMETER_PARAM_ADDED_ERROR) {
      /* parameter is already added. Nothing to care about */
      g_error_free(error);
      error = NULL;
    } else {
      goto error_out;
    }
  }

  /* Add parameter "ParameterThree" */
  if (!ax_parameter_add(parameter, "ParameterThree", "param_three", NULL,
                        &error)) {
    if (error->code == AX_PARAMETER_PARAM_ADDED_ERROR) {
      /* parameter is already added. Nothing to care about */
      g_error_free(error);
      error = NULL;
    } else {
      goto error_out;
    }
  }

  /* Get the value of the parameter "Parameter" */
  if (!ax_parameter_get(parameter, "Parameter", &value, &error)) {
    goto error_out;
  }
  syslog(LOG_INFO, "The value of \"Parameter\" is \"%s\"", value);

  /* Remove parameter "ParameterThree" */
  if (!ax_parameter_remove(parameter, "ParameterThree", &error)) {
    goto error_out;
  }

  /* Set the value of the parameter "Parameter" to "param_set" */
  if (!ax_parameter_set(parameter, "Parameter", "param_set", TRUE, &error)) {
    goto error_out;
  }

  /* List all parameter belonging to this application */
  list = ax_parameter_list(parameter, &error);
  if (list == NULL) {
    goto error_out;
  }

  list_tmp = list;
  while (list_tmp != NULL) {
    syslog(LOG_INFO, "Parameter in list: \"%s\"", (gchar*)list_tmp->data);
    list_tmp = g_list_next(list_tmp);
  }

  /* free the list and it's members */
  list_tmp = list;
  while (list_tmp != NULL) {
    /* free the string */
    g_free(list_tmp->data);
    list_tmp = g_list_next(list_tmp);
  }
  g_list_free(list);

  /* Register a callback, that will be called each time "Parameter" is changed */
  if (!ax_parameter_register_callback(parameter,
                                      "Parameter",
                                      parameter_callback,
                                      NULL,
                                      &error)) {
    goto error_out;
  }

  /* start the main loop */
  g_main_loop_run(loop);

  /* unref the main loop when the main loop has been quit */
  g_main_loop_unref(loop);

error_out:

  if (error) {
    syslog(LOG_INFO, "Failed %s", error->message);
    g_error_free(error);
  }

  /* clean up */
  g_free(value);
  ax_parameter_free(parameter);

  syslog(LOG_INFO, "Quitting %s", APP_NAME);

  return 0;
}
