#include "services/display/DisplayService.h"

#include <allegro5/allegro.h>

#include "common/Exceptions.h"
#include "scene/Scene.h"
#include "services/Locator.h"

// Draw ticks per second
const float DRAWS_PER_SECOND = 60;

// Setup DisplayService
DisplayService::DisplayService() {
  Locator::getLogger().log("[Display Service]: Starting up");

  // Create timer
  fps_timer = al_create_timer(1.0 / DRAWS_PER_SECOND);
  al_start_timer(fps_timer);

  // Register timer events
  Locator::getEventQueue().registerSource(al_get_timer_event_source(fps_timer));

  // Register self
  Locator::getEventQueue().registerService(this);

  // Set initial time
  old_time = al_get_time();
}

// Cleanup window
DisplayService::~DisplayService() {
  Locator::getLogger().log("[Display Service]: Shutting down");

  // Unregister self
  Locator::getEventQueue().unregisterService(this);

  // Cleanup
  if (display) {
    al_destroy_display(display);
  }

  if (buffer) {
    al_destroy_bitmap(buffer);
  }

  if (fps_timer) {
    al_destroy_timer(fps_timer);
  }
}

// Notify
void DisplayService::notify(const ALLEGRO_EVENT& event) {
  if (event.type == ALLEGRO_EVENT_DISPLAY_RESIZE) {
    // resize(event.display.width, event.display.height);
  } else if (event.type == ALLEGRO_EVENT_TIMER &&
             event.timer.source == fps_timer) {
    draw(Locator::getScene().getScene());
  }
}

// Returns current display mode
int DisplayService::getDisplayMode() const {
  return display_mode;
}

// Gets draw width
unsigned int DisplayService::getDrawWidth() const {
  return draw_w;
}

// Gets draw height
unsigned int DisplayService::getDrawHeight() const {
  return draw_h;
}

// Gets translation x
unsigned int DisplayService::getTranslationX() const {
  return translation_x;
}

// Gets translation y
unsigned int DisplayService::getTranslationY() const {
  return translation_y;
}

// Gets scale width
unsigned int DisplayService::getDisplayWidth() const {
  return window_w;
}

// Gets scale height
unsigned int DisplayService::getDisplayHeight() const {
  return window_h;
}

// Gets scale x
float DisplayService::getScaleX() const {
  return scale_x;
}

// Gets scale y
float DisplayService::getScaleY() const {
  return scale_y;
}

// Hide mouse from display
void DisplayService::hideMouse() {
  al_hide_mouse_cursor(display);
}

// Show mouse on display
void DisplayService::showMouse() {
  al_show_mouse_cursor(display);
}

// Resize window
void DisplayService::resize(const unsigned int window_w,
                            const unsigned int window_h) {
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
void DisplayService::setWindowSize(const unsigned int width,
                                   const unsigned int height) {
  window_w = width;
  window_h = height;
}

// Set buffer size
void DisplayService::setBufferSize(const unsigned int width,
                                   const unsigned int height) {
  draw_w = width;
  draw_h = height;
}

// Set scale
void DisplayService::setScale(const float width, const float height) {
  scale_x = width;
  scale_y = height;
}

// Set translation
void DisplayService::setTranslation(const unsigned int x,
                                    const unsigned int y) {
  translation_x = x;
  translation_y = y;
}

// Set window
void DisplayService::setTitle(const std::string& title) {
  al_set_window_title(display, title.c_str());
}

// Set display icon
void DisplayService::setIcon(const std::string& path) {
  ALLEGRO_BITMAP* icon = al_load_bitmap(path.c_str());
  if (!icon) {
    throw FileIOException("Could not load icon " + path);
  }
  al_set_display_icon(display, icon);
}

// Get fps
int DisplayService::getFps() {
  return fps;
}

// Change display mode
void DisplayService::setMode(const DISPLAY_MODE mode) {
  // Destroy existing display
  if (display) {
    Locator::getEventQueue().unregisterSource(
        al_get_display_event_source(display));
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
  Locator::getEventQueue().registerSource(al_get_display_event_source(display));
}

void DisplayService::draw(Scene* current_scene) {
  if (!display || !buffer) {
    return;
  }

  // Render a frame
  al_set_target_bitmap(buffer);
  al_clear_to_color(al_map_rgb(0, 0, 0));

  current_scene->drawInternal();
  current_scene->draw();

  al_set_target_backbuffer(display);
  al_clear_to_color(al_map_rgb(0, 0, 0));
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
