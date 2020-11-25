#include <iostream>

#include "../../include/Engine.h"
#include "../../include/scene/Scene.h"

class DemoScene : public Scene {
 public:
  void start() {
    std::cout << "Starting!";
    this->getWindow().setTitle("ex_screen");
  }

  void draw() { std::cout << "Drawing!"; }

  void update() { std::cout << "Updating!"; }

  void stop() { std::cout << "Stopping!"; }
};

int main() {
  Engine game = Engine();
  game.addScene<DemoScene>("demo");
  game.start("demo");
  return 0;
}