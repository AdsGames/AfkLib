#include "../include/Engine.h"
#include "../include/entities/ui/Button.h"
#include "../include/entities/ui/MessageBox.h"
#include "../include/scene/Scene.h"
#include "../include/services/Locator.h"

class DemoScene : public Scene {
 public:
  void start() {
    Locator::getLogger().log("Starting!");
    Locator::getDisplay().setWindowSize(512, 512);
    Locator::getDisplay().setBufferSize(512, 512);
    Locator::getDisplay().setMode(DISPLAY_MODE::WINDOWED);
    Locator::getDisplay().setTitle("ex_button");
    Locator::getAsset().loadFont("freesans", "assets/freesans.ttf", 12);

    int button_id =
        this->add<Button>(*this, 10, 10, 10, "CLICK ME", "freesans");

    this->get<Button>(button_id).setOnClick([]() {
      MessageBox message_box(INFO);
      message_box.setTitle("Nice");
      message_box.setHeading("You Clicked");
      message_box.setText("The button");
      message_box.show();
    });
  }

  void draw() {}

  void update() {}

  void stop() { Locator::getLogger().log("Stopping!"); }
};

int main(int argv, char** args) {
  Engine game = Engine();
  Locator::getScene().addScene<DemoScene>("demo");
  Locator::getScene().setNextScene("demo");
  game.start();
  return 0;
}