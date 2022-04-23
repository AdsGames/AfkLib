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
#include "../include/components/components.h"
#include "../include/entities/Entity.h"
#include "../include/scene/Scene.h"

void bounceSystem(afk::Registry& registry) {
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
  void start() override {
    logger.log("Starting!");

    display.setWindowSize(512, 512);
    display.setBufferSize(512, 512);
    display.setMode(afk::DisplayMode::Windowed);
    display.setTitle("ex_physics");

    assets.loadImage("lenna", "assets/lenna.png");

    lennaEntity = createEntity();
    createComponent<afk::Sprite>(lennaEntity, "lenna");
    createComponent<afk::Transform>(lennaEntity, afk::Vec3(0, 0, 0),
                                    afk::Vec2(40, 40));
    createComponent<afk::Physics>(lennaEntity, afk::Vec2(100.0f, 400.0f));
  }

  void update(uint32_t delta) override {
    Scene::update(delta);
    bounceSystem(getRegistry());
  }

  void stop() override { logger.log("Stopping!"); }

 private:
  afk::Entity lennaEntity;
};

int main(int argv, char** args) {
  afk::Game game = afk::Game();

  afk::SceneService& scenes = afk::Services::getSceneService();
  scenes.addScene<DemoScene>("demo");
  scenes.setNextScene("demo");

  game.start();

  return 0;
}
