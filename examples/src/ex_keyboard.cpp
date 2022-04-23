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
#include "../include/components/components.h"
#include "../include/scene/Scene.h"

void characterSystem(afk::Registry& registry,
                     afk::InputService& input,
                     uint32_t delta) {
  auto view = registry.view<afk::Transform>();

  for (auto [entity, transform] : view.each()) {
    float speed = delta / 10.0f;
    if (input.keyDown(afk::Keys::Up)) {
      transform.position.y -= speed;
    }
    if (input.keyDown(afk::Keys::Down)) {
      transform.position.y += speed;
    }
    if (input.keyDown(afk::Keys::Left)) {
      transform.position.x -= speed;
    }
    if (input.keyDown(afk::Keys::Right)) {
      transform.position.x += speed;
    }
  }
}

class DemoScene : public afk::Scene {
 public:
  void start() override {
    logger.log("Starting!");

    display.setWindowSize(512, 512);
    display.setBufferSize(512, 512);
    display.setMode(afk::DisplayMode::Windowed);
    display.setTitle("ex_keyboard");

    assets.loadImage("lenna", "assets/lenna.png");

    createCharacter();
  }

  void createCharacter() {
    afk::Entity id = createEntity();
    createComponent<afk::Transform>(id, afk::Vec3(100, 100, 0),
                                    afk::Vec2(40, 40));
    createComponent<afk::Sprite>(id, "lenna");
    entityIds.push_back(id);
  }

  void update(uint32_t delta) override {
    Scene::update(delta);

    if (input.keyPressed(afk::Keys::A)) {
      createCharacter();
    }

    if (input.keyPressed(afk::Keys::R)) {
      if (entityIds.size() > 0) {
        afk::Entity id = entityIds.back();
        destroyEntity(id);
        entityIds.pop_back();
      }
    }

    characterSystem(getRegistry(), input, delta);
  }

  void stop() override { logger.log("Stopping!"); }

 private:
  std::vector<afk::Entity> entityIds;
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
