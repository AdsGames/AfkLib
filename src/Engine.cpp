#include "Engine.h"

#include "EventQueue.h"
#include "Locator.h"
#include "assets/AssetManager.h"
#include "audio/DefaultAudioService.h"
#include "common/Exceptions.h"
#include "input/Input.h"
#include "logging/DebugLogger.h"
#include "scene/SceneManager.h"
#include "settings/SettingManager.h"
#include "ui/MessageBox.h"

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
  Locator::provideLogger<DebugLogger>();

  // Setup event queue
  Locator::provideEventQueue<EventQueue>();

  // Setup window
  Locator::provideWindow<Window>();

  // Setup service locator
  Locator::provideAudio<DefaultAudioService>();

  // Setup asset manager
  Locator::provideAssetManager<AssetManager>();

  // Setup setting manager
  Locator::provideSettings<SettingManager>();

  // Setup input
  Locator::provideInput<Input>();

  // Setup scene manager
  Locator::provideSceneManager<SceneManager>();

  // Register self with event queue
  Locator::getEventQueue().registerService(this);
}
