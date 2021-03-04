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
    Locator::getDisplay().setTitle("ex_keyboard");
    Locator::getAsset().loadImage("lenna", "assets/lenna.png");

    Sprite& lenna = addObj<Sprite>(*this, "lenna");
    lenna.setSize(30, 30);
    lenna.setPosition(100, 100);
    lennaId = lenna.getId();
  }

  void draw() {}

  void update() {
    const KeyboardState& keys = Locator::getInput().keyboard();
    Sprite& lenna = get<Sprite>(lennaId);

    if (keys.key[SDL_SCANCODE_UP]) {
      lenna.setPosition(lenna.getX(), lenna.getY() - 5);
    }
    if (keys.key[SDL_SCANCODE_DOWN]) {
      lenna.setPosition(lenna.getX(), lenna.getY() + 5);
    }
    if (keys.key[SDL_SCANCODE_LEFT]) {
      lenna.setPosition(lenna.getX() - 5, lenna.getY());
    }
    if (keys.key[SDL_SCANCODE_RIGHT]) {
      lenna.setPosition(lenna.getX() + 5, lenna.getY());
    }
  }

  void stop() { Locator::getLogger().log("Stopping!"); }

 private:
  ObjId lennaId;
};

int main(int argv, char** args) {
  Engine game = Engine();
  Locator::getScene().addScene<DemoScene>("demo");
  Locator::getScene().setNextScene("demo");
  game.start();
  return 0;
}