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
#include "../include/components/ui.h"
#include "../include/scene/Scene.h"
#include "../include/ui/MessageBox.h"

class DemoScene : public afk::Scene {
 public:
  void start() override {
    logger.log("Starting!");

    display.setWindowSize(256, 256);
    display.setBufferSize(256, 256);
    display.setMode(afk::DisplayMode::Windowed);
    display.setTitle("ex_message_box");

    assets.loadFont("freesans", "assets/freesans.ttf", 12);

    auto buttonEntity1 = createEntity();
    createComponent<afk::Transform>(buttonEntity1, afk::Vec3(10, 10, 10),
                                    afk::Vec2(160, 20));
    auto& button1 = createComponent<afk::Button>(buttonEntity1);
    button1.setFont("freesans");
    button1.setText("Question Message");
    // button1.sizeToText();
    button1.setOnClick([]() {
      afk::MessageBox messageBox(afk::MessageBoxType::Info);
      messageBox.setTitle("Info");
      messageBox.setText("Text");
      messageBox.show();
    });

    auto buttonEntity2 = createEntity();
    createComponent<afk::Transform>(buttonEntity2, afk::Vec3(10, 50, 10),
                                    afk::Vec2(160, 20));
    auto& button2 = createComponent<afk::Button>(buttonEntity2);
    button2.setFont("freesans");
    button2.setText("Warning Message");
    // button2.sizeToText();
    button2.setOnClick([]() {
      afk::MessageBox messageBox(afk::MessageBoxType::Warn);
      messageBox.setTitle("Warning");
      messageBox.setText("Text");
      messageBox.show();
    });

    auto buttonEntity3 = createEntity();
    createComponent<afk::Transform>(buttonEntity3, afk::Vec3(10, 90, 10),
                                    afk::Vec2(160, 20));
    auto& button3 = createComponent<afk::Button>(buttonEntity3);
    button3.setFont("freesans");
    button3.setText("Error Message");
    // button3.sizeToText();
    button3.setOnClick([]() {
      afk::MessageBox messageBox(afk::MessageBoxType::Error);
      messageBox.setTitle("Error");
      messageBox.setText("Text");
      messageBox.show();
    });
  }

  void stop() override { logger.log("Stopping!"); }
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
