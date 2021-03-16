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

#include <memory>

class DemoScene : public afk::Scene {
 public:
  void start() {
    logger.log("Starting!");

    display.setWindowSize(512, 512);
    display.setBufferSize(512, 512);
    display.setMode(afk::DisplayMode::WINDOWED);
    display.setTitle("ex_particles");
    display.setBackgroundColor(afk::color::black);

    assets.loadImage("fuzzball", "assets/fuzzball.png");

    afk::ParticleEmitter& emitter = add<afk::ParticleEmitter>(*this, 256, 256);
    emitter.transform.width = 30;
    emitter.transform.height = 30;

    for (int i = 0; i < 100; i++) {
      auto particle = std::make_unique<afk::Particle>(
          *this, 0, 0, 0, afk::ParticleType::SQUARE);
      particle->setLifespan(afk::Random::randomInt(100, 1000));
      particle->setSize(10.0f, 3.0f);
      particle->setColor(afk::color::rgb(128, 22, 22),
                         afk::color::rgb(100, 100, 100));
      particle->setVelocity(afk::Random::randomFloat(-5.0f, 5.0f),
                            afk::Random::randomFloat(-1.0f, -2.0f));
      particle->setAcceleration(0, 0.2f);
      // emitter.addParticle(particle);
    }

    afk::ParticleEmitter& emitter_2 =
        add<afk::ParticleEmitter>(*this, 128, 256);
    emitter_2.transform.width = 1;
    emitter_2.transform.height = 1;

    for (int i = 0; i < 100; i++) {
      auto particle = std::make_unique<afk::Particle>(
          *this, 0, 0, 0, afk::ParticleType::CIRCLE);
      particle->setLifespan(afk::Random::randomInt(100, 200));
      particle->setSize(3.0f, 2.0f);
      particle->setColor(afk::color::blue, afk::color::white);
      particle->setVelocity(afk::Random::randomFloat(-5, 5), -100);
      particle->setAcceleration(0, 3.0f);
      // emitter_2.addParticle(particle);
    }

    afk::ParticleEmitter& emitter_3 =
        add<afk::ParticleEmitter>(*this, 384, 256);
    emitter_3.transform.width = 5;
    emitter_3.transform.height = 5;
    smoke_id = emitter_3.id;

    for (int i = 0; i < 400; i++) {
      auto particle = std::make_unique<afk::Particle>(*this, 0, 0, 0,
                                                      afk::ParticleType::IMAGE);
      particle->setLifespan(afk::Random::randomInt(800, 1500));
      particle->setTexture("fuzzball");
      particle->setSize(16.0f, 20.0f);
      particle->setVelocity(afk::Random::randomFloat(2.0f, 2.5f), -5.0f);
      // emitter_3.addParticle(particle);
    }
  }

  void update(Uint32 delta) {
    Scene::update(delta);

    auto& smoke_emitter = get<afk::ParticleEmitter>(smoke_id);
    smoke_emitter.transform.x = input.mouseX();
    smoke_emitter.transform.y = input.mouseY();
  }

  void stop() { logger.log("Stopping!"); }

 private:
  ObjId smoke_id;
};

int main(int argv, char** args) {
  afk::Game game = afk::Game();

  afk::SceneService& scenes = afk::Services::getSceneService();
  scenes.addScene<DemoScene>("demo");
  scenes.setNextScene("demo");

  game.start();
  return 0;
}
