/**
 * @file ex_fps.cpp
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief
 * @version 0.1
 * @date 2021-03-08
 *
 * @copyright Copyright (c) 2021
 *
 */

#include "../include/Game.h"
#include "../include/common/random.h"
#include "../include/components/components.h"
#include "../include/components/ui.h"
#include "../include/entities/Entity.h"
#include "../include/scene/Scene.h"

const int NUM_SPRITE = 100;
const int SCREEN_H = 400;
const int SCREEN_H_2 = 200;
const int SCREEN_W = 400;
const int SPRITE_SIZE = 20;

class DemoScene : public afk::Scene {
 public:
  void start() override {
    logger.log("Starting!");

    display.setWindowSize(SCREEN_W, SCREEN_H);
    display.setBufferSize(SCREEN_W, SCREEN_H);
    display.setMode(afk::DisplayMode::Windowed);
    display.setTitle("ex_fps");

    assets.loadFont("freesans", "assets/freesans.ttf", 64);
    assets.loadImage("lenna", "assets/lenna.png");

    labelEntity = createEntity();
    createComponent<afk::Transform>(labelEntity, afk::Vec3(10, 5, 0));
    auto& label = createComponent<afk::Label>(labelEntity);
    label.setText("FPS");
    label.setFont("freesans");

    for (auto& sprite : sprites) {
      auto entity = createEntity();
      createComponent<afk::Sprite>(entity, "lenna");
      auto& transform = createComponent<afk::Transform>(entity);
      transform.size.x = SPRITE_SIZE;
      transform.size.y = SPRITE_SIZE;
      sprite = entity;
    }
  }

  void update(uint32_t delta) override {
    Scene::update(delta);

    iter += static_cast<float>(delta) / 10.0f;

    int fps = display.getFps();

    auto& label = getComponent<afk::Label>(labelEntity);
    label.setText(std::to_string(fps));

    for (unsigned int i = 0; i < NUM_SPRITE; i++) {
      auto& transform = getComponent<afk::Transform>(sprites[i]);
      transform.position.x = fmod(iter + i, SCREEN_W);
      transform.position.y = sin(iter / 100.0f + i) * SCREEN_H_2 + SCREEN_H_2;
      transform.angle += delta / 10.0f;
    }
  }

  void stop() override { logger.log("Stopping!"); }

 private:
  afk::Entity labelEntity;
  afk::Entity sprites[NUM_SPRITE];

  float iter = 0;
};

int main(int argv, char** args) {
  afk::Game game = afk::Game();

  afk::SceneService& scenes = afk::Services::getSceneService();
  scenes.addScene<DemoScene>("demo");
  scenes.setNextScene("demo");

  game.start();
  return 0;
}
