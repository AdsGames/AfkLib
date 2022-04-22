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
#include "../include/components/Collider.h"
#include "../include/components/Sprite.h"
#include "../include/components/Transform.h"
#include "../include/components/ui/Label.h"
#include "../include/scene/Scene.h"
#include "../include/services/Services.h"

class DemoScene : public afk::Scene {
 public:
  void start() {
    logger.log("Starting!");

    display.setWindowSize(512, 512);
    display.setBufferSize(512, 512);
    display.setMode(afk::DisplayMode::WINDOWED);
    display.setTitle("ex_collision");

    assets.loadImage("lenna", "assets/lenna.png");
    assets.loadFont("freesans", "assets/freesans.ttf", 12);

    lenna_1_id = createEntity();
    createComponent<afk::Transform>(lenna_1_id, afk::Vec3(10, 10, 0),
                                    afk::Vec2(40, 40));
    createComponent<afk::Sprite>(lenna_1_id, "lenna");
    createComponent<afk::Collider>(lenna_1_id);

    lenna_2_id = createEntity();
    createComponent<afk::Transform>(lenna_2_id, afk::Vec3(10, 80, 0),
                                    afk::Vec2(40, 40));
    createComponent<afk::Sprite>(lenna_2_id, "lenna");
    createComponent<afk::Collider>(lenna_2_id);

    label_id = createEntity();
    createComponent<afk::Transform>(label_id, afk::Vec3(10, 5, 0));
    auto& label = createComponent<afk::Label>(label_id);
    label.setText("FPS");
    label.setFont("freesans");
  }

  void update(Uint32 delta) {
    auto& label = getComponent<afk::Label>(label_id);
    auto& lenna_1 = getComponent<afk::Transform>(lenna_1_id);
    auto& lenna_2 = getComponent<afk::Transform>(lenna_2_id);

    if (input.mouseDown(afk::MouseButtons::LEFT)) {
      lenna_1.position.x = input.mouseX();
      lenna_1.position.y = input.mouseY();
    }

    if (input.mouseDown(afk::MouseButtons::RIGHT)) {
      lenna_2.position.x = input.mouseX();
      lenna_2.position.y = input.mouseY();
    }

    auto& collider = getComponent<afk::Collider>(lenna_1_id);
    if (collider.colliding) {
      label.setText("Colliding!");
    } else {
      label.setText("Not colliding");
    }

    Scene::update(delta);
  }

  void stop() { logger.log("Stopping!"); }

 private:
  entt::entity lenna_1_id;
  entt::entity lenna_2_id;
  entt::entity label_id;
};

int main(int argv, char** args) {
  afk::Game game = afk::Game();

  afk::SceneService& scenes = afk::Services::getSceneService();
  scenes.addScene<DemoScene>("demo");
  scenes.setNextScene("demo");

  game.start();
  return 0;
}
