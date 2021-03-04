#include "Engine.h"

#include "common/Exceptions.h"
#include "entities/ui/MessageBox.h"
#include "services/EventQueue.h"
#include "services/Locator.h"
#include "services/assets/AssetService.h"
#include "services/audio/DefaultAudioService.h"
#include "services/config/ConfigService.h"
#include "services/input/InputService.h"
#include "services/logging/DebugLoggingService.h"
#include "services/scene/SceneService.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#include <functional>
#endif

// Loop (emscripten compatibility)
#ifdef __EMSCRIPTEN__
EM_BOOL loop(double time, void* userData) {
  Locator::getEventQueue().process();
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
Engine::Engine() : closing(false) {
  // Setup engine
  setup();
}

// Shutdown engine
Engine::~Engine() {
  Locator::getEventQueue().unregisterService(this);

  SDL_Quit();
}

// Get the name of service
std::string Engine::getName() const {
  return "Engine Service";
}

// Start your engine!
void Engine::start() {
  try {
#ifdef __EMSCRIPTEN__
    emscripten_request_animation_frame_loop(loop, 0);
#else
    // Loop
    while (!closing) {
      Locator::getEventQueue().process();
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
void Engine::notify(const SDL_Event& event) {
  // Exit
  if (event.type == SDL_QUIT) {
    closing = true;
  }
}

// Sets up game
void Engine::setup() {
  // Init allegro 5
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
    throw InitException("Could not init sdl");
  }

  // Setup logger
  Locator::provideLogging<DebugLoggingService>();

  // Setup event queue
  Locator::provideEventQueue<EventQueue>();

  // Setup display
  Locator::provideDisplay<DisplayService>();

  // Setup service locator
  Locator::provideAudio<DefaultAudioService>();

  // Setup asset manager
  Locator::provideAsset<AssetService>();

  // Setup setting manager
  Locator::provideConfig<ConfigService>();

  // Setup input
  Locator::provideInput<InputService>();

  // Setup scene manager
  Locator::provideScene<SceneService>();

  // Register self with event queue
  Locator::getEventQueue().registerService(this);
}
