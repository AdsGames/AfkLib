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
#include "../include/entities/ui/Label.h"
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

    auto& lenna_1 = add<afk::GameObject>(*this, 10, 10);
    addComponent<afk::Sprite>(lenna_1.id);
    auto& lenna_1_sprite = getComponent<afk::Sprite>(lenna_1.id);
    lenna_1_sprite.texture = assets.getImage("lenna");
    addComponent<afk::Collider>(lenna_1.id);
    lenna_1.transform.width = 40;
    lenna_1.transform.height = 40;
    lenna_1_id = lenna_1.id;

    auto& lenna_2 = add<afk::GameObject>(*this, 10, 80);
    addComponent<afk::Sprite>(lenna_2.id);
    auto& lenna_2_sprite = getComponent<afk::Sprite>(lenna_2.id);
    lenna_2_sprite.texture = assets.getImage("lenna");
    addComponent<afk::Collider>(lenna_2.id);
    lenna_2.transform.width = 40;
    lenna_2.transform.height = 40;
    lenna_2_id = lenna_2.id;

    auto& label = add<afk::Label>(*this, 0, 0);
    label.setFont("freesans");
    label_id = label.id;
  }

  void update(Uint32 delta) {
    auto& label = get<afk::Label>(label_id);
    auto& lenna_1 = get(lenna_1_id);
    auto& lenna_2 = get(lenna_2_id);

    if (input.mouseDown(afk::MouseButtons::LEFT)) {
      lenna_1.transform.x = input.mouseX();
      lenna_1.transform.y = input.mouseY();
    }

    if (input.mouseDown(afk::MouseButtons::RIGHT)) {
      lenna_2.transform.x = input.mouseX();
      lenna_2.transform.y = input.mouseY();
    }

    auto& collider = getComponent<afk::Collider>(lenna_1_id);
    if (collider.collisions.size() > 0) {
      label.setText("Colliding!");
    } else {
      label.setText("Not colliding");
    }

    Scene::update(delta);
  }

  void stop() { logger.log("Stopping!"); }

 private:
  ObjId lenna_1_id;
  ObjId lenna_2_id;
  ObjId label_id;
};

int main(int argv, char** args) {
  afk::Game game = afk::Game();

  afk::SceneService& scenes = afk::Services::getSceneService();
  scenes.addScene<DemoScene>("demo");
  scenes.setNextScene("demo");

  game.start();
  return 0;
}
