
#ifndef ENGINE_DISPLAY_WINDOW_H
#define ENGINE_DISPLAY_WINDOW_H

#include <allegro5/display.h>
#include <string>

const int FRAME_BUFFER_SIZE = 100;

class Scene;

/**
 * @brief Display modes supported by window object
 *
 */
enum DISPLAY_MODE {
  /// Stretches window in fullscreen
  FULLSCREEN_WINDOW_STRETCH,
  /// Shows window in highest resolution without clipping or stretching
  FULLSCREEN_WINDOW_LETTERBOX,
  /// Centers the window at the standard window resolution
  FULLSCREEN_WINDOW_CENTER,
  /// Shows window in windowed mode at set window size
  WINDOWED,
};

/**
 * @brief Manages allegro display pointer and allows easy manipulation of
 * configuration
 *
 * @author Danny Van Stemp and Allan Legemaate
 * @date 20/11/2018
 */
class Window {
 public:
  /**
   * @brief Construct a new Window object
   *
   */
  Window();

  /**
   * @brief Destroy the Window object
   *
   */
  virtual ~Window(){};

  /**
   * @brief Set the current display mode. Should be called once on
   * initialization of game and any time the display mode needs to change
   *
   * @param mode Display mode to set it to
   * @see DISPLAY_MODE
   */
  void setMode(DISPLAY_MODE mode);

  /**
   * @brief Set the size of the buffer
   *
   * @param width Width of buffer in pixels
   * @param height Height of buffer in pixels
   */
  void setBufferSize(const unsigned int width, const unsigned int height);

  /**
   * @brief Set the size of the window
   *
   * @param width Width of window in pixels
   * @param height Height of window in pixels
   */
  void setWindowSize(const unsigned int width, const unsigned int height);

  /**
   * @brief Get the current display mode
   *
   * @return Selected display mode
   * @see DISPLAY_MODE
   */
  int getDisplayMode() const;

  /**
   * @brief Get the buffer width
   *
   * @return Width of buffer in pixels
   */
  unsigned int getDrawWidth() const;

  /**
   * @brief Get the buffer height
   *
   * @return Height of buffer in pixels
   */
  unsigned int getDrawHeight() const;

  /**
   * @brief Get the x translation of the window
   *
   * @return X translation in pixels
   */
  unsigned int getTranslationX() const;

  /**
   * @brief Get the y translation of the window
   *
   * @return Y translation in pixels
   */
  unsigned int getTranslationY() const;

  /**
   * @brief Get the current width of the winodw
   *
   * @return width of window
   */
  unsigned int getWindowWidth() const;

  /**
   * @brief Get the current height of window
   *
   * @return height of window
   */
  unsigned int getWindowHeight() const;

  /**
   * @brief Get the scaling being done on buffer. This is equivalent to buffer
   * width / window width
   *
   * @return X scale amount of buffer
   */
  float getScaleX() const;

  /**
   * @brief Get the scaling being done on buffer. This is equivalent to buffer
   * height / window height
   *
   * @return Y scale amount of buffer
   */
  float getScaleY() const;

  /**
   * @brief Hide mouse cursor
   *
   */
  void hideMouse();

  /**
   * @brief Show mouse cursor
   *
   */
  void showMouse();

  /**
   * @brief Resize window to given width and height
   *
   * @param window_w Width in pixels
   * @param window_h Height in pixels
   */
  void resize(const unsigned int window_w, const unsigned int window_h);

  /**
   * @brief Draw a scene. Calls the draw and draw_internal functions of a given
   * Scene object
   *
   * @param current_scene Scene to draw
   */
  void draw(Scene* current_scene);

  /**
   * @brief Register display with event queue
   *
   * @param queue Event queue to register with
   */
  void registerEventSource(ALLEGRO_EVENT_QUEUE* queue);

  /**
   * @brief Set the window title
   *
   * @param title String to show in title
   */
  void setTitle(const std::string& title);

  /**
   * @brief Set the window icon
   *
   * @param path Path to allegro compatible image
   */
  void setIcon(const std::string& path);

 private:
  /// Width of buffer
  unsigned int draw_w;

  /// Height of buffer
  unsigned int draw_h;

  /// Width of window
  unsigned int window_w;

  /// Height of window
  unsigned int window_h;

  /// X translation of window
  unsigned int translation_x;

  /// Y translation of window
  unsigned int translation_y;

  /// X scaling amount
  float scale_x;

  /// Y scaling amount
  float scale_y;

  /// Current display mode
  DISPLAY_MODE display_mode;

  /// Active display
  ALLEGRO_DISPLAY* display;

  /// Drawing buffer
  ALLEGRO_BITMAP* buffer;

  // Fps timer
  double old_time = 0;
  unsigned int frames_array[FRAME_BUFFER_SIZE];
  unsigned int fps = 0;

  /**
   * @brief Sets the window scaling in percent
   *
   * @param x X scaling percent
   * @param y Y scaling percent
   */
  void setScale(const float x, const float y);

  /**
   * @brief Set the translation amount in pixels
   *
   * @param x X translation
   * @param y Y translation
   */
  void setTranslation(const unsigned int x, const unsigned int y);
};

#endif  // ENGINE_DISPLAY_WINDOW_H
