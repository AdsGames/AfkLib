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

#include "systems/CollisionSystem.h"
#include "systems/ParticleSystem.h"
#include "systems/PhysicsSystem.h"
#include "systems/RenderSystem.h"
#include "systems/UISystem.h"

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

// Internal update method
void Scene::update(Uint32 delta) {
  systems::collisionSystem(registry);
  systems::physicsSystem(registry, delta);
  systems::particleSystem(registry, delta);
}

// Draw internal method
void Scene::draw() {
  // Draw
  systems::renderSystem(registry, assets);
  systems::uiSystem(registry, assets);
  systems::particleRenderSystem(registry, assets);
}

// Internal cleanup (on switch scene)
void Scene::stopInternal() {
  // entities.clear();
}

// Register a new entity
entity Scene::createEntity() {
  return registry.create();
}

// Remove an entity
void Scene::destroyEntity(entity entity) {
  registry.destroy(entity);
}

// Get a reference to the registry
registry& Scene::getRegistry() {
  return registry;
}

}  // namespace afk
