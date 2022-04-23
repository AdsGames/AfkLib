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
#include "../include/common/Color.h"
#include "../include/common/Vec.h"
#include "../include/common/random.h"
#include "../include/components/components.h"
#include "../include/scene/Scene.h"

class DemoScene : public afk::Scene {
 public:
  void start() {
    logger.log("Starting!");

    display.setWindowSize(512, 512);
    display.setBufferSize(512, 512);
    display.setMode(afk::DisplayMode::Windowed);
    display.setTitle("ex_particles");
    display.setBackgroundColor(afk::color::black);

    assets.loadImage("fuzzball", "assets/fuzzball.png");

    emitterEntity1 = createEntity();
    auto& emitter1 = createComponent<afk::ParticleEmitter>(emitterEntity1, 10);
    createComponent<afk::Transform>(emitterEntity1, afk::Vec3(256, 256, 0),
                                    afk::Vec2(30, 30));

    for (int i = 0; i < 100; i++) {
      auto& [particle, physics] = emitter1.addParticle();
      particle.setType(afk::ParticleType::Square);
      particle.setLifespan(afk::random::randomInt(100, 1000));
      particle.setSize(10.0f, 3.0f);
      particle.setColor(afk::color::rgb(128, 22, 22),
                        afk::color::rgb(100, 100, 100));
      physics.setVelocity(afk::random::randomFloat(-5.0f, 5.0f),
                          afk::random::randomFloat(-1.0f, -2.0f));
      physics.setAcceleration(0, 2.0f);
    }

    emitterEntity2 = createEntity();
    auto& emitter2 = createComponent<afk::ParticleEmitter>(emitterEntity2, 10);
    createComponent<afk::Transform>(emitterEntity2, afk::Vec3(128, 256, 0),
                                    afk::Vec2(1, 1));

    for (int i = 0; i < 100; i++) {
      auto& [particle, physics] = emitter2.addParticle();
      particle.setType(afk::ParticleType::Circle);
      particle.setLifespan(afk::random::randomInt(1000, 2000));
      particle.setSize(3.0f, 2.0f);
      particle.setColor(afk::color::blue, afk::color::white);
      physics.setVelocity(afk::random::randomFloat(-20.0, 20.0), -200.0f);
      physics.setAcceleration(0, 200.0f);
    }

    emitterEntity3 = createEntity();
    auto& emitter3 = createComponent<afk::ParticleEmitter>(emitterEntity3, 10);
    createComponent<afk::Transform>(emitterEntity3, afk::Vec3(384, 256, 0),
                                    afk::Vec2(5, 5));

    for (int i = 0; i < 400; i++) {
      auto& [particle, physics] = emitter3.addParticle();
      particle.setType(afk::ParticleType::Image);
      particle.setLifespan(afk::random::randomInt(800, 1500));
      particle.setSize(16.0f, 20.0f);
      particle.setTexture("fuzzball");
      physics.setVelocity(afk::random::randomFloat(2.0f, 2.5f), -5.0f);
    }
  }

  void update(uint32_t delta) {
    Scene::update(delta);

    auto& smoke_transform = getComponent<afk::Transform>(emitterEntity3);
    smoke_transform.position.x = input.mouseX();
    smoke_transform.position.y = input.mouseY();
  }

  void stop() { logger.log("Stopping!"); }

 private:
  afk::Entity emitterEntity1;
  afk::Entity emitterEntity2;
  afk::Entity emitterEntity3;
};

int main(int argv, char** args) {
  afk::Game game = afk::Game();

  afk::SceneService& scenes = afk::Services::getSceneService();
  scenes.addScene<DemoScene>("demo");
  scenes.setNextScene("demo");

  game.start();
  return 0;
}
