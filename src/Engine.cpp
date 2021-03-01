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

// Start your engine!
void Engine::start() {
  try {
    // Loop
    while (!closing) {
      Locator::getEventQueue().process();
    }
  } catch (const FileIOException& e) {
    showErrorDialog("File Error", e.what());
  } catch (const std::runtime_error& e) {
    showErrorDialog("Runtime Error", e.what());
  } catch (...) {
    showErrorDialog("Unknown Error", "An unknown error has occured :(");
  }
}

// Get event notification
void Engine::notify(const ALLEGRO_EVENT& event) {
  // Exit
  if (event.type == ALLEGRO_EVENT_DISPLAY_CLOSE) {
    closing = true;
  }
}

// Sets up game
void Engine::setup() {
  // Init allegro 5
  if (!al_init()) {
    throw InitException("Could not init allegro");
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
