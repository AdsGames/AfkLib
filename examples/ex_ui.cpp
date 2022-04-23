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
#include "../include/scene/Scene.h"
#include "../include/services/Services.h"
#include "../include/ui/Button.h"
#include "../include/ui/Checkbox.h"
#include "../include/ui/Image.h"
#include "../include/ui/Inputbox.h"
#include "../include/ui/Label.h"
#include "../include/ui/MessageBox.h"

class DemoScene : public afk::Scene {
 public:
  void start() {
    logger.log("Starting!");

    display.setWindowSize(512, 512);
    display.setBufferSize(512, 512);
    display.setMode(afk::DisplayMode::WINDOWED);
    display.setTitle("ex_button");

    assets.loadFont("freesans", "assets/freesans.ttf", 12);
    assets.loadImage("lenna", "assets/lenna.png");

    afk::Button& button = add<afk::Button>(*this, 10, 10);
    button.setText("CLICK ME");
    button.setFont("freesans");
    button.sizeToText();
    button.setOnClick([]() {
      afk::MessageBox messsageBox(afk::MessageBoxType::INFO);
      messsageBox.setTitle("Nice");
      messsageBox.setText("You Clicked\nThe button");
      messsageBox.show();
    });

    afk::Checkbox& checkbox = add<afk::Checkbox>(*this, 10, 40);
    checkbox.setText("CHECK ME");
    checkbox.setFont("freesans");
    checkbox.setOnCheck([](const bool checked) {
      afk::MessageBox messsageBox(afk::MessageBoxType::INFO);
      messsageBox.setTitle("Nice");
      if (checked) {
        messsageBox.setText("The checkbox is checked");
      } else {
        messsageBox.setText("The checkbox is unchecked");
      }
      messsageBox.show();
    });

    afk::Label& label = add<afk::Label>(*this, 10, 70);
    label.setText("LABEL ME");
    label.setFont("freesans");

    afk::Inputbox& inputbox = add<afk::Inputbox>(*this, 10, 90);
    inputbox.setText("WRITE ME");
    inputbox.setFont("freesans");

    afk::Image& image = add<afk::Image>(*this, 10, 120);
    image.setTexture("lenna");
    image.transform.size.x = 20;
    image.transform.size.y = 20;
    image.setOnClick([]() {
      afk::MessageBox messsageBox(afk::MessageBoxType::INFO);
      messsageBox.setTitle("Nice");
      messsageBox.setText("Clicked the image");
      messsageBox.show();
    });
  }

  void stop() { logger.log("Stopping!"); }
};

int main(int argv, char** args) {
  afk::Game game = afk::Game();

  afk::SceneService& scenes = afk::Services::getSceneService();
  scenes.addScene<DemoScene>("demo");
  scenes.setNextScene("demo");

  game.start();

  return 0;
}
