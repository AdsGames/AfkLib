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
#ifndef AFK_DISPLAYSERVICE_H
#define AFK_DISPLAYSERVICE_H

#include <SDL2/SDL.h>
#include <string>

#include "../../common/Color.h"
#include "../Service.h"

const int frameBufferSize = 50;

namespace afk {

class Scene;

/**
 * @brief Display modes supported by window object
 *
 */
enum class DisplayMode {
  /// Stretches window in full screen
  FullScreenWindowStretch,
  /// Shows window in highest resolution without clipping or stretching
  FullScreenWindowLetterbox,
  /// Centers the window at the standard window resolution
  FullScreenWindowCenter,
  /// Shows window in windowed mode at set window size
  Windowed,
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
   * @param currentScene Scene to draw
   */
  void draw(Scene* currentScene);

  /**
   * @brief Set the current display mode. Should be called once on
   * initialization of game and any time the display mode needs to change
   *
   * @param mode Display mode to set it to
   * @see DisplayMode
   */
  void setMode(DisplayMode mode);

  /**
   * @brief Set the size of the buffer
   *
   * @param width Width of buffer in pixels
   * @param height Height of buffer in pixels
   */
  void setBufferSize(uint32_t width, uint32_t height);

  /**
   * @brief Set the size of the window
   *
   * @param width Width of window in pixels
   * @param height Height of window in pixels
   */
  void setWindowSize(uint32_t width, uint32_t height);

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
  uint32_t getDrawWidth() const;

  /**
   * @brief Get the buffer height
   *
   * @return Height of buffer in pixels
   */
  uint32_t getDrawHeight() const;

  /**
   * @brief Get the x translation of the window
   *
   * @return X translation in pixels
   */
  uint32_t getTranslationX() const;

  /**
   * @brief Get the y translation of the window
   *
   * @return Y translation in pixels
   */
  uint32_t getTranslationY() const;

  /**
   * @brief Get the current width of the winodw
   *
   * @return width of window
   */
  uint32_t getDisplayServiceWidth() const;

  /**
   * @brief Get the current height of window
   *
   * @return height of window
   */
  uint32_t getDisplayServiceHeight() const;

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
   * @param windowW Width in pixels
   * @param windowH Height in pixels
   */
  void resize(uint32_t windowW, uint32_t windowH);

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
  uint32_t drawW = 0;

  /// Height of buffer
  uint32_t drawH = 0;

  /// Width of window
  uint32_t windowW = 0;

  /// Height of window
  uint32_t windowH = 0;

  /// X translation of window
  uint32_t translationX = 0;

  /// Y translation of window
  uint32_t translationY = 0;

  /// X scaling amount
  float scaleX = 0;

  /// Y scaling amount
  float scaleY = 0;

  /// Current display mode
  DisplayMode displayMode = DisplayMode::Windowed;

  /// Active window
  SDL_Window* window = nullptr;

  /// Renderer
  SDL_Renderer* renderer = nullptr;

  /// Fps timer
  uint32_t oldTime = 0;

  /// Frame array for calculating fps
  uint32_t framesArray[frameBufferSize] = {0};

  /// Current fps
  uint32_t fps = 0;

  /// Frame index
  uint32_t frameIndex = 0;

  /// Clear color
  color::Color clearColor;

  /**
   * @brief Sets the window scaling in percent
   *
   * @param x X scaling percent
   * @param y Y scaling percent
   */
  void setScale(float x, float y);

  /**
   * @brief Set the translation amount in pixels
   *
   * @param x X translation
   * @param y Y translation
   */
  void setTranslation(uint32_t x, uint32_t y);
};

}  // namespace afk

#endif  // AFK_DISPLAYSERVICE_H

/**
 * @example ex_display.cpp
 * This is an example of how to use the Window class to create a basic display.
 */

/**
 * @example ex_fps.cpp
 * This example shows how to use the fps functionality
 */
