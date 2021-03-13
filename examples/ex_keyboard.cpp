/**
 * @file ex_keyboard.cpp
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

class Character : public afk::Sprite {
 public:
  Character(afk::Scene& scene, const float x, const float y)
      : Sprite(scene, x, y) {
    setTexture("lenna");
    setSize(30, 30);
  }

  void update(Uint32 delta) {
    Sprite::update(delta);

    float speed = delta / 10.0f;
    if (scene.input.keyDown(afk::Keys::UP)) {
      setPosition(x, y - speed);
    }
    if (scene.input.keyDown(afk::Keys::DOWN)) {
      setPosition(x, y + speed);
    }
    if (scene.input.keyDown(afk::Keys::LEFT)) {
      setPosition(x - speed, y);
    }
    if (scene.input.keyDown(afk::Keys::RIGHT)) {
      setPosition(x + speed, y);
    }
  }
};

class DemoScene : public afk::Scene {
 public:
  void start() {
    logger.log("Starting!");

    display.setWindowSize(512, 512);
    display.setBufferSize(512, 512);
    display.setMode(afk::DisplayMode::WINDOWED);
    display.setTitle("ex_keyboard");

    assets.loadImage("lenna", "assets/lenna.png");

    add<Character>(*this, 100, 100);
  }

  void stop() { logger.log("Stopping!"); }
};

class MainGame : public afk::Game {
 public:
  MainGame() : Game() {
    afk::SceneService& scene = afk::Services::getSceneService();
    scene.addScene<DemoScene>("demo");
    scene.setNextScene("demo");

    start();
  }
};

int main(int argv, char** args) {
  MainGame game = MainGame();

  return 0;
}
