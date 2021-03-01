#include "../include/Engine.h"
#include "../include/entities/ui/Button.h"
#include "../include/entities/ui/MessageBox.h"
#include "../include/scene/Scene.h"
#include "../include/services/Locator.h"

class DemoScene : public Scene {
 public:
  void start() {
    Locator::getLogger().log("Starting!");
    Locator::getDisplay().setWindowSize(256, 256);
    Locator::getDisplay().setBufferSize(256, 256);
    Locator::getDisplay().setMode(DISPLAY_MODE::WINDOWED);
    Locator::getDisplay().setTitle("ex_button");
    Locator::getAsset().loadFont("freesans", "assets/freesans.ttf", 12);

    ObjId button_id_1 =
        this->add<Button>(*this, 10, 10, 10, "Question Message", "freesans");

    this->get<Button>(button_id_1).setOnClick([button_id_1]() {
      MessageBox message_box(QUESTION);
      message_box.setTitle("Question");
      message_box.setHeading("Heading");
      message_box.setText("Text");
      message_box.show();
    });

    ObjId button_id_2 =
        this->add<Button>(*this, 10, 30, 10, "Warning Message", "freesans");

    this->get<Button>(button_id_2).setOnClick([button_id_2]() {
      MessageBox message_box(WARN);
      message_box.setTitle("Warning");
      message_box.setHeading("Heading");
      message_box.setText("Text");
      message_box.show();
    });

    ObjId button_id_3 =
        this->add<Button>(*this, 10, 50, 10, "Error Message", "freesans");

    this->get<Button>(button_id_3).setOnClick([button_id_3]() {
      MessageBox message_box(ERROR);
      message_box.setTitle("Error");
      message_box.setHeading("Heading");
      message_box.setText("Text");
      message_box.show();
    });

    ObjId button_id_4 =
        this->add<Button>(*this, 10, 70, 10, "OK Cancel Message", "freesans");

    this->get<Button>(button_id_4).setOnClick([button_id_4]() {
      MessageBox message_box(OK_CANCEL);
      message_box.setTitle("OK Cancel");
      message_box.setHeading("Heading");
      message_box.setText("Text");
      message_box.show();
    });

    ObjId button_id_5 =
        this->add<Button>(*this, 10, 90, 10, "Yes No Message", "freesans");

    this->get<Button>(button_id_5).setOnClick([button_id_5]() {
      MessageBox message_box(YES_NO);
      message_box.setTitle("Yes No");
      message_box.setHeading("Heading");
      message_box.setText("Text");
      message_box.show();
    });
  }

  void draw() {}

  void update() {}

  void stop() { Locator::getLogger().log("Stopping!"); }
};

int main() {
  Engine game = Engine();
  Locator::getScene().addScene<DemoScene>("demo");
  Locator::getScene().setNextScene("demo");
  game.start();
  return 0;
}