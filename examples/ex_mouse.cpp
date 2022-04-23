/**
 * @file ex_mouse.cpp
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
#include "../include/entities/Entity.h"
#include "../include/scene/Scene.h"

class DemoScene : public afk::Scene {
 public:
  void start() override {
    logger.log("Starting!");

    display.setWindowSize(512, 512);
    display.setBufferSize(512, 512);
    display.setMode(afk::DisplayMode::Windowed);
    display.setTitle("ex_mouse");

    assets.loadImage("lenna", "assets/lenna.png");

    lennaEntity = createEntity();
    createComponent<afk::Sprite>(lennaEntity, "lenna");
    createComponent<afk::Transform>(lennaEntity, afk::Vec3(100, 100, 0),
                                    afk::Vec2(30, 30));
  }

  void update(uint32_t delta) override {
    Scene::update(delta);

    auto& transform = getComponent<afk::Transform>(lennaEntity);

    if (input.mouseDown(afk::MouseButtons::Left)) {
      transform.position.x = input.mouseX();
      transform.position.y = input.mouseY();
    }
    if (input.mouseDown(afk::MouseButtons::Right)) {
      transform.size.x = input.mouseX();
      transform.size.y = input.mouseY();
    }
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
