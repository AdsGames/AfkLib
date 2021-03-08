/**
 * @file ex_sound.cpp
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
    assets.loadAudio("win", "assets/win.wav");
  }

  void draw() {}

  void update() {
    if (input.mousePressed(afk::MouseButtons::LEFT)) {
      audio.playSound("win", {127, 0, 1.0f, false});
    }
  }

  void stop() { logger.log("Stopping!"); }
};

int main(int argv, char** args) {
  afk::Game game = afk::Game();

  afk::SceneService& scenes = afk::Services::getSceneService();
  scenes.addScene<DemoScene>("demo");
  scenes.setNextScene("demo");

  game.start();
  return 0;
}
