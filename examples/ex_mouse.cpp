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
#include "../include/entities/Sprite.h"
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

    afk::Sprite& lenna = addObj<afk::Sprite>(*this, "lenna");

    lenna.setSize(30, 30);
    lenna.setPosition(100, 100);
    lennaId = lenna.getId();
  }

  void draw() {}

  void update() {
    afk::Sprite& lenna = get<afk::Sprite>(lennaId);

    if (input.mousePressed(afk::MouseButtons::LEFT)) {
      lenna.setPosition(input.mouseX(), input.mouseY());
    }
    if (input.mouseDown(afk::MouseButtons::RIGHT)) {
      lenna.setSize(input.mouseX(), input.mouseY());
    }
  }

  void stop() { logger.log("Stopping!"); }

 private:
  ObjId lennaId;
};

int main(int argv, char** args) {
  afk::Game game = afk::Game();

  afk::SceneService& scenes = afk::Services::getSceneService();
  scenes.addScene<DemoScene>("demo");
  scenes.setNextScene("demo");

  game.start();
  return 0;
}
