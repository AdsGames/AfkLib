#include "../include/Game.h"
#include "../include/entities/Sprite.h"
#include "../include/scene/Scene.h"
#include "../include/services/Services.h"

class DemoScene : public afk::Scene {
 public:
  void start() {
    afk::LoggingService& logger = afk::Services::getLoggingService();
    logger.log("Starting!");

    afk::DisplayService& display = afk::Services::getDisplayService();
    display.setWindowSize(512, 512);
    display.setBufferSize(512, 512);
    display.setMode(afk::DISPLAY_MODE::WINDOWED);
    display.setTitle("ex_keyboard");

    afk::AssetService& assets = afk::Services::getAssetService();
    assets.loadImage("lenna", "assets/lenna.png");

    afk::Sprite& lenna = addObj<afk::Sprite>(*this, "lenna");
    lenna.setSize(30, 30);
    lenna.setPosition(100, 100);
    lennaId = lenna.getId();
  }

  void update() {
    afk::InputService& input = afk::Services::getInputService();
    afk::Sprite& lenna = get<afk::Sprite>(lennaId);

    if (input.keyDown(afk::Keys::KEY_UP)) {
      lenna.setPosition(lenna.getX(), lenna.getY() - 5);
    }
    if (input.keyDown(afk::Keys::KEY_DOWN)) {
      lenna.setPosition(lenna.getX(), lenna.getY() + 5);
    }
    if (input.keyDown(afk::Keys::KEY_LEFT)) {
      lenna.setPosition(lenna.getX() - 5, lenna.getY());
    }
    if (input.keyDown(afk::Keys::KEY_RIGHT)) {
      lenna.setPosition(lenna.getX() + 5, lenna.getY());
    }
  }

  void stop() {
    afk::LoggingService& logger = afk::Services::getLoggingService();
    logger.log("Stopping!");
  }

 private:
  ObjId lennaId;
};

int main(int argv, char** args) {
  afk::Game game = afk::Game();

  afk::SceneService& scenes = afk::Services::getSceneService();
  scenes.addScene<DemoScene>("demo");
  scenes.setNextScene("demo");

  game.start();
  return 0;
}