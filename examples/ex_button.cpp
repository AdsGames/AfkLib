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
    this->getWindow().setWindowSize(512, 512);
    this->getWindow().setBufferSize(512, 512);
    this->getWindow().setMode(DISPLAY_MODE::WINDOWED);
    this->getWindow().setTitle("ex_button");
    this->getAsset().loadFont("freesans", "assets/freesans.ttf", 12);

    int button_id =
        this->add<Button>(*this, 10, 10, 10, "CLICK ME", "freesans");

    this->get<Button>(button_id).setOnClick([]() {
      MessageBox message_box(QUESTION);
      message_box.setTitle("Nice");
      message_box.setHeading("You Clicked");
      message_box.setText("The button");
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