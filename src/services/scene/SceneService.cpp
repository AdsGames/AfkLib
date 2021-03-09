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
#include "services/Services.h"

namespace afk {

// Register events
SceneService::SceneService()
    : current_scene(nullptr),
      scene_id(""),
      next_scene(""),
      last_tick(SDL_GetTicks()) {}

// Unregister events
SceneService::~SceneService() {}

// Update scene
void SceneService::update() {
  // Change scene (if needed)
  changeScene();

  // Update scene
  if (current_scene) {
    Uint32 delta = SDL_GetTicks() - last_tick;
    current_scene->update(delta);
    current_scene->updateInternal(delta);
  }

  last_tick = SDL_GetTicks();
}

// Update scene
void SceneService::draw() {
  Services::getDisplayService().draw(current_scene);
}

// Get scene
Scene* SceneService::getSceneService() {
  return this->current_scene;
}

// Change game screen
void SceneService::changeScene() {
  // If the scene needs not to be changed
  if (next_scene == "") {
    return;
  }

  // Cleanup current scene
  if (current_scene) {
    current_scene->stop();
    current_scene->stopInternal();
  }

  // Find scene
  auto it = std::find_if(
      scenes.begin(), scenes.end(),
      [this](const SceneType& scene) { return scene.scene_id == next_scene; });

  // Dad not found
  if (it == scenes.end()) {
    throw SceneLookupException("Scene not found (" + next_scene + ")");
  }

  // Create scene
  current_scene = (*it).scene;
  current_scene->start();

  // Change the current scene ID
  scene_id = next_scene;

  // NULL the next scene ID
  next_scene = "";
}

// Set next scene to load
void SceneService::setNextScene(const std::string& scene_id) {
  // If the user doesn't want to exit
  if (next_scene != "exit") {
    // Set the next scene
    next_scene = scene_id;
  }
}

}  // namespace afk
