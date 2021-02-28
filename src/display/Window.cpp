#include "display/Window.h"

#include <allegro5/allegro.h>

#include "common/Exceptions.h"
#include "scene/Scene.h"
#include "color/Color.h"

Window::Window()
    : draw_w(0),
      draw_h(0),
      window_w(0),
      window_h(0),
      translation_x(0),
      translation_y(0),
      scale_x(0),
      scale_y(0),
      display_mode(DISPLAY_MODE::WINDOWED),
      display(nullptr),
      buffer(nullptr),
      frames_array() {}

// Returns current display mode
int Window::getDisplayMode() const {
  return display_mode;
}

// Gets draw width
unsigned int Window::getDrawWidth() const {
  return draw_w;
}

// Gets draw height
unsigned int Window::getDrawHeight() const {
  return draw_h;
}

// Gets translation x
unsigned int Window::getTranslationX() const {
  return translation_x;
}

// Gets translation y
unsigned int Window::getTranslationY() const {
  return translation_y;
}

// Gets scale width
unsigned int Window::getWindowWidth() const {
  return window_w;
}

// Gets scale height
unsigned int Window::getWindowHeight() const {
  return window_h;
}

// Gets scale x
float Window::getScaleX() const {
  return scale_x;
}

// Gets scale y
float Window::getScaleY() const {
  return scale_y;
}

// Hide mouse from display
void Window::hideMouse() {
  al_hide_mouse_cursor(display);
}

// Show mouse on display
void Window::showMouse() {
  al_show_mouse_cursor(display);
}

// Register display with event queue
void Window::registerEventSource(ALLEGRO_EVENT_QUEUE* queue) {
  al_register_event_source(queue, al_get_display_event_source(display));
}

// Resize window
void Window::resize(const unsigned int window_w, const unsigned int window_h) {
  // Get monitor width
  ALLEGRO_MONITOR_INFO info;
  al_get_monitor_info(0, &info);

  // Window mode
  switch (display_mode) {
    // Fullscreen windowed stretch
    case DISPLAY_MODE::FULLSCREEN_WINDOW_STRETCH:
      // Set flags
      al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

      // Set up screen size and positions
      setWindowSize(info.x2 - info.x1, info.y2 - info.y1);
      setScale((float)window_w / draw_w, (float)window_h / draw_h);
      setTranslation(0.0f, 0.0f);

      break;

    // Fullscreen window center
    case DISPLAY_MODE::FULLSCREEN_WINDOW_CENTER:
      // Set flags
      al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

      // Set up screen size and positions
      setWindowSize(info.x2 - info.x1, info.y2 - info.y1);
      setScale(1.0f, 1.0f);
      setTranslation((window_w - scale_x * draw_w) / 2,
                     (window_h - scale_y * draw_h) / 2);

      break;

    // Fullscreen window center
    case DISPLAY_MODE::FULLSCREEN_WINDOW_LETTERBOX:
      // Set flags
      al_set_new_display_flags(ALLEGRO_FULLSCREEN_WINDOW);

      // Set up screen size and positions
      setWindowSize(info.x2 - info.x1, info.y2 - info.y1);
      setScale(std::min((float)window_w / draw_w, (float)window_h / draw_h),
               std::min((float)window_w / draw_w, (float)window_h / draw_h));
      setTranslation((window_w - scale_x * draw_w) / 2,
                     (window_h - scale_y * draw_h) / 2);

      break;

    // Windowed
    case DISPLAY_MODE::WINDOWED:
      // Set flags
      al_set_new_display_flags(ALLEGRO_WINDOWED | ALLEGRO_RESIZABLE);

      // Set up screen size and positions
      setWindowSize(window_w, window_h);
      setScale((float)window_w / draw_w, (float)window_h / draw_h);
      setTranslation(0.0f, 0.0f);

      break;

    // Invalid mode
    default:
      throw InvalidParameterException("Invalid display mode passed");
  }
}

// Set window size
void Window::setWindowSize(const unsigned int width,
                           const unsigned int height) {
  window_w = width;
  window_h = height;
}

// Set buffer size
void Window::setBufferSize(const unsigned int width,
                           const unsigned int height) {
  draw_w = width;
  draw_h = height;
}

// Set scale
void Window::setScale(const float width, const float height) {
  scale_x = width;
  scale_y = height;
}

// Set translation
void Window::setTranslation(const unsigned int x, const unsigned int y) {
  translation_x = x;
  translation_y = y;
}

// Set window
void Window::setTitle(const std::string& title) {
  al_set_window_title(display, title.c_str());
}

// Set display icon
void Window::setIcon(const std::string& path) {
  ALLEGRO_BITMAP* icon = al_load_bitmap(path.c_str());
  if (!icon) {
    throw FileIOException("Could not load icon " + path);
  }
  al_set_display_icon(display, icon);
}

// Change display mode
void Window::setMode(const DISPLAY_MODE mode) {
  // Destroy existing display
  if (display) {
    al_destroy_display(display);
    display = nullptr;
  }

  // Create buffer
  if (!buffer) {
    buffer = al_create_bitmap(getDrawWidth(), getDrawHeight());
  }

  // Set mode
  display_mode = mode;

  // Resize window
  resize(window_w, window_h);

  // Create display
  display = al_create_display(window_w, window_h);
}

void Window::draw(Scene* current_scene) {
  if (!display || !buffer) {
    return;
  }

  // Render a frame
  al_set_target_bitmap(buffer);
  al_clear_to_color(Color::rgb(0, 0, 0));

  current_scene->drawInternal();
  current_scene->draw();

  al_set_target_backbuffer(display);
  al_clear_to_color(Color::rgb(0, 0, 0));
  al_draw_scaled_bitmap(buffer, 0, 0, draw_w, draw_h, translation_x,
                        translation_y, window_w, window_h, 0);

  // Flip (OpenGL)
  al_flip_display();

  // Shift fps buffer
  for (unsigned int i = FRAME_BUFFER_SIZE - 1; i > 0; i--) {
    frames_array[i] = frames_array[i - 1];
  }

  frames_array[0] = (1.0 / (al_get_time() - old_time));
  old_time = al_get_time();

  unsigned int fps_total = 0;

  for (unsigned int i = 0; i < FRAME_BUFFER_SIZE; i++) {
    fps_total += frames_array[i];
  }

  // FPS = average
  fps = fps_total / FRAME_BUFFER_SIZE;
}
