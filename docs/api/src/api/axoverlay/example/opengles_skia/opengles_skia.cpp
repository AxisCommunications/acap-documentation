/*
 * Copyright (C) 2022, Axis Communications AB, LUND, SWEDEN
 * Author: Mikael Murstam
 */

#include <axoverlay.h>
#include <chrono>
#include <glib-unix.h>
#include <signal.h>
#include <stdexcept>
#include <stdio.h>
#include <vector>

#include <ft2build.h>
#include FT_FREETYPE_H
#include <harfbuzz/hb.h>
#include <harfbuzz/hb-ft.h>
#include <raqm.h>
#include <include/core/SkCanvas.h>
#include <include/core/SkFont.h>
#include <include/core/SkGraphics.h>
#include <include/core/SkSurface.h>
#include <include/core/SkTextBlob.h>
#include <include/core/SkTypeface.h>
#include <include/effects/SkGradientShader.h>
#include <include/gpu/gl/GrGLInterface.h>
#include <include/gpu/GrDirectContext.h>

#ifndef GL_GLEXT_PROTOTYPES
#define GL_GLEXT_PROTOTYPES 1
#endif
#include <GLES2/gl2.h>
#include <EGL/egl.h>
#include <GLES2/gl2ext.h>
#include <EGL/eglext.h>

/*
 * Set the render resolution. This is what skia will use
 * as a render resolution. The render calls will assume this
 * resolution and be scaled to overlay buffer size.
 */
#define RENDER_TARGET_WIDTH 1920
#define RENDER_TARGET_HEIGHT 1080
#define OVL_BUFFER_WIDTH (RENDER_TARGET_WIDTH + RENDER_TARGET_WIDTH % 16)
#define OVL_BUFFER_HEIGHT (RENDER_TARGET_HEIGHT + RENDER_TARGET_HEIGHT % 16)

#define RENDER_T 33

#define FONT_PATH "/usr/share/fonts/truetype/wqy/wqy-microhei.ttc"
#define SWITCH_AFTER_MS 5000

enum class skia_examples {
  harfbuzz,
  animate_font,
  shapes,
  raqm,
  hb_comp
};

/*
 * Below is the list of examples you wish to run,
 * switching every SWITCH_AFTER_MS milliseconds.
 */
static std::vector<skia_examples>
run_examples = {
  skia_examples::harfbuzz,
  skia_examples::animate_font,
  skia_examples::hb_comp,
  skia_examples::raqm,
  skia_examples::shapes
};

static sk_sp<GrDirectContext> gr_context;

static skia_examples
get_active_example()
{
  static int counter = 0;
  static auto start = std::chrono::steady_clock::now();
  std::chrono::duration<double, std::milli> duration = std::chrono::steady_clock::now() - start;
  if (duration.count() >= SWITCH_AFTER_MS) {
    start = std::chrono::steady_clock::now();
    counter++;
    counter %= run_examples.size();
  }

  return run_examples[counter];
}

static sk_sp<SkTextBlob>
hb_create_text_blob(SkFont &font, const char *message, const char *font_path = FONT_PATH)
{
  FT_Library ft_library;
  FT_Face ft_face;

  /* Initialize FreeType and create FreeType font face. */
  FT_Init_FreeType(&ft_library);
  FT_New_Face(ft_library, FONT_PATH, 0, &ft_face);
  if (!ft_face) {
    fprintf(stderr, "Unable to load font from file\n");
    FT_Done_FreeType(ft_library);
    return nullptr;
  }

  const int font_size = font.getSize();
  FT_Set_Char_Size(ft_face, font_size * 64, font_size * 64, 0, 0);

  hb_buffer_t *hb_buffer = hb_buffer_create();
  if (!hb_buffer) {
    fprintf(stderr, "Unable to create hb buffer\n");
    FT_Done_Face(ft_face);
    FT_Done_FreeType(ft_library);
    return nullptr;
  }

  hb_font_t *hb_font = hb_ft_font_create(ft_face, NULL);
  if (!hb_font) {
    fprintf(stderr, "Unable to create hb font\n");
    hb_buffer_destroy(hb_buffer);
    FT_Done_Face(ft_face);
    FT_Done_FreeType(ft_library);
    return nullptr;
  }

  hb_buffer_add_utf8(hb_buffer, message, strlen(message), 0, strlen(message));
  hb_buffer_guess_segment_properties(hb_buffer);
  hb_shape(hb_font, hb_buffer, NULL, 0);

  size_t count = hb_buffer_get_length(hb_buffer);
  hb_glyph_info_t *hb_info = hb_buffer_get_glyph_infos(hb_buffer, NULL);
  hb_glyph_position_t *pos = hb_buffer_get_glyph_positions(hb_buffer, NULL);

  SkTextBlobBuilder text_blob_builder;
  const SkTextBlobBuilder::RunBuffer& runBuffer = text_blob_builder.allocRunPos(font, count);

  double x = 0;
  double y = 0;
  for (unsigned int i = 0; i < count; i++) {
    runBuffer.glyphs[i] = hb_info[i].codepoint;
    reinterpret_cast<SkPoint*>(runBuffer.pos)[i] = SkPoint::Make(
        x + pos[i].x_offset / 64.,
        y - pos[i].y_offset / 64.);
    x += pos[i].x_advance / 64.;
    y += pos[i].y_advance / 64.;
  }
  sk_sp<SkTextBlob> textblob = text_blob_builder.make();

  hb_buffer_destroy(hb_buffer);
  hb_font_destroy(hb_font);
  FT_Done_Face(ft_face);
  FT_Done_FreeType(ft_library);
  return textblob;
}

static sk_sp<SkTextBlob>
rq_create_text_blob(SkFont &font, const char *message, const char *font_path = FONT_PATH)
{
  FT_Library ft_library;
  FT_Face ft_face;
  size_t count;

  /* Initialize FreeType and create FreeType font face. */
  FT_Init_FreeType(&ft_library);
  FT_New_Face(ft_library, FONT_PATH, 0, &ft_face);
  if (!ft_face) {
    fprintf(stderr, "Unable to load font from file\n");
    FT_Done_FreeType(ft_library);
    return nullptr;
  }

  const int font_size = font.getSize();
  FT_Set_Char_Size(ft_face, font_size * 64, font_size * 64, 0, 0);

  raqm_t *rq = raqm_create();
  if (!rq) {
    fprintf(stderr, "Unable to create raqm structure\n");
    FT_Done_Face(ft_face);
    FT_Done_FreeType(ft_library);
    return nullptr;
  }
  raqm_set_text_utf8(rq, message, strlen(message));
  raqm_set_freetype_face(rq, ft_face);
  raqm_set_par_direction(rq, RAQM_DIRECTION_DEFAULT);
  raqm_layout(rq);
  raqm_glyph_t *glyphs = raqm_get_glyphs(rq, &count);

  SkTextBlobBuilder text_blob_builder;
  const SkTextBlobBuilder::RunBuffer& runBuffer = text_blob_builder.allocRunPos(font, count);

  double x = 0;
  double y = 0;
  for (unsigned int i = 0; i < count; i++) {
    runBuffer.glyphs[i] = glyphs[i].index;
    reinterpret_cast<SkPoint*>(runBuffer.pos)[i] = SkPoint::Make(
        x + glyphs[i].x_offset / 64.,
        y - glyphs[i].y_offset / 64.);
    x += glyphs[i].x_advance / 64.;
    y += glyphs[i].y_advance / 64.;
  }
  sk_sp<SkTextBlob> textblob = text_blob_builder.make();

  raqm_destroy(rq);
  FT_Done_Face(ft_face);
  FT_Done_FreeType(ft_library);
  return textblob;
}

static void
draw_text_blob(SkPaint &paint, SkCanvas *canvas, sk_sp<SkTextBlob> blob,
     SkColor fill_color, SkColor stroke_color, float stroke_width = 5.0f)
{
  paint.setStrokeWidth(stroke_width);
  paint.setColor(stroke_color);
  paint.setStyle(SkPaint::kStroke_Style);
  canvas->drawTextBlob(blob, 20, 20, paint);
  paint.setColor(fill_color);
  paint.setStyle(SkPaint::kFill_Style);
  canvas->drawTextBlob(blob, 20, 20, paint);
}

static void
draw_harfbuzz_example(SkCanvas *canvas, SkFont &font)
{
  canvas->clear(SK_AlphaTRANSPARENT);

  static SkPaint paint;
  static float angle = 0;

  paint.setAntiAlias(true);
  canvas->translate(sin(angle) * 10, 0);

  angle += 0.3f;
  angle = fmod(angle, M_PI * 2);

  font.setSize(120);

  /* Generate text blob. Make static if nothing changes. */
  static const char message[] = "Harfbuzz";
  static auto hb_blob = hb_create_text_blob(font, message);
  if (!hb_blob) {
    fprintf(stderr, "Unable to create blob with Harfbuzz\n");
    return;
  }

  /* Draw the text */
  for (int y = 0; y < 8; y++) {
    canvas->save();
    canvas->translate(0, -40 + 130 * (y + 1));
    for (int x = 0; x < 4; x++) {
      /* Draw a message with a nice black paint and red outline */
      draw_text_blob(paint, canvas, hb_blob, SK_ColorBLACK, SK_ColorRED);
      canvas->translate(500, 0);
    }
    canvas->restore();
  }
}

static void
draw_animate_font_size_example(SkCanvas *canvas, SkFont &font)
{
  canvas->clear(SK_AlphaTRANSPARENT);

  static SkPaint paint;
  static float angle = 0;

  paint.setAntiAlias(true);

  angle += 0.1f;
  angle = fmod(angle, M_PI * 2);

  font.setSize(40 * sin(angle) + 100);

  /* Generate text blob. Make static if nothing changes. */
  static const char message[] = "Animate";
  auto hb_blob = hb_create_text_blob(font, message);
  if (!hb_blob) {
    fprintf(stderr, "Unable to create blob with Harfbuzz\n");
    return;
  }

  /* Draw the text */
  for (int y = 0; y < 8; y++) {
    canvas->save();
    canvas->translate(0, -40 + 130 * (y + 1));
    for (int x = 0; x < 4; x++) {
      /* Draw a message with a nice black paint and red outline */
      draw_text_blob(paint, canvas, hb_blob, SK_ColorBLACK, SK_ColorRED, font.getSize() / 24.0f);
      canvas->translate(500, 0);
    }
    canvas->restore();
  }
}

static void
draw_text_example(SkCanvas *canvas, SkFont &font)
{
  static SkPaint paint;
  paint.setAntiAlias(true);

  canvas->clear(SK_AlphaTRANSPARENT);
  font.setSize(140);

  static const char message[] = "Hej 畢哿每 αι πολύ χαρούμε";
  static auto hb_title_blob = hb_create_text_blob(font, "Harfbuzz (πολύ)");
  static auto hb_msg_blob = hb_create_text_blob(font, message);
  if (!hb_title_blob || !hb_msg_blob) {
    fprintf(stderr, "Unable to create blobs with Harfbuzz\n");
    return;
  }

  static auto rq_title_blob = rq_create_text_blob(font, "Raqm (πολύ)");
  static auto rq_msg_blob = rq_create_text_blob(font, message);
  if (!rq_title_blob || !rq_msg_blob) {
    fprintf(stderr, "Unable to create blobs with Raqm\n");
    return;
  }

  sk_sp<SkTextBlob> active_blob;
  canvas->save();
  if (get_active_example() == skia_examples::raqm) {
    canvas->translate(650, 200);
    draw_text_blob(paint, canvas, rq_title_blob, SK_ColorBLACK, SK_ColorRED,
                   font.getSize() / 24.0f);
    active_blob = rq_msg_blob;
  } else {
    canvas->translate(550, 200);
    draw_text_blob(paint, canvas, hb_title_blob, SK_ColorBLACK, SK_ColorRED,
                   font.getSize() / 24.0f);
    active_blob = hb_msg_blob;
  }
  canvas->restore();
  canvas->save();
  canvas->translate(100, 540);
  draw_text_blob(paint, canvas, active_blob, SK_ColorBLACK, SK_ColorRED, font.getSize() / 24.0f);
  canvas->restore();
}

static void
draw_shapes_example(SkCanvas *canvas)
{
  static SkPaint paint;
  static float angle = 0;

  /* Clear the background with a transparent blue */
  canvas->clear(SkColorSetARGB(200, 0, 0, 100));

  /* Animate canvas */
  canvas->rotate(5 * sin(angle));
  float scale_factor = sin(angle) + 2;
  canvas->scale(scale_factor, scale_factor);
  paint.setAntiAlias(true);

  /* Set up a linear gradient and draw 10 rectangles */
  {
    SkPoint linear_points[] = { { 0, 0 }, { 300, 300 } };
    SkColor linear_colors[] = { SK_ColorRED, SK_ColorYELLOW };
    paint.setShader(SkGradientShader::MakeLinear(linear_points, linear_colors, nullptr, 2,
                                                 SkTileMode::kMirror));
    SkRect rect = SkRect::MakeXYWH(10, 10, 512, 128);
    paint.setStyle(SkPaint::kStroke_Style);
    paint.setStrokeWidth(5);
    for (int i = 0; i < 10; i++) {
      rect.offset(20, 30);
      canvas->drawRect(rect, paint);
    }

    /* Detach shader */
    paint.setShader(nullptr);
  }

  /* Set up a linear gradient and draw a circle */
  {
    SkPoint linear_points[] = { { 0, 0 }, { 300, 300 } };
    SkColor linear_colors[] = { SK_ColorGREEN, SK_ColorBLACK };
    paint.setShader(SkGradientShader::MakeLinear(linear_points, linear_colors, nullptr, 2,
                                                 SkTileMode::kMirror));
    paint.setStyle(SkPaint::kStroke_Style);
    paint.setStrokeWidth(15);
    canvas->drawCircle(300, 128, 64, paint);

    /* Detach shader */
    paint.setShader(nullptr);
  }

  /* Setup a path with cubic interpolation and draw it */
  {
    SkPath path;
    path.cubicTo(768, 0, -512, 256, 256, 256);
    path.offset(50, 50);
    paint.setStrokeWidth(5);
    paint.setColor(SK_ColorCYAN);
    canvas->drawPath(path, paint);
  }

  angle += 0.1f;
  angle = fmod(angle, M_PI * 2);
}

static void
draw(SkCanvas *canvas)
{
  static sk_sp<SkTypeface> tf = SkTypeface::MakeFromFile(FONT_PATH, 0);
  static SkFont default_font(tf);

  switch (get_active_example()) {
    case skia_examples::harfbuzz:
      draw_harfbuzz_example(canvas, default_font);
      break;
    case skia_examples::animate_font:
      draw_animate_font_size_example(canvas, default_font);
      break;
    case skia_examples::shapes:
      draw_shapes_example(canvas);
      break;
    case skia_examples::raqm:
    case skia_examples::hb_comp:
      draw_text_example(canvas, default_font);
      break;
    default:
      throw std::runtime_error("Example is undefined");
  }
}

static gboolean
signal_handler(gpointer data)
{
  GMainLoop *main_loop = (GMainLoop *) data;
  g_main_loop_quit(main_loop);
  return G_SOURCE_REMOVE;
}

static gboolean
render_trigger_redraw(gpointer data)
{
  GError *error = NULL;
  axoverlay_redraw(&error);
  if (error) {
    fprintf(stderr, "%s: Failed to trigger redraw using axoverlay: %s\n",
        __func__, error->message);
    g_error_free(error);
    return FALSE;
  }
  return TRUE;
}

static sk_sp<SkSurface>
create_render_surface(int width, int height)
{
  static const int sample_count = 0;
  static const int stencil_bits = 8;
  GrGLint sk_buffer;

  /*
   * Wrap the frame buffer object attached to the screen in a Skia render target so Skia can
   * render to it
   */
  glGetIntegerv(GL_FRAMEBUFFER_BINDING, &sk_buffer);

  GrGLFramebufferInfo info;
  info.fFBOID = (GrGLuint) sk_buffer;
  SkColorType color_type;

  color_type = kBGRA_8888_SkColorType;
  info.fFormat = GL_BGRA8_EXT;

  GrBackendRenderTarget target(width, height, sample_count, stencil_bits, info);

  const SkSurfaceProps props;
  sk_sp<SkSurface> surface(SkSurface::MakeFromBackendRenderTarget(gr_context.get(), target,
                                                                  kTopLeft_GrSurfaceOrigin,
                                                                  color_type, nullptr, &props));
  if (!surface) {
    std::string msg = "Unable to create a surface with size: ";
    throw std::runtime_error(msg + std::to_string(width) + "x" + std::to_string(height));
  }

  return surface;
}

static void
render_overlay_cb(gpointer render_context, gint id,
                   struct axoverlay_stream_data *stream,
                   enum axoverlay_position_type postype, gfloat overlay_x,
                   gfloat overlay_y, gint overlay_width, gint overlay_height,
                   gpointer user_data)
{
  gr_context->resetContext();
  try {
    auto surface = create_render_surface(overlay_width, overlay_height);
    auto canvas = surface->getCanvas();
    if (!canvas) {
      throw std::runtime_error("No canvas was provided by surface!");
    }

    auto info = canvas->imageInfo();
    if (info.width() != OVL_BUFFER_WIDTH || info.height() != OVL_BUFFER_HEIGHT) {
      canvas->scale((float) overlay_width / OVL_BUFFER_WIDTH,
                    (float) overlay_height / OVL_BUFFER_HEIGHT);
    }

    draw(canvas);
    surface->flushAndSubmit();
  } catch (const std::exception& e) {
    fprintf(stderr, "Failed to draw to canvas %s", e.what());
    raise(SIGTERM);
  }
}

int
main(int argc, char **argv)
{
  struct axoverlay_settings settings;
  struct axoverlay_overlay_data ax_data;
  gint overlay_id = -1;
  GError *error = NULL;
  GMainLoop *main_loop = NULL;

  main_loop = g_main_loop_new(NULL, FALSE);
  g_unix_signal_add(SIGINT, signal_handler, main_loop);
  g_unix_signal_add(SIGTERM, signal_handler, main_loop);

  /* Add init code */
  axoverlay_init_axoverlay_settings(&settings);

  settings.render_callback = render_overlay_cb;
  settings.adjustment_callback = NULL;
  settings.select_callback = NULL;
  settings.backend = AXOVERLAY_OPENGLES_BACKEND;

  axoverlay_init(&settings, &error);
  if (error != NULL) {
    fprintf(stderr, "Failed to initialize axoverlay: %s", error->message);
    g_error_free(error);
    return 1;
  }

  axoverlay_init_overlay_data(&ax_data);
  ax_data.postype = AXOVERLAY_CUSTOM_NORMALIZED;
  ax_data.anchor_point = AXOVERLAY_ANCHOR_CENTER;
  ax_data.width  = axoverlay_get_max_resolution_width(AXOVERLAY_DEFAULT_CAMERA_ID, NULL);
  ax_data.height = axoverlay_get_max_resolution_height(AXOVERLAY_DEFAULT_CAMERA_ID, NULL);
  ax_data.x = 0.0;
  ax_data.y = 0.0;
  ax_data.scale_to_stream = TRUE;
  ax_data.colorspace = AXOVERLAY_COLORSPACE_ARGB32;

  overlay_id = axoverlay_create_overlay(&ax_data, NULL, &error);
  if (error != NULL) {
    fprintf(stderr, "Failed to create first overlay: %s", error->message);
    g_error_free(error);
    return 1;
  }

  /* setup contexts */
  auto interface = GrGLMakeNativeInterface();
  gr_context = GrDirectContext::MakeGL(interface);
  SkASSERT(gr_context);

  g_timeout_add(RENDER_T, render_trigger_redraw, NULL);
  g_main_loop_run(main_loop);

  axoverlay_destroy_overlay(overlay_id, &error);
  if (error != NULL) {
    fprintf(stderr, "Failed to destroy first overlay: %s", error->message);
    g_error_free(error);
    return 0;
  }

  axoverlay_cleanup();
  g_main_loop_unref(main_loop);
  return 0;
}
