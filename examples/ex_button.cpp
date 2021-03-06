#include "../include/Game.h"
#include "../include/entities/ui/Button.h"
#include "../include/entities/ui/MessageBox.h"
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
    display.setTitle("ex_button");

    afk::AssetService& assets = afk::Services::getAssetService();
    assets.loadFont("freesans", "assets/freesans.ttf", 12);

    afk::Button& button =
        addObj<afk::Button>(*this, 10, 10, 10, "CLICK ME", "freesans");

    button.setOnClick([]() {
      afk::MessageBox message_box(afk::INFO);
      message_box.setTitle("Nice");
      message_box.setHeading("You Clicked");
      message_box.setText("The button");
      message_box.show();
    });
  }

  void update() {}

  void stop() {
    afk::LoggingService& logger = afk::Services::getLoggingService();
    logger.log("Stopping!");
  }
};

int main(int argv, char** args) {
  afk::Game game = afk::Game();

  afk::SceneService& scenes = afk::Services::getSceneService();
  scenes.addScene<DemoScene>("demo");
  scenes.setNextScene("demo");

  game.start();

  return 0;
}