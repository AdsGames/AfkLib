#include <iostream>

#include "../include/Engine.h"
#include "../include/Locator.h"
#include "../include/scene/Scene.h"
#include "../include/ui/Button.h"
#include "../include/ui/MessageBox.h"

class DemoScene : public Scene {
 public:
  void start() {
    std::cout << "Starting!" << std::endl;
    this->getWindow().setWindowSize(256, 256);
    this->getWindow().setBufferSize(256, 256);
    this->getWindow().setMode(DISPLAY_MODE::WINDOWED);
    this->getWindow().setTitle("ex_button");
    this->getAsset().loadFont("freesans", "assets/freesans.ttf", 12);

    ObjId button_id_1 =
        this->add<Button>(*this, 10, 10, 10, "Question Message", "freesans");

    this->get<Button>(button_id_1).setOnClick([button_id_1]() {
      std::cout << "Clicked button " << button_id_1 << std::endl;
      MessageBox message_box(QUESTION);
      message_box.setTitle("Question");
      message_box.setHeading("Heading");
      message_box.setText("Text");
      message_box.show();
    });

    ObjId button_id_2 =
        this->add<Button>(*this, 10, 30, 10, "Warning Message", "freesans");

    this->get<Button>(button_id_2).setOnClick([button_id_2]() {
      std::cout << "Clicked button " << button_id_2 << std::endl;
      MessageBox message_box(WARN);
      message_box.setTitle("Warning");
      message_box.setHeading("Heading");
      message_box.setText("Text");
      message_box.show();
    });

    ObjId button_id_3 =
        this->add<Button>(*this, 10, 50, 10, "Error Message", "freesans");

    this->get<Button>(button_id_3).setOnClick([button_id_3]() {
      std::cout << "Clicked button " << button_id_3 << std::endl;
      MessageBox message_box(ERROR);
      message_box.setTitle("Error");
      message_box.setHeading("Heading");
      message_box.setText("Text");
      message_box.show();
    });

    ObjId button_id_4 =
        this->add<Button>(*this, 10, 70, 10, "OK Cancel Message", "freesans");

    this->get<Button>(button_id_4).setOnClick([button_id_4]() {
      std::cout << "Clicked button " << button_id_4 << std::endl;
      MessageBox message_box(OK_CANCEL);
      message_box.setTitle("OK Cancel");
      message_box.setHeading("Heading");
      message_box.setText("Text");
      message_box.show();
    });

    ObjId button_id_5 =
        this->add<Button>(*this, 10, 90, 10, "Yes No Message", "freesans");

    this->get<Button>(button_id_5).setOnClick([button_id_5]() {
      std::cout << "Clicked button " << button_id_5 << std::endl;
      MessageBox message_box(YES_NO);
      message_box.setTitle("Yes No");
      message_box.setHeading("Heading");
      message_box.setText("Text");
      message_box.show();
    });
  }

  void draw() {}

  void update() {}

  void stop() { std::cout << "Stopping!"; }
};

int main() {
  Engine game = Engine();
  Locator::getSceneManager().addScene<DemoScene>("demo");
  Locator::getSceneManager().setNextScene("demo");
  game.start();
  return 0;
}