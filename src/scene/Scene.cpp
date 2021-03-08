#include "scene/Scene.h"

#include <algorithm>

#include "entities/GameObject.h"

namespace afk {

// Internal cleanup (on switch scene)
void Scene::stopInternal() {
  update_pool.clear();
  lookup_map.clear();
  collider_map.clear();
}

// Draw internal method
void Scene::drawInternal() {
  // Draw
  for (auto& obj : update_pool) {
    obj->draw();
  }
}

// Internal update method
void Scene::updateInternal() {
  // Update all
  for (unsigned int i = 0; i < update_pool.size(); i++) {
    GameObject& obj = *update_pool.at(i);

    // Update
    obj.update();

    // Get id
    const int id = obj.getId();

    // Collisions
    if (collider_map.count(id) > 0) {
      // Go through each id
      for (const int otherId : collider_map[id]) {
        // Get other
        GameObject& other = *update_pool.at(lookup_map[otherId]);
        if (obj.colliding(other)) {
          obj.onCollide(other);
          other.onCollide(obj);
        }
      }
    }
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
    const int id = update_pool.at(i)->getId();
    lookup_map[id] = i;
  }
}

}  // namespace afk
