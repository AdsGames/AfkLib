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
#include "../include/common/Vec.h"
#include "../include/components/components.h"
#include "../include/scene/Scene.h"

class DemoScene : public afk::Scene {
 public:
  void start() override {
    logger.log("Starting!");

    display.setWindowSize(512, 512);
    display.setBufferSize(512, 512);
    display.setMode(afk::DisplayMode::Windowed);
    display.setTitle("ex_sprite");

    auto& lennaTexture = assets.loadImage("lenna", "assets/lenna.png");

    auto sprite = createEntity();
    createComponent<afk::Sprite>(sprite, lennaTexture);
    createComponent<afk::Transform>(sprite, afk::Vec3(0, 0, 0),
                                    afk::Vec2(50, 50));
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
