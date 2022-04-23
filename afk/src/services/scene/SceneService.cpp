/**
 * @file SceneService.cpp
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Implementation of SceneService
 * @version 0.1
 * @date 2020-11-28
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "services/scene/SceneService.h"

#include <algorithm>

#include "common/Exceptions.h"
#include "scene/Scene.h"

namespace afk {

// Register events
SceneService::SceneService()
    : currentScene(nullptr), lastTick(SDL_GetTicks()) {}

// Unregister events
SceneService::~SceneService() = default;

// Update scene
void SceneService::update() {
  // Change scene (if needed)
  changeScene();

  // Update scene
  if (currentScene) {
    uint32_t delta = SDL_GetTicks() - lastTick;
    currentScene->update(delta);
  }

  lastTick = SDL_GetTicks();
}

// Update scene
void SceneService::draw() {
  Services::getDisplayService().draw(currentScene);
}

// Get scene
Scene* SceneService::getSceneService() {
  return this->currentScene;
}

// Change game screen
void SceneService::changeScene() {
  // If the scene needs not to be changed
  if (nextScene.empty()) {
    return;
  }

  // Cleanup current scene
  if (currentScene) {
    currentScene->stop();
    currentScene->stopInternal();
  }

  // Find scene
  auto it = std::find_if(
      scenes.begin(), scenes.end(),
      [this](const SceneType& scene) { return scene.sceneId == nextScene; });

  // Dad not found
  if (it == scenes.end()) {
    throw SceneLookupException("Scene not found (" + nextScene + ")");
  }

  // Create scene
  currentScene = (*it).scene;
  currentScene->start();

  // Change the current scene ID
  sceneId = nextScene;

  // NULL the next scene ID
  nextScene = "";
}

// Set next scene to load
void SceneService::setNextScene(const std::string& sceneId) {
  // If the user doesn't want to exit
  if (nextScene != "exit") {
    // Set the next scene
    nextScene = sceneId;
  }
}

}  // namespace afk
