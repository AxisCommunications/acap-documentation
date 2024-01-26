/*
 * This is an example application that demonstrates how to use the axptz library.
 * It does not contain examples that cover all of the axptz library functions,
 * the purpose of this example application is to give the end user some basic
 * knowledge on how to use the library.
 */

#include <stdio.h>
#include <unistd.h>
#include <syslog.h>
#include <fixmath.h>
#include <axsdk/axptz.h>

#define APP_NAME "axptzApp"

/* This activates logging to syslog */
#define WRITE_TO_SYS_LOG

#ifdef WRITE_TO_SYS_LOG
#define LOGINFO(fmt, args...) \
  do { \
    syslog(LOG_INFO, fmt, ## args); \
    printf(fmt, ## args); \
    printf("\n"); \
  } while(0)
#else
#define LOGINFO(fmt, args...)
#endif

/* The number of fractional bits used in fix-point variables */
#define FIXMATH_FRAC_BITS 16

/* global variables */
static AXPTZControlQueueGroup *ax_ptz_control_queue_group = NULL;
static gint video_channel = 1;
static gboolean camera_is_moving = FALSE;
static GList *capabilities = NULL;
static AXPTZStatus *unitless_status = NULL;
static AXPTZLimits *unitless_limits = NULL;
static AXPTZLimits *unit_limits = NULL;

static fixed_t fx_zero = fx_itox(0, FIXMATH_FRAC_BITS);
static fixed_t fx_two = fx_ftox(2.0f, FIXMATH_FRAC_BITS);
static fixed_t fx_four = fx_ftox(4.0f, FIXMATH_FRAC_BITS);

static fixed_t unitless_low_pan = fx_itox(0, FIXMATH_FRAC_BITS);
static fixed_t unitless_centre_pan = fx_itox(0, FIXMATH_FRAC_BITS);
static fixed_t unitless_high_pan = fx_itox(0, FIXMATH_FRAC_BITS);
static fixed_t unitless_low_tilt = fx_itox(0, FIXMATH_FRAC_BITS);
static fixed_t unitless_centre_tilt = fx_itox(0, FIXMATH_FRAC_BITS);
static fixed_t unitless_high_tilt = fx_itox(0, FIXMATH_FRAC_BITS);
static fixed_t unitless_centre_zoom = fx_itox(0, FIXMATH_FRAC_BITS);

static fixed_t unit_low_pan = fx_itox(0, FIXMATH_FRAC_BITS);
static fixed_t unit_centre_pan = fx_itox(0, FIXMATH_FRAC_BITS);
static fixed_t unit_high_pan = fx_itox(0, FIXMATH_FRAC_BITS);
static fixed_t unit_low_tilt = fx_itox(0, FIXMATH_FRAC_BITS);
static fixed_t unit_centre_tilt = fx_itox(0, FIXMATH_FRAC_BITS);
static fixed_t unit_high_tilt = fx_itox(0, FIXMATH_FRAC_BITS);
static fixed_t unit_centre_zoom = fx_itox(0, FIXMATH_FRAC_BITS);

static fixed_t unitless_pos_speed = fx_ftox(0.25f, FIXMATH_FRAC_BITS);

static fixed_t unitless_chosen_pan_position = fx_itox(0, FIXMATH_FRAC_BITS);

/*
 * Get the camera's supported PTZ move capabilities
 */
static gboolean get_ptz_move_capabilities(void)
{
  GError *local_error = NULL;

  if (!(capabilities =
       ax_ptz_movement_handler_get_move_capabilities(video_channel,
                                                     &local_error))) {
    g_error_free(local_error);
    return FALSE;
  }

  return TRUE;
}

/*
 * Check if a capability is supported
 */
static gboolean is_capability_supported(const char *capability)
{
  gboolean is_supported = FALSE;
  GList *it = NULL;

  if (capabilities) {
    for (it = g_list_first(capabilities); it != NULL; it = g_list_next(it)) {
      if (!(g_strcmp0((gchar *) it->data, capability))) {
        is_supported = TRUE;
        break;
      }
    }
  }

  return is_supported;
}

/*
 * Wait for the camera to reach it's position
 */
static gboolean wait_for_camera_movement_to_finish(void)
{
  gboolean is_moving = TRUE;
  gushort timer = 0;
  gushort timeout = 10;
  gushort sleep_time = 1;
  GError *local_error = NULL;

  /* Check if camera is moving */
  if (!(ax_ptz_movement_handler_is_ptz_moving
       (video_channel, &is_moving, &local_error))) {
    g_error_free(local_error);
    return FALSE;
  }

  /* Wait until camera is in position or until we get a timeout */
  while (is_moving && (timer < timeout)) {
    if (!(ax_ptz_movement_handler_is_ptz_moving
         (video_channel, &is_moving, &local_error))) {
      g_error_free(local_error);
      return FALSE;
    }

    sleep(sleep_time);
    timer++;
  }

  if (is_moving) {
    /* Camera is still moving */
    return FALSE;
  } else {
    /* Camera is in position */
    return TRUE;
  }
}

/*
 * Perform camera movement to absolute position
 */
static gboolean
move_to_absolute_position(fixed_t pan_value,
                          fixed_t tilt_value,
                          AXPTZMovementPanTiltSpace pan_tilt_space,
                          gfloat speed,
                          AXPTZMovementPanTiltSpeedSpace pan_tilt_speed_space,
                          fixed_t zoom_value, AXPTZMovementZoomSpace zoom_space)
{
  AXPTZAbsoluteMovement *abs_movement = NULL;
  GError *local_error = NULL;

  /* Set the unit spaces for an absolute movement */
  if ((ax_ptz_movement_handler_set_absolute_spaces
       (pan_tilt_space, pan_tilt_speed_space, zoom_space, &local_error))) {
    /* Create an absolute movement structure */
    if ((abs_movement = ax_ptz_absolute_movement_create(&local_error))) {

      /* Set the pan, tilt and zoom values for the absolute movement */
      if (!(ax_ptz_absolute_movement_set_pan_tilt_zoom(abs_movement,
                                                       pan_value,
                                                       tilt_value,
                                                       fx_ftox(speed,
                                                               FIXMATH_FRAC_BITS),
                                                       zoom_value,
                                                       AX_PTZ_MOVEMENT_NO_VALUE,
                                                       &local_error))) {
        ax_ptz_absolute_movement_destroy(abs_movement, NULL);
        g_error_free(local_error);
        return FALSE;
      }

      /* Perform the absolute movement */
      if (!(ax_ptz_movement_handler_absolute_move(ax_ptz_control_queue_group,
                                                  video_channel,
                                                  abs_movement,
                                                  AX_PTZ_INVOKE_ASYNC, NULL,
                                                  NULL, &local_error))) {
        ax_ptz_absolute_movement_destroy(abs_movement, NULL);
        g_error_free(local_error);
        return FALSE;
      }

      /* Now we don't need the absolute movement structure anymore, destroy it */
      if (!(ax_ptz_absolute_movement_destroy(abs_movement, &local_error))) {
        g_error_free(local_error);
        return FALSE;
      }
    } else {
      g_error_free(local_error);
      return FALSE;
    }
  } else {
    g_error_free(local_error);
    return FALSE;
  }

  return TRUE;
}

/*
 * Perform camera movement to relative position
 */
static gboolean
move_to_relative_position(fixed_t pan_value,
                          fixed_t tilt_value,
                          AXPTZMovementPanTiltSpace pan_tilt_space,
                          gfloat speed,
                          AXPTZMovementPanTiltSpeedSpace pan_tilt_speed_space,
                          fixed_t zoom_value, AXPTZMovementZoomSpace zoom_space)
{
  AXPTZRelativeMovement *rel_movement = NULL;
  GError *local_error = NULL;

  /* Set the unit spaces for a relative movement */
  if ((ax_ptz_movement_handler_set_relative_spaces
       (pan_tilt_space, pan_tilt_speed_space, zoom_space, &local_error))) {

    /* Create a relative movement structure */
    if ((rel_movement = ax_ptz_relative_movement_create(&local_error))) {

      /* Set the pan, tilt and zoom values for the relative movement */
      if (!(ax_ptz_relative_movement_set_pan_tilt_zoom(rel_movement,
                                                       pan_value,
                                                       tilt_value,
                                                       fx_ftox(speed, FIXMATH_FRAC_BITS),
                                                       zoom_value,
                                                       AX_PTZ_MOVEMENT_NO_VALUE,
                                                       &local_error))) {
        ax_ptz_relative_movement_destroy(rel_movement, NULL);
        g_error_free(local_error);
        return FALSE;
      }

      /* Perform the relative movement */
      if (!(ax_ptz_movement_handler_relative_move(ax_ptz_control_queue_group,
                                                  video_channel,
                                                  rel_movement,
                                                  AX_PTZ_INVOKE_ASYNC, NULL,
                                                  NULL, &local_error))) {
        ax_ptz_relative_movement_destroy(rel_movement, NULL);
        g_error_free(local_error);
        return FALSE;
      }

      /* Now we don't need the relative movement structure anymore, destroy it */
      if (!(ax_ptz_relative_movement_destroy(rel_movement, &local_error))) {
        g_error_free(local_error);
        return FALSE;
      }
    } else {
      g_error_free(local_error);
      return FALSE;
    }
  } else {
    g_error_free(local_error);
    return FALSE;
  }

  return TRUE;
}

/*
 * Perform continous camera movement
 */
static gboolean
start_continous_movement(fixed_t pan_speed,
                         fixed_t tilt_speed,
                         AXPTZMovementPanTiltSpeedSpace pan_tilt_speed_space,
                         fixed_t zoom_speed, gfloat timeout)
{
  AXPTZContinuousMovement *cont_movement = NULL;
  GError *local_error = NULL;

  /* Set the unit spaces for a continous movement */
  if ((ax_ptz_movement_handler_set_continuous_spaces
       (pan_tilt_speed_space, &local_error))) {

    /* Create a continous movement structure */
    if ((cont_movement = ax_ptz_continuous_movement_create(&local_error))) {

      /* Set the pan, tilt and zoom speeds for the continous movement */
      if (!(ax_ptz_continuous_movement_set_pan_tilt_zoom(cont_movement,
                                                         pan_speed,
                                                         tilt_speed,
                                                         zoom_speed,
                                                         fx_ftox(timeout, FIXMATH_FRAC_BITS),
                                                         &local_error))) {
        ax_ptz_continuous_movement_destroy(cont_movement, NULL);
        g_error_free(local_error);
        return FALSE;
      }

      /* Perform the continous movement */
      if (!(ax_ptz_movement_handler_continuous_start(ax_ptz_control_queue_group,
                                                     video_channel,
                                                     cont_movement,
                                                     AX_PTZ_INVOKE_ASYNC, NULL,
                                                     NULL, &local_error))) {
        ax_ptz_continuous_movement_destroy(cont_movement, NULL);
        g_error_free(local_error);
        return FALSE;
      }

      /* Now we don't need the continous movement structure anymore, destroy it */
      if (!(ax_ptz_continuous_movement_destroy(cont_movement, &local_error))) {
        g_error_free(local_error);
        return FALSE;
      }
    } else {
      g_error_free(local_error);
      return FALSE;
    }
  } else {
    g_error_free(local_error);
    return FALSE;
  }

  return TRUE;
}

/*
 * Stop continous camera movement
 */
static gboolean stop_continous_movement(gboolean stop_pan_tilt,
                                        gboolean stop_zoom)
{
  GError *local_error = NULL;

  /* Stop the continous movement */
  if (!(ax_ptz_movement_handler_continuous_stop(ax_ptz_control_queue_group,
                                                video_channel,
                                                stop_pan_tilt,
                                                stop_zoom, AX_PTZ_INVOKE_ASYNC,
                                                NULL, NULL, &local_error))) {
    g_error_free(local_error);
    return FALSE;
  }

  return TRUE;
}

/*
 * Main
 */
int main(int argc, char **argv)
{
  GList *it = NULL;
  gint preset_number_0 = -1;
  gint preset_number_1 = -1;
  gint queue_pos = -1;
  gint time_to_pos_one = -1;
  gint poll_time = -1;
  GError *local_error = NULL;

#ifdef WRITE_TO_SYS_LOG
  openlog(APP_NAME, LOG_PID | LOG_CONS, LOG_USER);
#endif
  LOGINFO("\'axptz library\' example application started...\n");

  /* Create the axptz library */
  if (!(ax_ptz_create(&local_error))) {
    goto failure;
  }

  /* Get the application group from the PTZ control queue */
  if (!(ax_ptz_control_queue_group =
       ax_ptz_control_queue_get_app_group_instance(&local_error))) {
    goto failure;
  }

  /* Get the supported capabilities */
  if (!(get_ptz_move_capabilities())) {
    goto failure;
  }

  /* Get the current status (e.g. the current pan/tilt/zoom value/position) */
  if (!(ax_ptz_movement_handler_get_ptz_status(video_channel,
                                               AX_PTZ_MOVEMENT_PAN_TILT_UNITLESS,
                                               AX_PTZ_MOVEMENT_ZOOM_UNITLESS,
                                               &unitless_status,
                                               &local_error))) {
    goto failure;
  }

  LOGINFO("Now we got the current PTZ status.\n");

  /* Get the pan, tilt and zoom limits for the unitless space */
  if ((ax_ptz_movement_handler_get_ptz_limits(video_channel,
                                              AX_PTZ_MOVEMENT_PAN_TILT_UNITLESS,
                                              AX_PTZ_MOVEMENT_ZOOM_UNITLESS,
                                              &unitless_limits,
                                              &local_error))) {
    unitless_low_pan =
        fx_addx(fx_divx
                (fx_subx
                 (unitless_limits->max_pan_value,
                  unitless_limits->min_pan_value), fx_four, FIXMATH_FRAC_BITS),
                unitless_limits->min_pan_value);
    unitless_centre_pan =
        fx_addx(fx_divx
                (fx_subx
                 (unitless_limits->max_pan_value,
                  unitless_limits->min_pan_value), fx_two, FIXMATH_FRAC_BITS),
                unitless_limits->min_pan_value);
    unitless_high_pan =
        fx_subx(unitless_limits->max_pan_value,
                fx_divx(fx_subx
                        (unitless_limits->max_pan_value,
                         unitless_limits->min_pan_value), fx_four,
                        FIXMATH_FRAC_BITS));
    unitless_low_tilt =
        fx_addx(fx_divx
                (fx_subx
                 (unitless_limits->max_tilt_value,
                  unitless_limits->min_tilt_value), fx_four, FIXMATH_FRAC_BITS),
                unitless_limits->min_tilt_value);
    unitless_centre_tilt =
        fx_addx(fx_divx
                (fx_subx
                 (unitless_limits->max_tilt_value,
                  unitless_limits->min_tilt_value), fx_two, FIXMATH_FRAC_BITS),
                unitless_limits->min_tilt_value);
    unitless_high_tilt =
        fx_subx(unitless_limits->max_tilt_value,
                fx_divx(fx_subx
                        (unitless_limits->max_tilt_value,
                         unitless_limits->min_tilt_value), fx_two,
                        FIXMATH_FRAC_BITS));
    unitless_centre_zoom =
        fx_addx(fx_divx
                (fx_subx
                 (unitless_limits->max_zoom_value,
                  unitless_limits->min_zoom_value), fx_two, FIXMATH_FRAC_BITS),
                unitless_limits->min_zoom_value);
  } else {
    goto failure;
  }

  /* Get the pan, tilt and zoom limits for the unit (degrees) space */
  if ((ax_ptz_movement_handler_get_ptz_limits(video_channel,
                                              AX_PTZ_MOVEMENT_PAN_TILT_DEGREE,
                                              AX_PTZ_MOVEMENT_ZOOM_UNITLESS,
                                              &unit_limits, &local_error))) {
    unit_low_pan =
        fx_addx(fx_divx
                (fx_subx
                 (unit_limits->max_pan_value, unit_limits->min_pan_value),
                 fx_four, FIXMATH_FRAC_BITS), unit_limits->min_pan_value);
    unit_centre_pan =
        fx_addx(fx_divx
                (fx_subx
                 (unit_limits->max_pan_value, unit_limits->min_pan_value),
                 fx_two, FIXMATH_FRAC_BITS), unit_limits->min_pan_value);
    unit_high_pan =
        fx_subx(unit_limits->max_pan_value,
                fx_divx(fx_subx
                        (unit_limits->max_pan_value,
                         unit_limits->min_pan_value), fx_four,
                        FIXMATH_FRAC_BITS));
    unit_low_tilt =
        fx_addx(fx_divx
                (fx_subx
                 (unit_limits->max_tilt_value, unit_limits->min_tilt_value),
                 fx_four, FIXMATH_FRAC_BITS), unit_limits->min_tilt_value);
    unit_centre_tilt =
        fx_addx(fx_divx
                (fx_subx
                 (unit_limits->max_tilt_value, unit_limits->min_tilt_value),
                 fx_two, FIXMATH_FRAC_BITS), unit_limits->min_tilt_value);
    unit_high_tilt =
        fx_subx(unit_limits->max_tilt_value,
                fx_divx(fx_subx
                        (unit_limits->max_tilt_value,
                         unit_limits->min_tilt_value), fx_four,
                        FIXMATH_FRAC_BITS));
    unit_centre_zoom =
        fx_addx(fx_divx
                (fx_subx
                 (unit_limits->max_zoom_value, unit_limits->min_zoom_value),
                 fx_two, FIXMATH_FRAC_BITS), unit_limits->min_zoom_value);
  } else {
    goto failure;
  }

  LOGINFO("Now we got the current PTZ limits.\n");

  /* Verify that the 'absolute pan movement' capability is supported */
  if ((is_capability_supported("AX_PTZ_MOVE_ABS_PAN"))) {
    if (!(move_to_absolute_position(unitless_centre_pan, AX_PTZ_MOVEMENT_NO_VALUE,
                                    AX_PTZ_MOVEMENT_PAN_TILT_UNITLESS, 0.5f,
                                    AX_PTZ_MOVEMENT_PAN_TILT_SPEED_UNITLESS,
                                    unitless_status->zoom_value,
                                    AX_PTZ_MOVEMENT_ZOOM_UNITLESS))) {
      goto failure;
    }

    LOGINFO("Absolute movement to centre pan position.\n");

    /* We wait for the camera ptz movement to finish */
    if (!(wait_for_camera_movement_to_finish())) {
      goto failure;
    }
  }

  /* Verify that the 'relative pan movement' capability is supported */
  if ((is_capability_supported("AX_PTZ_MOVE_REL_PAN"))) {

    /* Choose a pan position between the current
     * position (centre) and the high pan position
     */
    unitless_chosen_pan_position =
        fx_divx((fx_subx(unitless_high_pan, unitless_centre_pan)), fx_two,
                FIXMATH_FRAC_BITS);

    if (!(move_to_relative_position(unitless_chosen_pan_position,
                                    AX_PTZ_MOVEMENT_NO_VALUE,
                                    AX_PTZ_MOVEMENT_PAN_TILT_UNITLESS,
                                    0.5f,
                                    AX_PTZ_MOVEMENT_PAN_TILT_SPEED_UNITLESS,
                                    unitless_status->zoom_value,
                                    AX_PTZ_MOVEMENT_ZOOM_UNITLESS))) {
      goto failure;
    }

    LOGINFO("Relative movement to chosen pan position.\n");

    /* We wait for the camera ptz movement to finish */
    if (!(wait_for_camera_movement_to_finish())) {
      goto failure;
    }
  }

  /* Verify that the 'absolute tilt movement' capability is supported */
  if ((is_capability_supported("AX_PTZ_MOVE_ABS_TILT"))) {
    if (!(move_to_absolute_position(AX_PTZ_MOVEMENT_NO_VALUE,
                                    unit_centre_tilt,
                                    AX_PTZ_MOVEMENT_PAN_TILT_DEGREE,
                                    0.5f,
                                    AX_PTZ_MOVEMENT_PAN_TILT_SPEED_UNITLESS,
                                    unitless_status->zoom_value,
                                    AX_PTZ_MOVEMENT_ZOOM_UNITLESS))) {
      goto failure;
    }

    LOGINFO("Absolute movement to centre tilt position.\n");

    /* We wait for the camera ptz movement to finish */
    if (!(wait_for_camera_movement_to_finish())) {
      goto failure;
    }
  }

  /* Verify that the 'absolute zoom movement' capability is supported */
  if ((is_capability_supported("AX_PTZ_MOVE_ABS_ZOOM"))) {
    if (!(move_to_absolute_position(AX_PTZ_MOVEMENT_NO_VALUE,
                                    AX_PTZ_MOVEMENT_NO_VALUE,
                                    AX_PTZ_MOVEMENT_PAN_TILT_UNITLESS,
                                    0.5f,
                                    AX_PTZ_MOVEMENT_PAN_TILT_SPEED_UNITLESS,
                                    unitless_limits->max_zoom_value,
                                    AX_PTZ_MOVEMENT_ZOOM_UNITLESS))) {
      goto failure;
    }

    LOGINFO("Absolute movement to maximum zoom position.\n");

    /* We wait for the camera ptz movement to finish */
    if (!(wait_for_camera_movement_to_finish())) {
      goto failure;
    }

    if (!(move_to_absolute_position(AX_PTZ_MOVEMENT_NO_VALUE,
                                    AX_PTZ_MOVEMENT_NO_VALUE,
                                    AX_PTZ_MOVEMENT_PAN_TILT_UNITLESS,
                                    0.5f,
                                    AX_PTZ_MOVEMENT_PAN_TILT_SPEED_UNITLESS,
                                    unitless_limits->min_zoom_value,
                                    AX_PTZ_MOVEMENT_ZOOM_UNITLESS))) {
      goto failure;
    }

    LOGINFO("Absolute movement to minimum zoom position.\n");

    /* We wait for the camera ptz movement to finish */
    if (!(wait_for_camera_movement_to_finish())) {
      goto failure;
    }
  }

  /* Verify that the 'continous pan movement' capability is supported */
  if ((is_capability_supported("AX_PTZ_MOVE_CONT_PAN"))) {
    if (!(start_continous_movement(unitless_pos_speed,
                                   fx_zero,
                                   AX_PTZ_MOVEMENT_PAN_TILT_SPEED_UNITLESS,
                                   fx_zero, 1000.0f))) {
      goto failure;
    }

    LOGINFO("Continous pan movement started.\n");

    /* Let the camera move for some seconds */
    sleep(5);

    /* Check if camera is moving */
    if (!(ax_ptz_movement_handler_is_ptz_moving
         (video_channel, &camera_is_moving, &local_error))) {
      goto failure;
    } else {
      if (camera_is_moving) {
        LOGINFO("Continous pan: Camera is moving.\n");
      } else {
        LOGINFO("Continous pan: Camera is not moving.\n");
      }
    }

    /* Stop the continous pan movement */
    if (!(stop_continous_movement(TRUE, FALSE))) {
      goto failure;
    }

    /* Give the camera some time to stop moving */
    sleep(1);

    /* Check if camera is moving */
    if (!(ax_ptz_movement_handler_is_ptz_moving
         (video_channel, &camera_is_moving, &local_error))) {
      goto failure;
    } else {
      if (camera_is_moving) {
        LOGINFO("Continous pan: Camera is moving.\n");
      } else {
        LOGINFO("Continous pan: Camera is not moving.\n");
      }
    }

    LOGINFO("Continous pan movement ended.\n");
  }

  /* Create PTZ preset 0 */
  if (!(ax_ptz_preset_handler_create_preset_name(ax_ptz_control_queue_group,
                                                 video_channel, "Max_values",
                                                 &preset_number_0,
                                                 &local_error))) {
    goto failure;
  }

  LOGINFO("Create preset %d\n", preset_number_0);

  /* Verify that the 'absolute pan', 'absolute tilt' and 'absolute zoom'
   * movements are supported */
  if ((is_capability_supported("AX_PTZ_MOVE_ABS_PAN") &&
       is_capability_supported("AX_PTZ_MOVE_ABS_TILT")
       && is_capability_supported("AX_PTZ_MOVE_ABS_ZOOM"))) {

    /* Perform unitless absolute movement to the maximum pan, tilt and zoom
     * positions */
    if (!(move_to_absolute_position(unitless_limits->max_pan_value,
                                    unitless_limits->max_tilt_value,
                                    AX_PTZ_MOVEMENT_PAN_TILT_UNITLESS,
                                    0.5f,
                                    AX_PTZ_MOVEMENT_PAN_TILT_SPEED_UNITLESS,
                                    unitless_limits->max_zoom_value,
                                    AX_PTZ_MOVEMENT_ZOOM_UNITLESS))) {
      goto failure;
    }

    /* We wait for the camera ptz movement to finish */
    if (!(wait_for_camera_movement_to_finish())) {
      goto failure;
    }
  }

  /* Set PTZ preset 0 to the current camera position */
  if (!(ax_ptz_preset_handler_set_preset_number(ax_ptz_control_queue_group,
                                                video_channel, preset_number_0,
                                                FALSE, &local_error))) {
    goto failure;
  }
  LOGINFO("Set preset %d\n", preset_number_0);

  /* Create PTZ preset 1 */
  if (!(ax_ptz_preset_handler_create_preset_name(ax_ptz_control_queue_group,
                                                 video_channel, "Centre_values",
                                                 &preset_number_1,
                                                 &local_error))) {
    goto failure;
  }

  LOGINFO("Create preset %d\n", preset_number_1);

  /* Verify that the 'absolute pan', 'absolute tilt' and 'absolute zoom'
   * movements are supported */
  if ((is_capability_supported("AX_PTZ_MOVE_ABS_PAN") &&
       is_capability_supported("AX_PTZ_MOVE_ABS_TILT")
       && is_capability_supported("AX_PTZ_MOVE_ABS_ZOOM"))) {

    /* Perform unitless absolute movement to the centre pan, tilt and zoom
     * positions */
    if (!(move_to_absolute_position(unitless_centre_pan,
                                    unitless_centre_tilt,
                                    AX_PTZ_MOVEMENT_PAN_TILT_UNITLESS,
                                    0.5f,
                                    AX_PTZ_MOVEMENT_PAN_TILT_SPEED_UNITLESS,
                                    unitless_centre_zoom,
                                    AX_PTZ_MOVEMENT_ZOOM_UNITLESS))) {
      goto failure;
    }

    /* We wait for the camera ptz movement to finish */
    if (!(wait_for_camera_movement_to_finish())) {
      goto failure;
    }
  }

  /* Set PTZ preset 1 to the current camera position */
  if (!(ax_ptz_preset_handler_set_preset_number(ax_ptz_control_queue_group,
                                                video_channel, preset_number_1,
                                                FALSE, &local_error))) {
    goto failure;
  }

  LOGINFO("Set preset %d\n", preset_number_1);

  /* Goto preset 0 */
  if (!(ax_ptz_preset_handler_goto_preset_number(ax_ptz_control_queue_group,
                                                 video_channel,
                                                 preset_number_0,
                                                 fx_ftox(1.0f,
                                                         FIXMATH_FRAC_BITS),
                                                 AX_PTZ_PRESET_MOVEMENT_UNITLESS,
                                                 AX_PTZ_INVOKE_ASYNC, NULL,
                                                 NULL, &local_error))) {
    goto failure;
  }

  LOGINFO("Goto preset %d\n", preset_number_0);

  /* We wait for the camera ptz movement to finish */
  if (!(wait_for_camera_movement_to_finish())) {
    goto failure;
  }

  sleep(2);

  /* Goto preset 1 */
  if (!(ax_ptz_preset_handler_goto_preset_number(ax_ptz_control_queue_group,
                                                 video_channel,
                                                 preset_number_1,
                                                 fx_ftox(1.0f,
                                                         FIXMATH_FRAC_BITS),
                                                 AX_PTZ_PRESET_MOVEMENT_UNITLESS,
                                                 AX_PTZ_INVOKE_ASYNC, NULL,
                                                 NULL, &local_error))) {
    goto failure;
  }

  LOGINFO("Goto preset %d\n", preset_number_1);

  /* We wait for the camera ptz movement to finish */
  if (!(wait_for_camera_movement_to_finish())) {
    goto failure;
  }

  /* Remove preset 0 */
  if (!(ax_ptz_preset_handler_remove_preset_number(ax_ptz_control_queue_group,
                                                   video_channel,
                                                   preset_number_0,
                                                   &local_error))) {
    goto failure;
  }

  LOGINFO("Remove preset %d\n", preset_number_0);

  /* Remove preset 1 */
  if (!(ax_ptz_preset_handler_remove_preset_number(ax_ptz_control_queue_group,
                                                   video_channel,
                                                   preset_number_1,
                                                   &local_error))) {
    goto failure;
  }

  LOGINFO("Remove preset %d\n", preset_number_1);

  /* Get the PTZ control queue status for the application */
  if (!(ax_ptz_control_queue_request(ax_ptz_control_queue_group,
                                     video_channel,
                                     AX_PTZ_CONTROL_QUEUE_QUERY_STATUS,
                                     &queue_pos, &time_to_pos_one, &poll_time,
                                     &local_error))) {
    goto failure;
  }

  LOGINFO("Request AX_PTZ_CONTROL_QUEUE_QUERY_STATUS:\n");
  LOGINFO("queue_pos = %d\n", queue_pos);
  LOGINFO("time_to_pos_one = %d\n", time_to_pos_one);
  LOGINFO("poll_time = %d\n", poll_time);

  /* Request for getting the PTZ control */
  if (!(ax_ptz_control_queue_request(ax_ptz_control_queue_group,
                                     video_channel,
                                     AX_PTZ_CONTROL_QUEUE_GET,
                                     &queue_pos, &time_to_pos_one, &poll_time,
                                     &local_error))) {
    goto failure;
  }

  LOGINFO("Request AX_PTZ_CONTROL_QUEUE_GET:\n");
  LOGINFO("queue_pos = %d\n", queue_pos);
  LOGINFO("time_to_pos_one = %d\n", time_to_pos_one);
  LOGINFO("poll_time = %d\n", poll_time);

  /* Get the PTZ control queue status for the application */
  if (!(ax_ptz_control_queue_request(ax_ptz_control_queue_group,
                                     video_channel,
                                     AX_PTZ_CONTROL_QUEUE_QUERY_STATUS,
                                     &queue_pos, &time_to_pos_one, &poll_time,
                                     &local_error))) {
    goto failure;
  }

  LOGINFO("Request AX_PTZ_CONTROL_QUEUE_QUERY_STATUS:\n");
  LOGINFO("queue_pos = %d\n", queue_pos);
  LOGINFO("time_to_pos_one = %d\n", time_to_pos_one);
  LOGINFO("poll_time = %d\n", poll_time);

  /* Request for dropping the PTZ control */
  if (!(ax_ptz_control_queue_request(ax_ptz_control_queue_group,
                                     video_channel,
                                     AX_PTZ_CONTROL_QUEUE_DROP,
                                     &queue_pos, &time_to_pos_one, &poll_time,
                                     &local_error))) {
    goto failure;
  }

  LOGINFO("Request AX_PTZ_CONTROL_QUEUE_DROP:\n");
  LOGINFO("queue_pos = %d\n", queue_pos);
  LOGINFO("time_to_pos_one = %d\n", time_to_pos_one);
  LOGINFO("poll_time = %d\n", poll_time);

  /* Get the PTZ control queue status for the application */
  if (!(ax_ptz_control_queue_request(ax_ptz_control_queue_group,
                                     video_channel,
                                     AX_PTZ_CONTROL_QUEUE_QUERY_STATUS,
                                     &queue_pos, &time_to_pos_one, &poll_time,
                                     &local_error))) {
    goto failure;
  }

  LOGINFO("Request AX_PTZ_CONTROL_QUEUE_QUERY_STATUS:\n");
  LOGINFO("queue_pos = %d\n", queue_pos);
  LOGINFO("time_to_pos_one = %d\n", time_to_pos_one);
  LOGINFO("poll_time = %d\n", poll_time);

  /* Now we don't need the axptz library anymore, destroy it */
  if (!(ax_ptz_destroy(&local_error))) {
    goto failure;
  }

  LOGINFO("%s finished successfully...\n", APP_NAME);

  /* Perform cleanup */

  if (local_error) {
    g_error_free(local_error);
    local_error = NULL;
  }

  if (capabilities) {
    for (it = g_list_first(capabilities); it != NULL; it = g_list_next(it)) {
      g_free((gchar *) it->data);
    }
  }

  g_list_free(capabilities);
  capabilities = NULL;
  g_free(unitless_status);
  unitless_status = NULL;
  g_free(unitless_limits);
  unitless_limits = NULL;
  g_free(unit_limits);
  unit_limits = NULL;

  exit(EXIT_SUCCESS);

/* We will end up here if something went wrong */
 failure:

  if (local_error && local_error->message) {
    LOGINFO("ERROR: %s ended with errors:\n", APP_NAME);
    LOGINFO("%s\n", local_error->message);
  }

  if (local_error) {
    g_error_free(local_error);
    local_error = NULL;
  }

  /* Now we don't need the axptz library anymore, destroy it */
  ax_ptz_destroy(&local_error);

  /* Perform cleanup */

  if (local_error) {
    g_error_free(local_error);
    local_error = NULL;
  }

  if (capabilities) {
    for (it = g_list_first(capabilities); it != NULL; it = g_list_next(it)) {
      g_free((gchar *) it->data);
    }
  }

  g_list_free(capabilities);
  capabilities = NULL;
  g_free(unitless_status);
  unitless_status = NULL;
  g_free(unitless_limits);
  unitless_limits = NULL;
  g_free(unit_limits);
  unit_limits = NULL;

#ifdef WRITE_TO_SYS_LOG
  closelog();
#endif

  exit(EXIT_FAILURE);
}
