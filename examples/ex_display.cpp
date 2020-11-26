#include <iostream>

#include "../include/Engine.h"
#include "../include/scene/Scene.h"

class DemoScene : public Scene {
 public:
  void start() {
    std::cout << "Starting!";
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
  game.addScene<DemoScene>("demo");
  game.start("demo");
  return 0;
}