#include "services/display/DisplayService.h"

#include <SDL2/SDL_image.h>

#include "common/Exceptions.h"
#include "scene/Scene.h"

#include "color/Color.h"
#include "services/Services.h"

namespace afk {

// Setup DisplayService
DisplayService::DisplayService() {
  // Set initial time
  old_time = SDL_GetTicks();
}

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

void DisplayService::draw(Scene* current_scene) {
  if (!window || !renderer) {
    return;
  }

  // Render a frame
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  current_scene->draw();
  current_scene->drawInternal();

  // Flip
  SDL_RenderPresent(renderer);

  // Update frame index
  frames_array[frame_index] = SDL_GetTicks() - old_time;
  old_time = SDL_GetTicks();
  frame_index = (frame_index + 1) % FRAME_BUFFER_SIZE;

  float fps_total = 0;
  for (Uint32 i = 0; i < FRAME_BUFFER_SIZE; ++i) {
    fps_total += frames_array[i];
  }

  // FPS = average
  fps = 1000.0f / (fps_total / FRAME_BUFFER_SIZE);
}

// Returns current display mode
DisplayMode DisplayService::getDisplayMode() const {
  return display_mode;
}

// Gets draw width
Uint32 DisplayService::getDrawWidth() const {
  return draw_w;
}

// Gets draw height
Uint32 DisplayService::getDrawHeight() const {
  return draw_h;
}

// Gets translation x
Uint32 DisplayService::getTranslationX() const {
  return translation_x;
}

// Gets translation y
Uint32 DisplayService::getTranslationY() const {
  return translation_y;
}

// Gets scale width
Uint32 DisplayService::getDisplayServiceWidth() const {
  return window_w;
}

// Gets scale height
Uint32 DisplayService::getDisplayServiceHeight() const {
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
  SDL_ShowCursor(false);
}

// Show mouse on display
void DisplayService::showMouse() {
  SDL_ShowCursor(true);
}

// Resize window
void DisplayService::resize(const Uint32 window_w, const Uint32 window_h) {
  // Get monitor width
  SDL_DisplayMode info;
  SDL_GetCurrentDisplayMode(0, &info);

  // Window mode
  switch (display_mode) {
    // Fullscreen windowed stretch
    case DisplayMode::FULLSCREEN_WINDOW_STRETCH:
      // Set flags
      SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

      // Set up screen size and positions
      setWindowSize(info.w, info.h);
      setScale((float)window_w / draw_w, (float)window_h / draw_h);
      setTranslation(0.0f, 0.0f);

      break;

    // Fullscreen window center
    case DisplayMode::FULLSCREEN_WINDOW_CENTER:
      // Set flags
      SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

      // Set up screen size and positions
      setWindowSize(info.w, info.h);
      setScale(1.0f, 1.0f);
      setTranslation((window_w - scale_x * draw_w) / 2,
                     (window_h - scale_y * draw_h) / 2);

      break;

    // Fullscreen window center
    case DisplayMode::FULLSCREEN_WINDOW_LETTERBOX:
      // Set flags
      SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

      // Set up screen size and positions
      setWindowSize(info.w, info.h);
      setScale(std::min((float)window_w / draw_w, (float)window_h / draw_h),
               std::min((float)window_w / draw_w, (float)window_h / draw_h));
      setTranslation((window_w - scale_x * draw_w) / 2,
                     (window_h - scale_y * draw_h) / 2);

      break;

    // Windowed
    case DisplayMode::WINDOWED:
      // Set flags
      SDL_SetWindowFullscreen(window, 0);

      // Set up screen size and positions
      setWindowSize(window_w, window_h);
      setScale((float)window_w / draw_w, (float)window_h / draw_h);
      setTranslation(0.0f, 0.0f);

      break;

    // Invalid mode
    default:
      throw InvalidParameterException("Invalid display mode passed");
  }

  // Set scale
  SDL_RenderSetScale(renderer, draw_w, draw_h);
}

// Set window size
void DisplayService::setWindowSize(const Uint32 width, const Uint32 height) {
  window_w = width;
  window_h = height;
}

// Set buffer size
void DisplayService::setBufferSize(const Uint32 width, const Uint32 height) {
  draw_w = width;
  draw_h = height;
}

// Set scale
void DisplayService::setScale(const float width, const float height) {
  scale_x = width;
  scale_y = height;
}

// Set translation
void DisplayService::setTranslation(const Uint32 x, const Uint32 y) {
  translation_x = x;
  translation_y = y;
}

// Set window
void DisplayService::setTitle(const std::string& title) {
  SDL_SetWindowTitle(window, title.c_str());
}

// Set display icon
void DisplayService::setIcon(const std::string& path) {
  SDL_Surface* icon = IMG_Load(path.c_str());
  if (!icon) {
    throw FileIOException("Could not load icon " + path);
  }
  SDL_SetWindowIcon(window, icon);
  SDL_FreeSurface(icon);
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
  display_mode = mode;

  // Resize window
  resize(window_w, window_h);

  // Create display
  window =
      SDL_CreateWindow("", SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
                       window_w, window_h, SDL_WINDOW_RESIZABLE);
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