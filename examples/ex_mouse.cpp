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
    display.setMode(afk::DisplayMode::WINDOWED);
    display.setTitle("ex_mouse");

    afk::AssetService& assets = afk::Services::getAssetService();
    assets.loadImage("lenna", "assets/lenna.png");

    afk::Sprite& lenna = addObj<afk::Sprite>(*this, "lenna");

    lenna.setSize(30, 30);
    lenna.setPosition(100, 100);
    lennaId = lenna.getId();
  }

  void draw() {}

  void update() {
    afk::InputService& input = afk::Services::getInputService();
    afk::Sprite& lenna = get<afk::Sprite>(lennaId);

    if (input.mousePressed(afk::MouseButtons::BUTTON_LEFT)) {
      lenna.setPosition(input.mouseX(), input.mouseY());
    }
    if (input.mouseDown(afk::MouseButtons::BUTTON_RIGHT)) {
      lenna.setSize(input.mouseX(), input.mouseY());
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