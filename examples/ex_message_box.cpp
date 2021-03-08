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
    display.setWindowSize(256, 256);
    display.setBufferSize(256, 256);
    display.setMode(afk::DisplayMode::WINDOWED);
    display.setTitle("ex_message_box");

    afk::AssetService& assets = afk::Services::getAssetService();
    assets.loadFont("freesans", "assets/freesans.ttf", 12);

    afk::Button& button1 =
        addObj<afk::Button>(*this, 10, 10, 10, "Question Message", "freesans");

    button1.setOnClick([]() {
      afk::MessageBox message_box(afk::MessageBoxType::INFO);
      message_box.setTitle("Info");
      message_box.setHeading("Heading");
      message_box.setText("Text");
      message_box.show();
    });

    afk::Button& button2 =
        addObj<afk::Button>(*this, 10, 30, 10, "Warning Message", "freesans");

    button2.setOnClick([]() {
      afk::MessageBox message_box(afk::MessageBoxType::WARN);
      message_box.setTitle("Warning");
      message_box.setHeading("Heading");
      message_box.setText("Text");
      message_box.show();
    });

    afk::Button& button3 =
        addObj<afk::Button>(*this, 10, 50, 10, "Error Message", "freesans");

    button3.setOnClick([]() {
      afk::MessageBox message_box(afk::MessageBoxType::ERROR);
      message_box.setTitle("Error");
      message_box.setHeading("Heading");
      message_box.setText("Text");
      message_box.show();
    });
  }

  void draw() {}

  void update() {}

  void stop() { afk::Services::getLoggingService().log("Stopping!"); }
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