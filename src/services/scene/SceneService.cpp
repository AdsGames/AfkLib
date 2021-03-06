#include "services/scene/SceneService.h"

#include <algorithm>

#include "common/Exceptions.h"
#include "scene/Scene.h"
#include "services/Services.h"

namespace afk {

// Update ticks per second
const Uint32 MS_PER_UPDATE = 50;

// Register events
SceneService::SceneService() {
  // Register timer events
  update_timer = Services::getEventQueue().registerTimer(MS_PER_UPDATE, 1);

  // Register self
  Services::getEventQueue().registerService(this);
}

// Unregister events
SceneService::~SceneService() {
  // Unregister self
  Services::getEventQueue().unregisterService(this);

  // Remove timer
  Services::getEventQueue().unregisterTimer(update_timer);
}

// Get the name of service
std::string SceneService::getName() const {
  return "Scene Service";
}

// Process event notification
void SceneService::notify(const SDL_Event& event) {
  // Update timer
  if (event.type == SDL_USEREVENT && event.user.code == 1) {
    // Change scene (if needed)
    changeScene();

    // Update scene
    if (current_scene) {
      current_scene->update();
      current_scene->updateInternal();
    }
  }
}

// Get scene
afk::Scene* SceneService::getSceneService() {
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
    throw SceneLookupException("Scene not found" + next_scene);
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

}