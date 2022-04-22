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
#include "../include/components/Sprite.h"
#include "../include/components/Transform.h"
#include "../include/scene/Scene.h"
#include "../include/services/Services.h"

class DemoScene : public afk::Scene {
 public:
  void start() {
    logger.log("Starting!");

    display.setWindowSize(512, 512);
    display.setBufferSize(512, 512);
    display.setMode(afk::DisplayMode::WINDOWED);
    display.setTitle("ex_mouse");

    assets.loadImage("lenna", "assets/lenna.png");

    lennaId = createEntity();
    createComponent<afk::Sprite>(lennaId, "lenna");
    createComponent<afk::Transform>(lennaId, afk::Vec3(100, 100, 0),
                                    afk::Vec2(30, 30));
  }

  void update(Uint32 delta) {
    Scene::update(delta);

    auto& transform = getComponent<afk::Transform>(lennaId);

    if (input.mouseDown(afk::MouseButtons::LEFT)) {
      transform.position.x = input.mouseX();
      transform.position.y = input.mouseY();
    }
    if (input.mouseDown(afk::MouseButtons::RIGHT)) {
      transform.size.x = input.mouseX();
      transform.size.y = input.mouseY();
    }
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
