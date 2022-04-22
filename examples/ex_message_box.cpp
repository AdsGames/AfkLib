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
#include "../include/services/Services.h"
#include "../include/ui/MessageBox.h"
class DemoScene : public afk::Scene {
 public:
  void start() {
    logger.log("Starting!");

    display.setWindowSize(256, 256);
    display.setBufferSize(256, 256);
    display.setMode(afk::DisplayMode::WINDOWED);
    display.setTitle("ex_message_box");

    assets.loadFont("freesans", "assets/freesans.ttf", 12);

    auto button_1 = createEntity();
    createComponent<afk::Transform>(button_1, afk::Vec3(10, 10, 10));
    auto& button_1_button = createComponent<afk::Button>(button_1);
    button_1_button.setFont("freesans");
    button_1_button.setText("Question Message");
    // button_1_button.sizeToText();
    // button_1_button.setOnClick([]() {
    //   afk::MessageBox message_box(afk::MessageBoxType::INFO);
    //   message_box.setTitle("Info");
    //   message_box.setText("Text");
    //   message_box.show();
    // });

    auto button_2 = createEntity();
    createComponent<afk::Transform>(button_2, afk::Vec3(10, 50, 10));
    auto& button_2_button = createComponent<afk::Button>(button_2);
    button_2_button.setFont("freesans");
    button_2_button.setText("Warning Message");
    // button_2_button.sizeToText();
    // button_2_button.setOnClick([]() {
    //   afk::MessageBox message_box(afk::MessageBoxType::WARN);
    //   message_box.setTitle("Warning");
    //   message_box.setText("Text");
    //   message_box.show();
    // });

    auto button_3 = createEntity();
    createComponent<afk::Transform>(button_3, afk::Vec3(10, 90, 10));
    auto& button_3_button = createComponent<afk::Button>(button_3);
    button_3_button.setFont("freesans");
    button_3_button.setText("Error Message");
    // button_3_button.sizeToText();
    // button_3_button.setOnClick([]() {
    //   afk::MessageBox message_box(afk::MessageBoxType::ERROR);
    //   message_box.setTitle("Error");
    //   message_box.setText("Text");
    //   message_box.show();
    // });
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
