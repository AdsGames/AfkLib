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
#include "components/Sprite.h"
#include "components/Transform.h"
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

      // Render system
      if (hasComponent<Sprite>(obj->id)) {
        Sprite& sprite = getComponent<Sprite>(obj->id);
        Transform& transform = getComponent<Transform>(obj->id);

        // Draw image
        sprite.texture.drawEx(transform.x, transform.y, transform.width,
                              transform.height, transform.angle);
      }
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
  if (remove_pool.size() > 0) {
    for (auto& elem : remove_pool) {
      logger.log("Removing ID: " + std::to_string(elem));
    }

    for (const auto& obj_id : remove_pool) {
      // Get vector index
      unsigned int entity_index = entity_map[obj_id];

      // Remove from lookup map
      entity_map.erase(obj_id);

      // Erase game object while keeping most indicies correct
      entities[entity_index] = std::move(entities.back());
      entities.pop_back();

      // Update moved index
      if (entities.size() > 0) {
        auto& moved_obj = *entities[entity_index];
        entity_map[moved_obj.id] = entity_index;
      }

      // Erase components
      for (auto& comp_entry : component_map) {
        removeComponentById(obj_id, comp_entry.first);
      }
    }

    // Clear remove pool
    remove_pool.clear();
  }

  // Sort sprites
  if (need_sort) {
    const std::size_t id = typeid(Sprite).hash_code();

    // std::sort(components[id].begin(), components[id].end(), [](auto& c1,
    // auto& c2) {
    //   return obj1->transform.z < obj2->transform.z;
    // });
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

// Remove component by type id
void Scene::removeComponentById(const ObjId obj_id, const std::size_t id) {
  // Check has
  if (component_map[id].count(obj_id) > 0) {
    // Copy index
    int comp_index = component_map[id][obj_id];

    // Erase from map
    component_map[id].erase(obj_id);

    // Erase component
    components[id][comp_index] = std::move(components[id].back());
    components[id].pop_back();

    // Update moved index
    if (components[id].size() > 0) {
      component_map[id][obj_id] = comp_index;
    }
  }
}

}  // namespace afk
