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
#include "../include/components/Sprite.h"
#include "../include/scene/Scene.h"
#include "../include/services/Services.h"

class Character : public afk::GameObject {
 public:
  Character(afk::Scene& scene, const float x, const float y)
      : GameObject(scene, x, y) {
    auto& sprite = scene.addComponent<afk::Sprite>(id);
    sprite.texture = scene.assets.getImage("lenna");

    transform.width = 30;
    transform.height = 30;
  }

  void update(Uint32 delta) {
    float speed = delta / 10.0f;
    if (scene.input.keyDown(afk::Keys::UP)) {
      transform.y -= speed;
    }
    if (scene.input.keyDown(afk::Keys::DOWN)) {
      transform.y += speed;
    }
    if (scene.input.keyDown(afk::Keys::LEFT)) {
      transform.x -= speed;
    }
    if (scene.input.keyDown(afk::Keys::RIGHT)) {
      transform.x += speed;
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

    ObjId id = add<Character>(*this, 100, 100).id;
    character_ids.push_back(id);
  }

  void update(Uint32 delta) override {
    if (input.keyPressed(afk::Keys::A)) {
      ObjId id = add<Character>(*this, 100, 100).id;
      character_ids.push_back(id);
    }
    if (input.keyPressed(afk::Keys::R)) {
      if (character_ids.size() > 0) {
        ObjId id = character_ids.back();
        remove(id);
        character_ids.pop_back();
      }
    }

    Scene::update(delta);
  }

  void stop() { logger.log("Stopping!"); }

 private:
  std::vector<ObjId> character_ids;
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
