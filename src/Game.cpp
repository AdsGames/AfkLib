#include "Game.h"

#include "common/Exceptions.h"
#include "entities/ui/MessageBox.h"
#include "services/Services.h"
#include "services/assets/AssetService.h"
#include "services/audio/DefaultAudioService.h"
#include "services/config/ConfigService.h"
#include "services/events/EventQueue.h"
#include "services/input/InputService.h"
#include "services/logging/DebugLoggingService.h"
#include "services/scene/SceneService.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#include <functional>
#endif

namespace afk {

// Loop (emscripten compatibility)
#ifdef __EMSCRIPTEN__
EM_BOOL loop(double time, void* userData) {
  Services::getEventQueue().process();
  return EM_FALSE;
}
#endif

// Exit helper
void showErrorDialog(const std::string& title,
                     const std::string& message = "") {
  MessageBox error(ERROR);
  error.setTitle(title);
  error.setHeading(title);
  error.setText(message);
  error.show();
}

// Setup engine
Game::Game() : closing(false) {
  // Setup engine
  setup();
}

// Shutdown engine
Game::~Game() {
  Services::getEventQueue().unregisterService(this);

  SDL_Quit();
}

// Get the name of service
std::string Game::getName() const {
  return "Game Service";
}

// Start your engine!
void Game::start() {
  try {
#ifdef __EMSCRIPTEN__
    emscripten_request_animation_frame_loop(loop, 0);
#else
    // Loop
    while (!closing) {
      Services::getEventQueue().process();
    }
#endif
  } catch (const FileIOException& e) {
    showErrorDialog("File Error", e.what());
  } catch (const std::runtime_error& e) {
    showErrorDialog("Runtime Error", e.what());
  } catch (...) {
    showErrorDialog("Unknown Error", "An unknown error has occured :(");
  }
}

// Get event notification
void Game::notify(const SDL_Event& event) {
  // Exit
  if (event.type == SDL_QUIT) {
    closing = true;
  }
}

// Sets up game
void Game::setup() {
  // Init allegro 5
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
    throw InitException("Could not init sdl");
  }

  // Setup logger
  Services::provideLoggingService<DebugLoggingService>();

  // Setup event queue
  Services::provideEventQueue<EventQueue>();

  // Setup display
  Services::provideDisplayService<DisplayService>();

  // Setup service locator
  Services::provideAudioService<DefaultAudioService>();

  // Setup asset manager
  Services::provideAssetService<AssetService>();

  // Setup setting manager
  Services::provideConfigService<ConfigService>();

  // Setup input
  Services::provideInputService<InputService>();

  // Setup scene manager
  Services::provideSceneService<SceneService>();

  // Register self with event queue
  Services::getEventQueue().registerService(this);
}

}