
#ifndef SERVICES_DISPLAY_DISPLAY_SERVICE_H
#define SERVICES_DISPLAY_DISPLAY_SERVICE_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_timer.h>
#include <string>

#include "../Service.h"

const int FRAME_BUFFER_SIZE = 20;

namespace afk {

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
class DisplayService : public Service {
 public:
  /**
   * @brief Construct a new DisplayService object
   *
   */
  DisplayService();

  /**
   * @brief Destroy the DisplayService object
   *
   */
  virtual ~DisplayService();

  /**
   * @brief Get the name of service
   *
   * @return name
   */
  std::string getName() const;

  /**
   * @brief Notify about event updates
   *
   * @param event Event which happened
   */
  virtual void notify(const SDL_Event& event);

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
  int getDisplayServiceMode() const;

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
  unsigned int getDisplayServiceWidth() const;

  /**
   * @brief Get the current height of window
   *
   * @return height of window
   */
  unsigned int getDisplayServiceHeight() const;

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

  /**
   * @brief Get the current frames per second
   *
   * @return int Frames per second
   */
  int getFps();

  /**
   * @brief Get the window renderer
   *
   * @return SDL_Renderer* pointer to window renderer
   */
  SDL_Renderer* getRenderer();

  /**
   * @brief Get the window
   *
   * @return SDL_Window* pointer to window
   */
  SDL_Window* getWindow();

 private:
  /**
   * @brief Draw a scene. Calls the draw and draw_internal functions of a given
   * Scene object
   *
   * @param current_scene Scene to draw
   */
  void draw(Scene* current_scene);

  /// Width of buffer
  unsigned int draw_w = 0;

  /// Height of buffer
  unsigned int draw_h = 0;

  /// Width of window
  unsigned int window_w = 0;

  /// Height of window
  unsigned int window_h = 0;

  /// X translation of window
  unsigned int translation_x = 0;

  /// Y translation of window
  unsigned int translation_y = 0;

  /// X scaling amount
  float scale_x = 0;

  /// Y scaling amount
  float scale_y = 0;

  /// Current display mode
  DISPLAY_MODE display_mode = DISPLAY_MODE::WINDOWED;

  /// Active window
  SDL_Window* window = nullptr;

  /// Renderer
  SDL_Renderer* renderer = nullptr;

  /// Fps timer
  double old_time = 0;

  /// Frame array for calculating fps
  unsigned int frames_array[FRAME_BUFFER_SIZE] = {0};

  /// Current fps
  unsigned int fps = 0;

  /// Timer id
  SDL_TimerID draw_timer = 0;

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

}  // namespace afk

#endif  // SERVICES_DISPLAY_DISPLAY_SERVICE_H

/**
 * @example ex_display.cpp
 * This is an example of how to use the Window class to create a basic display.
 */