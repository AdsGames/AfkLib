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
#include "../include/components/Particle.h"
#include "../include/components/ParticleEmitter.h"
#include "../include/components/Transform.h"
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

    emitter_1_id = createEntity();
    auto& emitter_1 = createComponent<afk::ParticleEmitter>(emitter_1_id, 10);
    createComponent<afk::Transform>(emitter_1_id, afk::Vec3(256, 256, 0),
                                    afk::Vec2(30, 30));

    for (int i = 0; i < 100; i++) {
      auto& [particle, physics] = emitter_1.addParticle();
      particle.setType(afk::ParticleType::SQUARE);
      particle.setLifespan(afk::random::randomInt(100, 1000));
      particle.setSize(10.0f, 3.0f);
      particle.setColor(afk::color::rgb(128, 22, 22),
                        afk::color::rgb(100, 100, 100));
      physics.setVelocity(afk::random::randomFloat(-5.0f, 5.0f),
                          afk::random::randomFloat(-1.0f, -2.0f));
      physics.setAcceleration(0, 2.0f);
    }

    emitter_2_id = createEntity();
    auto& emitter_2 = createComponent<afk::ParticleEmitter>(emitter_2_id, 10);
    createComponent<afk::Transform>(emitter_2_id, afk::Vec3(128, 256, 0),
                                    afk::Vec2(1, 1));

    for (int i = 0; i < 100; i++) {
      auto& [particle, physics] = emitter_2.addParticle();
      particle.setType(afk::ParticleType::CIRCLE);
      particle.setLifespan(afk::random::randomInt(1000, 2000));
      particle.setSize(3.0f, 2.0f);
      particle.setColor(afk::color::blue, afk::color::white);
      physics.setVelocity(afk::random::randomFloat(-20.0, 20.0), -200.0f);
      physics.setAcceleration(0, 200.0f);
    }

    emitter_3_id = createEntity();
    auto& emitter_3 = createComponent<afk::ParticleEmitter>(emitter_3_id, 10);
    createComponent<afk::Transform>(emitter_3_id, afk::Vec3(384, 256, 0),
                                    afk::Vec2(5, 5));

    for (int i = 0; i < 400; i++) {
      auto& [particle, physics] = emitter_3.addParticle();
      particle.setType(afk::ParticleType::IMAGE);
      particle.setLifespan(afk::random::randomInt(800, 1500));
      particle.setSize(16.0f, 20.0f);
      particle.setTexture("fuzzball");
      physics.setVelocity(afk::random::randomFloat(2.0f, 2.5f), -5.0f);
    }
  }

  void update(Uint32 delta) {
    Scene::update(delta);

    auto& smoke_transform = getComponent<afk::Transform>(emitter_3_id);
    smoke_transform.position.x = input.mouseX();
    smoke_transform.position.y = input.mouseY();
  }

  void stop() { logger.log("Stopping!"); }

 private:
  entt::entity emitter_1_id;
  entt::entity emitter_2_id;
  entt::entity emitter_3_id;
};

int main(int argv, char** args) {
  afk::Game game = afk::Game();

  afk::SceneService& scenes = afk::Services::getSceneService();
  scenes.addScene<DemoScene>("demo");
  scenes.setNextScene("demo");

  game.start();
  return 0;
}
