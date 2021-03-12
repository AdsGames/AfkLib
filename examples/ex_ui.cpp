/**
 * @file ex_button.cpp
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
#include "../include/entities/ui/Checkbox.h"
#include "../include/entities/ui/Inputbox.h"
#include "../include/entities/ui/Label.h"
#include "../include/entities/ui/MessageBox.h"
#include "../include/scene/Scene.h"
#include "../include/services/Services.h"

class DemoScene : public afk::Scene {
 public:
  void start() {
    logger.log("Starting!");

    display.setWindowSize(512, 512);
    display.setBufferSize(512, 512);
    display.setMode(afk::DisplayMode::WINDOWED);
    display.setTitle("ex_button");

    assets.loadFont("freesans", "assets/freesans.ttf", 12);

    afk::Button& button = addObj<afk::Button>(*this, 10, 10);
    button.setText("CLICK ME");
    button.setFont("freesans");
    button.sizeToText();
    button.setOnClick([]() {
      afk::MessageBox message_box(afk::MessageBoxType::INFO);
      message_box.setTitle("Nice");
      message_box.setHeading("You Clicked");
      message_box.setText("The button");
      message_box.show();
    });

    afk::Checkbox& checkbox = addObj<afk::Checkbox>(*this, 10, 40);
    checkbox.setText("CHECK ME");
    checkbox.setFont("freesans");
    checkbox.setOnCheck([](const bool checked) {
      afk::MessageBox message_box(afk::MessageBoxType::INFO);
      message_box.setTitle("Nice");
      if (checked) {
        message_box.setText("The checkbox is checked");
      } else {
        message_box.setText("The checkbox is unchecked");
      }
      message_box.show();
    });

    afk::Label& label = addObj<afk::Label>(*this, 10, 70);
    label.setText("LABEL ME");
    label.setFont("freesans");

    afk::Inputbox& inputbox = addObj<afk::Inputbox>(*this, 10, 90);
    inputbox.setText("WRITE ME");
    inputbox.setFont("freesans");
  }

  void draw() {}

  void update(Uint32 delta) {}

  void stop() { logger.log("Stopping!"); }

 private:
  ObjId checkbox_id;
};

int main(int argv, char** args) {
  afk::Game game = afk::Game();

  afk::SceneService& scenes = afk::Services::getSceneService();
  scenes.addScene<DemoScene>("demo");
  scenes.setNextScene("demo");

  game.start();

  return 0;
}
