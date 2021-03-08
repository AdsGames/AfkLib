#include "../include/Game.h"
#include "../include/color/Color.h"
#include "../include/entities/ParticleEmitter.h"
#include "../include/scene/Scene.h"
#include "../include/services/Services.h"

class DemoScene : public afk::Scene {
 public:
  void start() {
    afk::LoggingService& logger = afk::Services::getLoggingService();
    logger.log("Starting!");

    afk::DisplayService& display = afk::Services::getDisplayService();
    display.setWindowSize(512, 512);
    display.setBufferSize(512, 512);
    display.setMode(afk::DisplayMode::WINDOWED);
    display.setTitle("ex_mouse");

    afk::Particle particle(0, 0, afk::color::rgb(0, 255, 127), 1, 1, 2,
                           afk::ParticleType::SQUARE);

    afk::ParticleEmitter& emitter =
        addObj<afk::ParticleEmitter>(*this, particle, 256, 256);
    emitter.setSize(30, 30);
    emitter.setPosition(100, 100);
  }

  void draw() {}

  void update() {}

  void stop() {
    afk::LoggingService& logger = afk::Services::getLoggingService();
    logger.log("Stopping!");
  }
};

int main(int argv, char** args) {
  afk::Game game = afk::Game();

  afk::SceneService& scenes = afk::Services::getSceneService();
  scenes.addScene<DemoScene>("demo");
  scenes.setNextScene("demo");

  game.start();
  return 0;
}