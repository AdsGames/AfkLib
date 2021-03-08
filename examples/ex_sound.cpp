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
    display.setTitle("ex_mouse");

    afk::AssetService& assets = afk::Services::getAssetService();
    assets.loadAudio("win", "assets/win.wav");
  }

  void update() {
    afk::InputService& input = afk::Services::getInputService();
    afk::AudioService& audio = afk::Services::getAudioService();

    if (input.mousePressed(afk::MouseButtons::BUTTON_LEFT)) {
      audio.playSound("win", {127, 0, 1.0f, false});
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