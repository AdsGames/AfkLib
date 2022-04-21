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
#include "../include/components/Transform.h"
#include "../include/scene/Scene.h"
#include "../include/services/Services.h"

void characterSystem(entt::registry& registry,
                     afk::InputService& input,
                     Uint32 delta) {
  auto view = registry.view<afk::Transform>();

  for (auto [entity, transform] : view.each()) {
    float speed = delta / 10.0f;
    if (input.keyDown(afk::Keys::UP)) {
      transform.position.y -= speed;
    }
    if (input.keyDown(afk::Keys::DOWN)) {
      transform.position.y += speed;
    }
    if (input.keyDown(afk::Keys::LEFT)) {
      transform.position.x -= speed;
    }
    if (input.keyDown(afk::Keys::RIGHT)) {
      transform.position.x += speed;
    }
  }
}

class DemoScene : public afk::Scene {
 public:
  void start() {
    logger.log("Starting!");

    display.setWindowSize(512, 512);
    display.setBufferSize(512, 512);
    display.setMode(afk::DisplayMode::WINDOWED);
    display.setTitle("ex_keyboard");

    assets.loadImage("lenna", "assets/lenna.png");

    createCharacter();
  }

  void createCharacter() {
    entt::entity id = createEntity();
    createComponent<afk::Transform>(id, afk::Vec3(100, 100, 0),
                                    afk::Vec2(40, 40));
    createComponent<afk::SpriteComponent>(id, "lenna");
    character_ids.push_back(id);
  }

  void update(Uint32 delta) override {
    Scene::update(delta);

    if (input.keyPressed(afk::Keys::A)) {
      createCharacter();
    }

    if (input.keyPressed(afk::Keys::R)) {
      if (character_ids.size() > 0) {
        entt::entity id = character_ids.back();
        destroyEntity(id);
        character_ids.pop_back();
      }
    }

    characterSystem(getRegistry(), input, delta);
  }

  void stop() { logger.log("Stopping!"); }

 private:
  std::vector<entt::entity> character_ids;
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
