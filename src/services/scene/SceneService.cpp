#include "services/scene/SceneService.h"

#include <algorithm>

#include "common/Exceptions.h"
#include "scene/Scene.h"
#include "services/Locator.h"

// Update ticks per second
const float UPDATES_PER_SECOND = 20;

// Register events
SceneService::SceneService() {
  Locator::getLogger().log("[Scene Service]: Starting up");

  // Create timer
  update_timer = al_create_timer(1.0 / UPDATES_PER_SECOND);
  al_start_timer(update_timer);

  // Register timer events
  Locator::getEventQueue().registerSource(
      al_get_timer_event_source(update_timer));

  // Register self
  Locator::getEventQueue().registerService(this);
}

// Unregister events
SceneService::~SceneService() {
  Locator::getLogger().log("[Scene Service]: Shutting down");

  // Unregister self
  Locator::getEventQueue().unregisterService(this);
}

// Process event notification
void SceneService::notify(const ALLEGRO_EVENT& event) {
  // Update timer
  if (event.type == ALLEGRO_EVENT_TIMER && event.timer.source == update_timer) {
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
Scene* SceneService::getScene() {
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

// Get the update timer (useful for checking if timer event is from here)
ALLEGRO_TIMER* SceneService::getUpdateTimer() {
  return update_timer;
}