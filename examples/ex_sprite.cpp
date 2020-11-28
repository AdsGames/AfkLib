#include <iostream>

#include "../include/Engine.h"
#include "../include/Locator.h"
#include "../include/entities/Sprite.h"
#include "../include/scene/Scene.h"

class DemoScene : public Scene {
 public:
  void start() {
    std::cout << "Starting!" << std::endl;
    this->getWindow().setWindowSize(512, 512);
    this->getWindow().setBufferSize(512, 512);
    this->getWindow().setMode(DISPLAY_MODE::WINDOWED);
    this->getWindow().setTitle("ex_sprite");
    this->getAsset().loadImage("lenna", "assets/lenna.png");
    this->add<Sprite>(*this, "lenna");
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