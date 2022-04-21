/**
 * @file ex_physics.cpp
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Demonstrates usage of physics component
 * @version 0.1
 * @date 2022-04-20
 *
 * @copyright Copyright (c) 2022
 *
 */
#include "../include/Game.h"
#include "../include/common/Vec.h"
#include "../include/components/Physics.h"
#include "../include/components/Sprite.h"
#include "../include/components/Transform.h"
#include "../include/scene/Scene.h"

void bounceSystem(entt::registry& registry) {
  auto view = registry.view<const afk::Transform, afk::Physics>();

  for (auto [entity, transform, physics] : view.each()) {
    if (transform.position.x > 512 - transform.size.x) {
      physics.velocity.x *= -1;
    }
    if (transform.position.y > 512 - transform.size.y) {
      physics.velocity.y *= -1;
    }
    if (transform.position.x < 0) {
      physics.velocity.x *= -1;
    }
    if (transform.position.y < 0) {
      physics.velocity.y *= -1;
    }
  }
}

class DemoScene : public afk::Scene {
 public:
  void start() {
    logger.log("Starting!");

    display.setWindowSize(512, 512);
    display.setBufferSize(512, 512);
    display.setMode(afk::DisplayMode::WINDOWED);
    display.setTitle("ex_physics");

    assets.loadImage("lenna", "assets/lenna.png");

    lennaId = createEntity();
    createComponent<afk::SpriteComponent>(lennaId, "lenna");
    createComponent<afk::Transform>(lennaId, afk::Vec3(0, 0, 0),
                                    afk::Vec2(40, 40));
    createComponent<afk::Physics>(lennaId, afk::Vec2(100.0f, 400.0f));
  }

  void update(Uint32 delta) {
    Scene::update(delta);
    bounceSystem(getRegistry());
  }

  void stop() { logger.log("Stopping!"); }

 private:
  entt::entity lennaId;
};

int main(int argv, char** args) {
  afk::Game game = afk::Game();

  afk::SceneService& scenes = afk::Services::getSceneService();
  scenes.addScene<DemoScene>("demo");
  scenes.setNextScene("demo");

  game.start();

  return 0;
}
