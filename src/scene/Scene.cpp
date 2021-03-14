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

#include "common/Exceptions.h"
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
      config(afk::Services::getConfigService()),
      need_sort(false) {}

// Internal cleanup (on switch scene)
void Scene::stopInternal() {
  update_pool.clear();
  lookup_map.clear();
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
  // Update all (we need to indices here since updates can add objects)
  for (Uint32 i = 0; i < update_pool.size(); ++i) {
    if (update_pool.at(i)->getEnabled() && update_pool.at(i)->getHooked()) {
      update_pool.at(i)->update(delta);
    }
  }

  // Internal updates
  for (auto& obj : update_pool) {
    obj->updateInternal();
  }

  // Remove any game objects that need to be cleaned up
  for (auto& id : remove_pool) {
    // Get vector index
    auto index = lookup_map.at(id);

    // Erase game object
    update_pool.erase(update_pool.begin() + index);

    // Remove from lookup map
    lookup_map.erase(id);

    // We will need a sort after this
    need_sort = true;
  }

  // Clear remove pool
  remove_pool.clear();

  // Sort flag toggled
  if (need_sort) {
    // Z sort, use defined < operator
    std::sort(update_pool.begin(), update_pool.end(),
              [](auto& obj1, auto& obj2) -> bool { return *obj1 < *obj2; });

    // Repopulate lookup map
    for (unsigned int i = 0; i < update_pool.size(); i++) {
      lookup_map[update_pool.at(i)->id] = i;
    }

    // Done sorting
    need_sort = false;
  }
}

// Remove game object from scene
void Scene::remove(const ObjId id) {
  remove_pool.push_back(id);
}

}  // namespace afk
