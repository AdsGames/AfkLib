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
#include "../include/scene/Scene.h"

class DemoScene : public afk::Scene {
 public:
  void start() override {
    logger.log("Starting!");
    display.setWindowSize(512, 512);
    display.setBufferSize(512, 512);
    display.setMode(afk::DisplayMode::Windowed);
    display.setTitle("ex_mouse");
    assets.loadAudio("win", "assets/win.wav");
  }

  void update(uint32_t delta) override {
    Scene::update(delta);

    if (input.mousePressed(afk::MouseButtons::Left)) {
      audio.playSound("win", 1.0f, 0.0f, 1.0f, false);
    }
  }

  void stop() override { logger.log("Stopping!"); }
};

int main(int argv, char** args) {
  afk::Game game = afk::Game();

  afk::SceneService& scenes = afk::Services::getSceneService();
  scenes.addScene<DemoScene>("demo");
  scenes.setNextScene("demo");

  game.start();
  return 0;
}
