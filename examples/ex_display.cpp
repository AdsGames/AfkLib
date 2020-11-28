#include <iostream>

#include "../include/Engine.h"
#include "../include/Locator.h"
#include "../include/scene/Scene.h"

class DemoScene : public Scene {
 public:
  void start() {
    std::cout << "Starting!" << std::endl;
    this->getWindow().setWindowSize(100, 100);
    this->getWindow().setBufferSize(100, 100);
    this->getWindow().setMode(DISPLAY_MODE::WINDOWED);
    this->getWindow().setTitle("ex_display");
  }

  void draw() {}

  void update() {}

  void stop() { std::cout << "Stopping!"; }
};

int main() {
  Engine game = Engine();
  Locator::getSceneManager().addScene<DemoScene>("demo");
  Locator::getSceneManager().setNextScene("demo");
  game.start();
  return 0;
}