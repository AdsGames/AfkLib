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
  entities.clear();
  entity_map.clear();
}

// Draw internal method
void Scene::draw() {
  // Draw
  for (auto& obj : entities) {
    if (obj->getVisible() && obj->getHooked()) {
      obj->draw();
    }
  }
}

// Internal update method
void Scene::update(Uint32 delta) {
  // Update all (we need to indices here since updates can add objects)
  for (Uint32 i = 0; i < entities.size(); ++i) {
    if (entities.at(i)->getEnabled() && entities.at(i)->getHooked()) {
      entities.at(i)->update(delta);
    }
  }

  // Internal updates
  for (auto& obj : entities) {
    obj->updateInternal();
  }

  // Remove any game objects that need to be cleaned up
  for (auto& id : remove_pool) {
    // Get vector index
    auto index = entity_map.at(id);

    // Erase game object
    entities.erase(entities.begin() + index);

    // Remove from lookup map
    entity_map.erase(id);

    // We will need a sort after this
    need_sort = true;
  }

  // Clear remove pool
  remove_pool.clear();

  // Sort flag toggled
  if (need_sort) {
    // Z sort, use defined < operator
    std::sort(entities.begin(), entities.end(),
              [](std::unique_ptr<afk::GameObject>& obj1,
                 std::unique_ptr<afk::GameObject>& obj2) -> bool {
                return obj1->transform.z < obj2->transform.z;
              });

    // Repopulate lookup map
    for (unsigned int i = 0; i < entities.size(); i++) {
      entity_map[entities.at(i)->id] = i;
    }

    // Done sorting
    need_sort = false;
  }
}

// Remove game object from scene
void Scene::remove(const ObjId id) {
  remove_pool.push_back(id);
}

// Check if obj id exists in scene
bool Scene::has(const ObjId id) {
  return entity_map.count(id) == 1;
}

}  // namespace afk
