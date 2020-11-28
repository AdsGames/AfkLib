#include <string>

#include "../include/Engine.h"
#include "../include/entities/Sprite.h"
#include "../include/entities/ui/Label.h"
#include "../include/random/RandomGenerator.h"
#include "../include/scene/Scene.h"
#include "../include/services/Locator.h"

const int NUM_SPRITE = 1000;
const int SCREEN_H = 400;
const int SCREEN_W = 400;
const int SPRITE_SIZE = 20;

class DemoScene : public Scene {
 public:
  void start() {
    Locator::getLogger().log("Starting!");
    Locator::getDisplay().setWindowSize(SCREEN_W, SCREEN_H);
    Locator::getDisplay().setBufferSize(SCREEN_W, SCREEN_H);
    Locator::getDisplay().setMode(DISPLAY_MODE::WINDOWED);
    Locator::getDisplay().setTitle("ex_fps");

    Locator::getAsset().loadFont("freesans", "assets/freesans.ttf", 64);
    Locator::getAsset().loadImage("lenna", "assets/lenna.png");

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

    unsigned int fps = Locator::getDisplay().getFps();
    this->get<Label>(label_id).setText(std::to_string(fps));

    for (unsigned int i = 0; i < NUM_SPRITE; i++) {
      Sprite& sprite = this->get<Sprite>(sprites[i]);
      sprite.setPosition((iter + i) % SCREEN_W,
                         sin(iter / 100.0f + i) * SCREEN_H / 2 + SCREEN_H / 2);
    }
  }

  void stop() { Locator::getLogger().log("Stopping!"); }

 private:
  ObjId label_id = -1;
  ObjId sprites[NUM_SPRITE];

  unsigned int iter = 0;
};

int main() {
  Engine game = Engine();
  Locator::getScene().addScene<DemoScene>("demo");
  Locator::getScene().setNextScene("demo");
  game.start();
  return 0;
}