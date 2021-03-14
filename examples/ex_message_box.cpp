/**
 * @file ex_message_box.cpp
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief
 * @version 0.1
 * @date 2021-03-08
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "../include/Game.h"
#include "../include/entities/ui/Button.h"
#include "../include/entities/ui/MessageBox.h"
#include "../include/scene/Scene.h"
#include "../include/services/Services.h"

class DemoScene : public afk::Scene {
 public:
  void start() {
    logger.log("Starting!");

    display.setWindowSize(256, 256);
    display.setBufferSize(256, 256);
    display.setMode(afk::DisplayMode::WINDOWED);
    display.setTitle("ex_message_box");

    assets.loadFont("freesans", "assets/freesans.ttf", 12);

    afk::Button& button1 = add<afk::Button>(*this, 10, 10, 10);
    button1.setFont("freesans");
    button1.setText("Question Message");
    button1.sizeToText();
    button1.setOnClick([]() {
      afk::MessageBox message_box(afk::MessageBoxType::INFO);
      message_box.setTitle("Info");
      message_box.setText("Text");
      message_box.show();
    });

    afk::Button& button2 = add<afk::Button>(*this, 10, 50, 10);
    button2.setFont("freesans");
    button2.setText("Warning Message");
    button2.sizeToText();
    button2.setOnClick([]() {
      afk::MessageBox message_box(afk::MessageBoxType::WARN);
      message_box.setTitle("Warning");
      message_box.setText("Text");
      message_box.show();
    });

    afk::Button& button3 = add<afk::Button>(*this, 10, 90, 10);
    button3.setFont("freesans");
    button3.setText("Error Message");
    button3.sizeToText();
    button3.setOnClick([]() {
      afk::MessageBox message_box(afk::MessageBoxType::ERROR);
      message_box.setTitle("Error");
      message_box.setText("Text");
      message_box.show();
    });
  }

  void stop() { logger.log("Stopping!"); }
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
