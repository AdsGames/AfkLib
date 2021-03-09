/**
 * @file ex_rotate.cpp
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
    display.setTitle("ex_sprite");

    assets.loadImage("lenna", "assets/lenna.png");

    lennaId = add<afk::Sprite>(*this, "lenna");
  }

  void draw() {}

  void update(Uint32 delta) {
    afk::Sprite& lenna = get<afk::Sprite>(lennaId);
    lenna.setAngle(lenna.getAngle() + delta / 10.0f);
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
