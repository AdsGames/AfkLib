/**
 * @file ex_sprite.cpp
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief
 * @version 0.1
 * @date 2021-03-08
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "../include/Game.h"
#include "../include/components/components.h"
#include "../include/components/ui.h"
#include "../include/entities/Entity.h"
#include "../include/scene/Scene.h"

class DemoScene : public afk::Scene {
 public:
  void start() override {
    logger.log("Starting!");

    display.setWindowSize(512, 512);
    display.setBufferSize(512, 512);
    display.setMode(afk::DisplayMode::Windowed);
    display.setTitle("ex_collision");

    auto& lennaTexture = assets.loadImage("lenna", "assets/lenna.png");
    assets.loadFont("freesans", "assets/freesans.ttf", 12);

    lennaEntity1 = createEntity();
    createComponent<afk::Transform>(lennaEntity1, afk::Vec3(10, 10, 0),
                                    afk::Vec2(40, 40));
    createComponent<afk::Sprite>(lennaEntity1, lennaTexture);
    createComponent<afk::Collider>(lennaEntity1);

    lennaEntity2 = createEntity();
    createComponent<afk::Transform>(lennaEntity2, afk::Vec3(10, 80, 0),
                                    afk::Vec2(40, 40));
    createComponent<afk::Sprite>(lennaEntity2, lennaTexture);
    createComponent<afk::Collider>(lennaEntity2);

    labelEntity = createEntity();
    createComponent<afk::Transform>(labelEntity, afk::Vec3(10, 5, 0));
    auto& label = createComponent<afk::Label>(labelEntity);
    label.font = "freesans";
  }

  void update(uint32_t delta) override {
    auto& label = getComponent<afk::Label>(labelEntity);
    auto& lennaTransform1 = getComponent<afk::Transform>(lennaEntity1);
    auto& lennaTransform2 = getComponent<afk::Transform>(lennaEntity2);

    if (input.mouseDown(afk::MouseButtons::Left)) {
      lennaTransform1.position.x = input.mouseX();
      lennaTransform1.position.y = input.mouseY();
    }

    if (input.mouseDown(afk::MouseButtons::Right)) {
      lennaTransform2.position.x = input.mouseX();
      lennaTransform2.position.y = input.mouseY();
    }

    auto& collider = getComponent<afk::Collider>(lennaEntity1);
    if (collider.colliding) {
      label.text = "Colliding!";
    } else {
      label.text = "Not colliding";
    }

    Scene::update(delta);
  }

  void stop() override { logger.log("Stopping!"); }

 private:
  afk::Entity lennaEntity1;
  afk::Entity lennaEntity2;
  afk::Entity labelEntity;
};

int main(int argv, char** args) {
  afk::Game game = afk::Game();

  afk::SceneService& scenes = afk::Services::getSceneService();
  scenes.addScene<DemoScene>("demo");
  scenes.setNextScene("demo");

  game.start();
  return 0;
}
