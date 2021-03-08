#include "../include/Game.h"
#include "../include/entities/Sprite.h"
#include "../include/scene/Scene.h"
#include "../include/services/Services.h"

class Character : public afk::Sprite {
 public:
  Character(afk::Scene& scene, const float x, const float y)
      : Sprite(scene, x, y) {
    setTexture("lenna");
    setSize(30, 30);
  }

  void update() {
    afk::InputService& input = afk::Services::getInputService();

    if (input.keyDown(afk::Keys::KEY_UP)) {
      setPosition(x, y - 5);
    }
    if (input.keyDown(afk::Keys::KEY_DOWN)) {
      setPosition(x, y + 5);
    }
    if (input.keyDown(afk::Keys::KEY_LEFT)) {
      setPosition(x - 5, y);
    }
    if (input.keyDown(afk::Keys::KEY_RIGHT)) {
      setPosition(x + 5, y);
    }
  }
};

class DemoScene : public afk::Scene {
 public:
  void start() {
    afk::LoggingService& logger = afk::Services::getLoggingService();
    logger.log("Starting!");

    afk::DisplayService& display = afk::Services::getDisplayService();
    display.setWindowSize(512, 512);
    display.setBufferSize(512, 512);
    display.setMode(afk::DisplayMode::WINDOWED);
    display.setTitle("ex_keyboard");

    afk::AssetService& assets = afk::Services::getAssetService();
    assets.loadImage("lenna", "assets/lenna.png");

    add<Character>(*this, 100, 100);
  }

  void draw() {}

  void update() {}

  void stop() {
    afk::LoggingService& logger = afk::Services::getLoggingService();
    logger.log("Stopping!");
  }
};

class MainGame : public afk::Game {
 public:
  MainGame() : Game() {
    afk::SceneService& scene = afk::Services::getSceneService();
    scene.addScene<DemoScene>("demo");
    scene.setNextScene("demo");

    start();
  }
};

int main(int argv, char** args) {
  MainGame game = MainGame();

  return 0;
}