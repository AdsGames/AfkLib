#include "../include/Engine.h"
#include "../include/scene/Scene.h"
#include "../include/services/Locator.h"

class DemoScene : public Scene {
 public:
  void start() {
    Locator::getLogger().log("Starting!");
    Locator::getDisplay().setWindowSize(100, 100);
    Locator::getDisplay().setBufferSize(100, 100);
    Locator::getDisplay().setMode(DISPLAY_MODE::WINDOWED);
    Locator::getDisplay().setTitle("ex_display");
  }

  void draw() {}

  void update() {}

  void stop() { Locator::getLogger().log("Stopping!"); }
};

int main(int argv, char** args) {
  Engine game = Engine();
  Locator::getScene().addScene<DemoScene>("demo");
  Locator::getScene().setNextScene("demo");
  game.start();
  return 0;
}