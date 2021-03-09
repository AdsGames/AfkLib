/**
 * @file ex_particles.cpp
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief
 * @version 0.1
 * @date 2021-03-08
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "../include/Game.h"
#include "../include/color/Color.h"
#include "../include/entities/ParticleEmitter.h"
#include "../include/random/RandomGenerator.h"
#include "../include/scene/Scene.h"
#include "../include/services/Services.h"

class DemoScene : public afk::Scene {
 public:
  void start() {
    logger.log("Starting!");

    display.setWindowSize(512, 512);
    display.setBufferSize(512, 512);
    display.setMode(afk::DisplayMode::WINDOWED);
    display.setTitle("ex_particles");
    display.setBackgroundColor(afk::color::rgb(0, 0, 0));

    assets.loadImage("fuzzball", "assets/fuzzball.png");

    afk::ParticleEmitter& emitter =
        addObj<afk::ParticleEmitter>(*this, 256, 256);
    emitter.setSize(30, 30);

    for (int i = 0; i < 100; i++) {
      afk::Particle particle(*this, 0, 0, 0, afk::ParticleType::SQUARE);
      particle.setLifespan(afk::Random::randomInt(100, 1000));
      particle.setSize(10.0f, 3.0f);
      particle.setColor(afk::color::rgb(128, 22, 22),
                        afk::color::rgb(100, 100, 100));
      particle.setVelocity(afk::Random::randomFloat(-0.2, 0.2),
                           afk::Random::randomFloat(-0.1, -0.2));
      particle.setAcceleration(0, 0.1f);
      emitter.addParticle(particle);
    }

    afk::ParticleEmitter& emitter_2 =
        addObj<afk::ParticleEmitter>(*this, 128, 256);
    emitter_2.setSize(1, 1);

    for (int i = 0; i < 100; i++) {
      afk::Particle particle(*this, 0, 0, 0, afk::ParticleType::CIRCLE);
      particle.setLifespan(afk::Random::randomInt(100, 200));
      particle.setSize(3.0f, 2.0f);
      particle.setColor(afk::color::rgb(0, 0, 128),
                        afk::color::rgb(255, 255, 255));
      particle.setVelocity(afk::Random::randomFloat(-0.5, 0.5), -10.0);
      particle.setAcceleration(0, 0.3f);
      emitter_2.addParticle(particle);
    }

    afk::ParticleEmitter& emitter_3 =
        addObj<afk::ParticleEmitter>(*this, 384, 256);
    emitter_3.setSize(5, 5);

    for (int i = 0; i < 100; i++) {
      afk::Particle particle(*this, 0, 0, 0, afk::ParticleType::IMAGE);
      particle.setLifespan(afk::Random::randomInt(800, 1500));
      particle.setTexture("fuzzball");
      particle.setSize(16.0f, 20.0f);
      particle.setVelocity(afk::Random::randomFloat(0.2, 0.25), -0.5);
      emitter_3.addParticle(particle);
    }
  }

  void draw() {}

  void update() {}

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
