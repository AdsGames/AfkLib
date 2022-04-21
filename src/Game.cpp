/**
 * @file Game.cpp
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Implementation of Game
 * @version 0.1
 * @date 2020-11-07
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "Game.h"

#include "common/Exceptions.h"
#include "entities/ui/MessageBox.h"
#include "random/RandomGenerator.h"
#include "services/Services.h"

#ifdef __EMSCRIPTEN__
#include <emscripten.h>
#include <emscripten/html5.h>
#endif

namespace afk {

// Loop (emscripten compatibility)
#ifdef __EMSCRIPTEN__
void loop() {
  // Process events
  Services::getEventQueue().process();

  // Process logic
  Services::getInputService().update();
  Services::getSceneService().update();

  // Draw
  Services::getSceneService().draw();
}
#endif

// Exit helper
void showErrorDialog(const std::string& title,
                     const std::string& message = "") {
  MessageBox error(MessageBoxType::ERROR);
  error.setTitle(title);
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
    emscripten_set_main_loop(loop, 0, 1);
#else
    float timeDelta = 1000.0f / 30.0f;
    float timeAcc = 0.0f;
    Uint32 startTime = 0;

    // Loop
    while (!closing) {
      // Add dt to acc
      startTime = SDL_GetTicks();

      // Process events
      Services::getEventQueue().process();

      // Process logic
      while (timeAcc >= timeDelta) {
        Services::getInputService().update();
        Services::getSceneService().update();
        timeAcc -= timeDelta;
      }

      // Draw
      Services::getSceneService().draw();

      // Inc accumulator
      timeAcc += SDL_GetTicks() - startTime;
    }
#endif
  } catch (const FileIOException& e) {
    showErrorDialog("File Error", e.what());
  } catch (const std::runtime_error& e) {
    showErrorDialog("Runtime Error", e.what());
  } catch (const std::exception& e) {
    showErrorDialog("Exception", e.what());
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
  // Init SDL2
  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_TIMER) < 0) {
    throw InitException("Could not init sdl");
  }

  // Register self with event queue
  Services::getEventQueue().registerService(this);
}

}  // namespace afk
