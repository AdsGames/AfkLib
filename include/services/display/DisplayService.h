/**
 * @file DisplayService.h
 * @author
 *  Allan Legemaate (alegemaate@gmail.com)
 *  Danny Van Stemp (dannyvanstemp@gmail.com)
 * @brief Service that encapsulates SDL display related functionality.
 * @version 0.1
 * @date 2018-11-20
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INCLUDE_SERVICES_DISPLAY_DISPLAYSERVICE_H_
#define INCLUDE_SERVICES_DISPLAY_DISPLAYSERVICE_H_

#include <SDL2/SDL.h>
#include <string>

#include "../../color/Color.h"
#include "../Service.h"

const int FRAME_BUFFER_SIZE = 50;

namespace afk {

class Scene;

/**
 * @brief Display modes supported by window object
 *
 */
enum class DisplayMode {
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
 * @brief Manages sdl display pointer and allows easy manipulation of
 * configuration
 *
 */
class DisplayService {
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
   * @brief Draw a scene. Calls the draw and draw_internal functions of a given
   * Scene object
   *
   * @param current_scene Scene to draw
   */
  void draw(Scene* current_scene);

  /**
   * @brief Set the current display mode. Should be called once on
   * initialization of game and any time the display mode needs to change
   *
   * @param mode Display mode to set it to
   * @see DisplayMode
   */
  void setMode(const DisplayMode mode);

  /**
   * @brief Set the size of the buffer
   *
   * @param width Width of buffer in pixels
   * @param height Height of buffer in pixels
   */
  void setBufferSize(const Uint32 width, const Uint32 height);

  /**
   * @brief Set the size of the window
   *
   * @param width Width of window in pixels
   * @param height Height of window in pixels
   */
  void setWindowSize(const Uint32 width, const Uint32 height);

  /**
   * @brief Get the current display mode
   *
   * @return Selected display mode
   * @see DisplayMode
   */
  DisplayMode getDisplayMode() const;

  /**
   * @brief Get the buffer width
   *
   * @return Width of buffer in pixels
   */
  Uint32 getDrawWidth() const;

  /**
   * @brief Get the buffer height
   *
   * @return Height of buffer in pixels
   */
  Uint32 getDrawHeight() const;

  /**
   * @brief Get the x translation of the window
   *
   * @return X translation in pixels
   */
  Uint32 getTranslationX() const;

  /**
   * @brief Get the y translation of the window
   *
   * @return Y translation in pixels
   */
  Uint32 getTranslationY() const;

  /**
   * @brief Get the current width of the winodw
   *
   * @return width of window
   */
  Uint32 getDisplayServiceWidth() const;

  /**
   * @brief Get the current height of window
   *
   * @return height of window
   */
  Uint32 getDisplayServiceHeight() const;

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
  void resize(const Uint32 window_w, const Uint32 window_h);

  /**
   * @brief Set the window title
   *
   * @param title String to show in title
   */
  void setTitle(const std::string& title);

  /**
   * @brief Set the window icon
   *
   * @param path Path to sdl compatible image
   */
  void setIcon(const std::string& path);

  /**
   * @brief Set clear color
   *
   * @param color to set to
   */
  void setBackgroundColor(const color::Color& color);

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
  /// Width of buffer
  Uint32 draw_w = 0;

  /// Height of buffer
  Uint32 draw_h = 0;

  /// Width of window
  Uint32 window_w = 0;

  /// Height of window
  Uint32 window_h = 0;

  /// X translation of window
  Uint32 translation_x = 0;

  /// Y translation of window
  Uint32 translation_y = 0;

  /// X scaling amount
  float scale_x = 0;

  /// Y scaling amount
  float scale_y = 0;

  /// Current display mode
  DisplayMode display_mode = DisplayMode::WINDOWED;

  /// Active window
  SDL_Window* window = nullptr;

  /// Renderer
  SDL_Renderer* renderer = nullptr;

  /// Fps timer
  Uint32 old_time = 0;

  /// Frame array for calculating fps
  Uint32 frames_array[FRAME_BUFFER_SIZE] = {0};

  /// Current fps
  Uint32 fps = 0;

  /// Frame index
  Uint32 frame_index = 0;

  /// Clear color
  color::Color clear_color;

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
  void setTranslation(const Uint32 x, const Uint32 y);
};

}  // namespace afk

#endif  // INCLUDE_SERVICES_DISPLAY_DISPLAYSERVICE_H_

/**
 * @example ex_display.cpp
 * This is an example of how to use the Window class to create a basic display.
 */

/**
 * @example ex_fps.cpp
 * This example shows how to use the fps functionality
 */
