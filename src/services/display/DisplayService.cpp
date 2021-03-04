#include "services/display/DisplayService.h"

#include <SDL2/SDL_image.h>

#include "common/Exceptions.h"
#include "scene/Scene.h"

#include "color/Color.h"
#include "services/Locator.h"

// Draw ticks per second
const Uint32 MS_PER_DRAW = 17;

// Setup DisplayService
DisplayService::DisplayService() {
  // Register timer events
  draw_timer = Locator::getEventQueue().registerTimer(MS_PER_DRAW, 0);

  // Register self
  Locator::getEventQueue().registerService(this);

  // Set initial time
  old_time = SDL_GetTicks();
}

// Cleanup window
DisplayService::~DisplayService() {
  // Unregister self
  Locator::getEventQueue().unregisterService(this);

  // Remove timer
  Locator::getEventQueue().unregisterTimer(draw_timer);

  // Cleanup
  if (window) {
    SDL_DestroyWindow(window);
  }

  if (renderer) {
    SDL_DestroyRenderer(renderer);
  }
}

// Get the name of service
std::string DisplayService::getName() const {
  return "Display Service";
}

// Notify
void DisplayService::notify(const SDL_Event& event) {
  if (event.type == SDL_DISPLAYEVENT) {
    // resize(event.display.width, event.display.height);
  } else if (event.type == SDL_USEREVENT && event.user.code == 0) {
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
  SDL_ShowCursor(false);
}

// Show mouse on display
void DisplayService::showMouse() {
  SDL_ShowCursor(true);
}

// Resize window
void DisplayService::resize(const unsigned int window_w,
                            const unsigned int window_h) {
  // Get monitor width
  SDL_DisplayMode info;
  SDL_GetCurrentDisplayMode(0, &info);

  // Window mode
  switch (display_mode) {
    // Fullscreen windowed stretch
    case DISPLAY_MODE::FULLSCREEN_WINDOW_STRETCH:
      // Set flags
      SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

      // Set up screen size and positions
      setWindowSize(info.w, info.h);
      setScale((float)window_w / draw_w, (float)window_h / draw_h);
      setTranslation(0.0f, 0.0f);

      break;

    // Fullscreen window center
    case DISPLAY_MODE::FULLSCREEN_WINDOW_CENTER:
      // Set flags
      SDL_SetWindowFullscreen(window, SDL_WINDOW_FULLSCREEN);

      // Set up screen size and positions
      setWindowSize(info.w, info.h);
      setScale(1.0f, 1.0f);
      setTranslation((window_w - scale_x * draw_w) / 2,
                     (window_h - scale_y * draw_h) / 2);

      break;

    // Fullscreen window center
    case DISPLAY_MODE::FULLSCREEN_WINDOW_LETTERBOX:
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
    case DISPLAY_MODE::WINDOWED:
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
void DisplayService::setMode(const DISPLAY_MODE mode) {
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

  renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);
  if (!renderer) {
    throw InitException("Could not create renderer");
  }
}

void DisplayService::draw(Scene* current_scene) {
  if (!window || !renderer) {
    return;
  }

  // Render a frame
  SDL_SetRenderDrawColor(renderer, 255, 255, 255, 255);
  SDL_RenderClear(renderer);

  current_scene->drawInternal();
  current_scene->draw();

  // Flip
  SDL_RenderPresent(renderer);

  // Shift fps buffer
  for (unsigned int i = FRAME_BUFFER_SIZE - 1; i > 0; i--) {
    frames_array[i] = frames_array[i - 1];
  }

  frames_array[0] = (1.0 / (SDL_GetTicks() - old_time));
  old_time = SDL_GetTicks();

  unsigned int fps_total = 0;

  for (unsigned int i = 0; i < FRAME_BUFFER_SIZE; i++) {
    fps_total += frames_array[i];
  }

  // FPS = average
  fps = fps_total / FRAME_BUFFER_SIZE;
}
