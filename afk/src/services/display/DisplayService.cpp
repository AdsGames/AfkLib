/**
 * @file DisplayService.cpp
 * @author
 *   Allan Legemaate (alegemaate@gmail.com)
 *   Danny Van Stemp (dannyvanstemp@gmail.com)
 * @brief Implementation of DisplayService
 * @version 0.1
 * @date 2018-11-20
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "services/display/DisplayService.h"

#include <SDL2/SDL_image.h>

#include "common/Exceptions.h"
#include "scene/Scene.h"

namespace afk {

// Setup DisplayService
DisplayService::DisplayService() : oldTime(SDL_GetTicks()) {}

// Cleanup window
DisplayService::~DisplayService() {
  // Cleanup
  if (window) {
    SDL_DestroyWindow(window);
  }

  if (renderer) {
    SDL_DestroyRenderer(renderer);
  }
}

void DisplayService::draw(Scene* currentScene) {
  if (!window || !renderer) {
    return;
  }

  // Render a frame
  SDL_SetRenderDrawColor(renderer, clearColor.r, clearColor.g, clearColor.b,
                         clearColor.a);
  SDL_RenderClear(renderer);

  currentScene->draw();

  // Flip
  SDL_RenderPresent(renderer);

  // Update frame index
  uint32_t currentTime = SDL_GetTicks();
  framesArray[frameIndex] = currentTime - oldTime;
  oldTime = currentTime;
  frameIndex = (frameIndex + 1) % frameBufferSize;

  float fpsTotal = 0;
  for (unsigned int i : framesArray) {
    fpsTotal += i;
  }

  // FPS = average
  fps = 1000.0f / (fpsTotal / frameBufferSize);
}

// Returns current display mode
DisplayMode DisplayService::getDisplayMode() const {
  return displayMode;
}

// Gets draw width
uint32_t DisplayService::getDrawWidth() const {
  return drawW;
}

// Gets draw height
uint32_t DisplayService::getDrawHeight() const {
  return drawH;
}

// Gets translation x
uint32_t DisplayService::getTranslationX() const {
  return translationX;
}

// Gets translation y
uint32_t DisplayService::getTranslationY() const {
  return translationY;
}

// Gets scale width
uint32_t DisplayService::getDisplayServiceWidth() const {
  return windowW;
}

// Gets scale height
uint32_t DisplayService::getDisplayServiceHeight() const {
  return windowH;
}

// Gets scale x
float DisplayService::getScaleX() const {
  return scaleX;
}

// Gets scale y
float DisplayService::getScaleY() const {
  return scaleY;
}

// Hide mouse from display
void DisplayService::hideMouse() {
  SDL_ShowCursor(false);
}

// Show mouse on display
void DisplayService::showMouse() {
  SDL_ShowCursor(true);
}

// Resize window
void DisplayService::resize(const uint32_t windowW, const uint32_t windowH) {
  // Get monitor width
  SDL_DisplayMode info;
  SDL_GetCurrentDisplayMode(0, &info);

  // Window mode
  switch (displayMode) {
    // Full screen windowed stretch
    case DisplayMode::FullScreenWindowStretch:
      // Set flags
      SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

      // Set up screen size and positions
      setWindowSize(info.w, info.h);
      setScale(static_cast<float>(windowW) / drawW,
               static_cast<float>(windowH) / drawH);
      setTranslation(0.0f, 0.0f);

      break;

    // Full screen window center
    case DisplayMode::FullScreenWindowCenter:
      // Set flags
      SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

      // Set up screen size and positions
      setWindowSize(info.w, info.h);
      setScale(1.0f, 1.0f);
      setTranslation((windowW - scaleX * drawW) / 2,
                     (windowH - scaleY * drawH) / 2);

      break;

    // Full screen window center
    case DisplayMode::FullScreenWindowLetterbox:
      // Set flags
      SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

      // Set up screen size and positions
      setWindowSize(info.w, info.h);
      setScale(std::min(static_cast<float>(windowW) / drawW,
                        static_cast<float>(windowH) / drawH),
               std::min(static_cast<float>(windowW) / drawW,
                        static_cast<float>(windowH) / drawH));
      setTranslation((windowW - scaleX * drawW) / 2,
                     (windowH - scaleY * drawH) / 2);

      break;

    // Windowed
    case DisplayMode::Windowed:
      // Set flags
      SDL_SetWindowFullscreen(window, 0);

      // Set up screen size and positions
      setWindowSize(windowW, windowH);
      setScale(static_cast<float>(windowW) / drawW,
               static_cast<float>(windowH) / drawH);
      setTranslation(0.0f, 0.0f);

      break;

    // Invalid mode
    default:
      throw InvalidParameterException("Invalid display mode passed");
  }

  // Set scale
  SDL_RenderSetScale(renderer, drawW, drawH);
}

// Set window size
void DisplayService::setWindowSize(const uint32_t width,
                                   const uint32_t height) {
  windowW = width;
  windowH = height;
}

// Set buffer size
void DisplayService::setBufferSize(const uint32_t width,
                                   const uint32_t height) {
  drawW = width;
  drawH = height;
}

// Set scale
void DisplayService::setScale(const float width, const float height) {
  scaleX = width;
  scaleY = height;
}

// Set translation
void DisplayService::setTranslation(const uint32_t x, const uint32_t y) {
  translationX = x;
  translationY = y;
}

// Set window
void DisplayService::setTitle(const std::string& title) {
  SDL_SetWindowTitle(window, title.c_str());
}

// Set display icon
void DisplayService::setIcon(const std::string& path) {
  SDL_Surface* icon = IMG_Load(path.c_str());
  if (!icon) {
    throw FileIoException("Could not load icon " + path);
  }
  SDL_SetWindowIcon(window, icon);
  SDL_FreeSurface(icon);
}

// Set clear colour
void DisplayService::setBackgroundColor(const color::Color& color) {
  clearColor = color;
}

// Get fps
int DisplayService::getFps() {
  return fps;
}

// Get the window renderer
SDL_Renderer* DisplayService::getRenderer() {
  return renderer;
}

// Get window
SDL_Window* DisplayService::getWindow() {
  return window;
}

// Change display mode
void DisplayService::setMode(const DisplayMode mode) {
  // Destroy existing display
  if (window) {
    SDL_DestroyWindow(window);
  }

  // Set mode
  displayMode = mode;

  // Resize window
  resize(windowW, windowH);

  // Create display
  window =
      SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       windowW, windowH, SDL_WINDOW_RESIZABLE);
  if (!window) {
    throw InitException("Could not create window");
  }

  renderer = SDL_CreateRenderer(
      window, -1, SDL_RENDERER_ACCELERATED | SDL_RENDERER_PRESENTVSYNC);
  if (!renderer) {
    throw InitException("Could not create renderer");
  }
}

}  // namespace afk
