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
#include "../include/entities/Sprite.h"
#include "../include/entities/ui/Label.h"
#include "../include/random/RandomGenerator.h"
#include "../include/scene/Scene.h"
#include "../include/services/Services.h"

const int NUM_SPRITE = 100;
const int SCREEN_H = 400;
const int SCREEN_H_2 = 200;
const int SCREEN_W = 400;
const int SPRITE_SIZE = 20;

class DemoScene : public afk::Scene {
 public:
  void start() {
    logger.log("Starting!");

    display.setWindowSize(SCREEN_W, SCREEN_H);
    display.setBufferSize(SCREEN_W, SCREEN_H);
    display.setMode(afk::DisplayMode::WINDOWED);
    display.setTitle("ex_fps");

    assets.loadFont("freesans", "assets/freesans.ttf", 64);
    assets.loadImage("lenna", "assets/lenna.png");

    afk::Label& label = add<afk::Label>(*this, 10, 5, 100);
    label.setText("FPS");
    label.setFont("freesans");
    label_id = label.id;

    for (unsigned int i = 0; i < NUM_SPRITE; i++) {
      afk::Sprite& sprite = add<afk::Sprite>(*this, "lenna");
      sprite.setSize(SPRITE_SIZE, SPRITE_SIZE);
      sprites[i] = sprite.id;
    }
  }

  void update(Uint32 delta) {
    Scene::update(delta);

    iter += static_cast<float>(delta) / 10.0f;

    int fps = display.getFps();

    get<afk::Label>(label_id).setText(std::to_string(fps));

    for (unsigned int i = 0; i < NUM_SPRITE; i++) {
      afk::Sprite& sprite = get<afk::Sprite>(sprites[i]);
      sprite.setPosition(fmod(iter + i, SCREEN_W),
                         sin(iter / 100.0f + i) * SCREEN_H_2 + SCREEN_H_2);
      sprite.setAngle(sprite.getAngle() + delta / 10.0f);
    }
  }

  void stop() { logger.log("Stopping!"); }

 private:
  ObjId label_id = -1;
  ObjId sprites[NUM_SPRITE];

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
