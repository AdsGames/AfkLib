#include "../include/Engine.h"
#include "../include/entities/Sprite.h"
#include "../include/scene/Scene.h"
#include "../include/services/Locator.h"

class DemoScene : public Scene {
 public:
  void start() {
    Locator::getLogger().log("Starting!");
    Locator::getDisplay().setWindowSize(512, 512);
    Locator::getDisplay().setBufferSize(512, 512);
    Locator::getDisplay().setMode(DISPLAY_MODE::WINDOWED);
    Locator::getDisplay().setTitle("ex_sprite");
    Locator::getAsset().loadImage("lenna", "assets/lenna.png");
    this->add<Sprite>(*this, "lenna");
  }

  void draw() {}

  void update() {}

  void stop() { Locator::getLogger().log("Stopping!"); }
};

int main() {
  Engine game = Engine();
  Locator::getScene().addScene<DemoScene>("demo");
  Locator::getScene().setNextScene("demo");
  game.start();
  return 0;
}