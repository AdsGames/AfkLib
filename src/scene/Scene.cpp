/**
 * @file Scene.cpp
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Implementation of Scene class
 * @version 0.1
 * @date 2016-12-30
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "scene/Scene.h"

#include <algorithm>

#include "entities/GameObject.h"

namespace afk {

// Constructor
Scene::Scene()
    : audio(afk::Services::getAudioService()),
      logger(afk::Services::getLoggingService()),
      display(afk::Services::getDisplayService()),
      assets(afk::Services::getAssetService()),
      input(afk::Services::getInputService()),
      scene(afk::Services::getSceneService()),
      config(afk::Services::getConfigService()) {}

// Internal cleanup (on switch scene)
void Scene::stopInternal() {
  update_pool.clear();
  lookup_map.clear();
  collider_map.clear();
}

// Draw internal method
void Scene::draw() {
  // Draw
  for (auto& obj : update_pool) {
    if (obj->getVisible() && obj->getHooked()) {
      obj->draw();
    }
  }
}

// Internal update method
void Scene::update(Uint32 delta) {
  // Update all
  for (auto& obj : update_pool) {
    if (obj->getEnabled() && obj->getHooked()) {
      obj->update(delta);
    }
  }

  // Internal updates
  for (auto& obj : update_pool) {
    obj->updateInternal();
  }
}

// Remove game object from scene
void Scene::remove(const ObjId id) {
  const unsigned int index = lookup_map.at(id);
  update_pool.erase(update_pool.begin() + index);
  sortGameObjects();
}

// Add collider between two game objects
void Scene::addCollider(const ObjId id1, const ObjId id2) {
  // Add collider 1
  if (collider_map.count(id1) > 0) {
    collider_map.at(id1).push_back(id2);
  } else {
    collider_map.at(id1) = std::vector<ObjId>(id2);
  }

  // Add collider 2
  if (collider_map.count(id2) > 0) {
    collider_map.at(id2).push_back(id1);
  } else {
    collider_map.at(id2) = std::vector<ObjId>(id1);
  }
}

// Sort game objects by Z
void Scene::sortGameObjects() {
  // Z sort, use defined < operator
  std::sort(update_pool.begin(), update_pool.end(),
            [](auto& obj1, auto& obj2) -> bool { return *obj1 < *obj2; });

  // Erase map
  lookup_map.clear();

  // Update lookup map
  for (unsigned int i = 0; i < update_pool.size(); i++) {
    const int id = update_pool.at(i)->id;
    lookup_map[id] = i;
  }
}

}  // namespace afk
