#include <string>

#include "../include/Game.h"
#include "../include/entities/Sprite.h"
#include "../include/entities/ui/Label.h"
#include "../include/random/RandomGenerator.h"
#include "../include/scene/Scene.h"
#include "../include/services/Services.h"

const int NUM_SPRITE = 100;
const int SCREEN_H = 400;
const int SCREEN_W = 400;
const int SPRITE_SIZE = 20;

class DemoScene : public afk::Scene {
 public:
  void start() {
    afk::LoggingService& logger = afk::Services::getLoggingService();
    logger.log("Starting!");

    afk::DisplayService& display = afk::Services::getDisplayService();
    display.setWindowSize(SCREEN_W, SCREEN_H);
    display.setBufferSize(SCREEN_W, SCREEN_H);
    display.setMode(afk::DISPLAY_MODE::WINDOWED);
    display.setTitle("ex_fps");

    afk::AssetService& assets = afk::Services::getAssetService();
    assets.loadFont("freesans", "assets/freesans.ttf", 64);
    assets.loadImage("lenna", "assets/lenna.png");

    label_id = add<afk::Label>(*this, 10, 5, 0, "fps", "freesans");

    for (unsigned int i = 0; i < NUM_SPRITE; i++) {
      int x = afk::Random::randomInt(0, SCREEN_W);
      int y = afk::Random::randomInt(0, SCREEN_H);
      sprites[i] = add<afk::Sprite>(*this, "lenna", x, y);
      get<afk::Sprite>(sprites[i]).setSize(SPRITE_SIZE, SPRITE_SIZE);
    }
  }

  void update() {
    iter++;

    unsigned int fps = afk::Services::getDisplayService().getFps();

    get<afk::Label>(label_id).setText(std::to_string(fps));

    for (unsigned int i = 0; i < NUM_SPRITE; i++) {
      afk::Sprite& sprite = get<afk::Sprite>(sprites[i]);
      sprite.setPosition((iter + i) % SCREEN_W,
                         sin(iter / 100.0f + i) * SCREEN_H / 2 + SCREEN_H / 2);
    }
  }

  void stop() {
    afk::LoggingService& logger = afk::Services::getLoggingService();
    logger.log("Stopping!");
  }

 private:
  ObjId label_id = -1;
  ObjId sprites[NUM_SPRITE];

  unsigned int iter = 0;
};

int main(int argv, char** args) {
  afk::Game game = afk::Game();

  afk::SceneService& scenes = afk::Services::getSceneService();
  scenes.addScene<DemoScene>("demo");
  scenes.setNextScene("demo");

  game.start();
  return 0;
}