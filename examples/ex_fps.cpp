#include <iostream>
#include <string>

#include "../include/Engine.h"
#include "../include/Locator.h"
#include "../include/entities/Sprite.h"
#include "../include/random/RandomGenerator.h"
#include "../include/scene/Scene.h"
#include "../include/ui/Label.h"

const int NUM_SPRITE = 1000;
const int SCREEN_H = 400;
const int SCREEN_W = 400;
const int SPRITE_SIZE = 20;

class DemoScene : public Scene {
 public:
  void start() {
    std::cout << "Starting!" << std::endl;
    this->getWindow().setWindowSize(SCREEN_W, SCREEN_H);
    this->getWindow().setBufferSize(SCREEN_W, SCREEN_H);
    this->getWindow().setMode(DISPLAY_MODE::WINDOWED);
    this->getWindow().setTitle("ex_display");

    this->getAsset().loadFont("freesans", "assets/freesans.ttf", 64);
    this->getAsset().loadImage("lenna", "assets/lenna.png");

    label_id = this->add<Label>(*this, 10, 5, 0, "fps", "freesans");

    for (unsigned int i = 0; i < NUM_SPRITE; i++) {
      int x = RandomGenerator::randomInt(0, SCREEN_W);
      int y = RandomGenerator::randomInt(0, SCREEN_H);
      sprites[i] = this->add<Sprite>(*this, "lenna", x, y);
      this->get<Sprite>(sprites[i]).setSize(SPRITE_SIZE, SPRITE_SIZE);
    }
  }

  void draw() {}

  void update() {
    iter++;

    unsigned int fps = Locator::getWindow().getFps();
    this->get<Label>(label_id).setText(std::to_string(fps));

    for (unsigned int i = 0; i < NUM_SPRITE; i++) {
      Sprite& sprite = this->get<Sprite>(sprites[i]);
      sprite.setPosition((iter + i) % SCREEN_W,
                         sin(iter / 100.0f + i) * SCREEN_H / 2 + SCREEN_H / 2);
    }
  }

  void stop() { std::cout << "Stopping!"; }

 private:
  ObjId label_id = -1;
  ObjId sprites[NUM_SPRITE];

  unsigned int iter = 0;
};

int main() {
  Engine game = Engine();
  Locator::getSceneManager().addScene<DemoScene>("demo");
  Locator::getSceneManager().setNextScene("demo");
  game.start();
  return 0;
}