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
#include "../include/components/ui.h"
#include "../include/scene/Scene.h"

class DemoScene : public afk::Scene {
 public:
  void start() override {
    logger.log("Starting!");

    display.setWindowSize(512, 512);
    display.setBufferSize(512, 512);
    display.setMode(afk::DisplayMode::Windowed);
    display.setTitle("ex_particles");
    display.setBackgroundColor(afk::color::black);

    assets.loadImage("fuzzball", "assets/fuzzball.png");
    assets.loadFont("freesans", "assets/freesans.ttf", 24);

    // Weird box thing
    emitterEntity1 = createEntity();
    auto& emitter1 =
        createComponent<afk::ParticleEmitter>(emitterEntity1, 10.0f);
    createComponent<afk::Transform>(emitterEntity1, afk::Vec3(256, 256, 0),
                                    afk::Vec2(30, 30));

    for (int i = 0; i < 100; i++) {
      auto& [particle, physics] = emitter1.addPrefab();
      particle.type = afk::ParticleType::Square;
      particle.lifespan = afk::random::randomInt(100, 1000);
      particle.startSize = 10.0f, particle.endSize = 3.0f;
      particle.startColor = afk::color::rgb(128, 22, 22);
      particle.endColor = afk::color::rgb(100, 100, 100);
      physics.velocity = {afk::random::randomFloat(-5.0f, 5.0f),
                          afk::random::randomFloat(-1.0f, -2.0f)};
      physics.acceleration = {0, 2.0f};
    }

    // Water
    emitterEntity2 = createEntity();
    auto& emitter2 =
        createComponent<afk::ParticleEmitter>(emitterEntity2, 10.0f);
    createComponent<afk::Transform>(emitterEntity2, afk::Vec3(64, 256, 0),
                                    afk::Vec2(1, 1));

    for (int i = 0; i < 100; i++) {
      auto& [particle, physics] = emitter2.addPrefab();
      particle.type = afk::ParticleType::Circle;
      particle.lifespan = afk::random::randomInt(1000, 2000);
      particle.startSize = 3.0f;
      particle.endSize = 2.0f;
      particle.startColor = afk::color::blue;
      particle.endColor = afk::color::white;
      physics.velocity = {afk::random::randomFloat(-20.0, 20.0),
                          afk::random::randomFloat(-200.0f, -220.0f)};
      physics.acceleration = {0, 200.0f};
    }

    // Smoke
    emitterEntity3 = createEntity();
    auto& emitter3 =
        createComponent<afk::ParticleEmitter>(emitterEntity3, 10.0f);
    createComponent<afk::Transform>(emitterEntity3, afk::Vec3(0, 0, 0),
                                    afk::Vec2(5, 5));

    for (int i = 0; i < 400; i++) {
      auto& [particle, physics] = emitter3.addPrefab();
      particle.type = afk::ParticleType::Image;
      particle.lifespan = 3000;
      particle.startSize = 24.0f;
      particle.endSize = 48.0f;
      particle.texture = "fuzzball";
      physics.velocity = {2.0f, -10.0f};
      physics.acceleration = {10.0f, 0};
    }

    emitterEntity4 = createEntity();
    auto& emitter4 =
        createComponent<afk::ParticleEmitter>(emitterEntity4, 10.0f);
    createComponent<afk::Transform>(emitterEntity4, afk::Vec3(128, 256, 0),
                                    afk::Vec2(1, 1));

    // Sparks
    for (int i = 0; i < 400; i++) {
      auto& [particle, physics] = emitter4.addPrefab();
      particle.type = afk::ParticleType::Square;
      particle.startColor = afk::color::rgba(128, 20, 20, 128);
      particle.endColor = afk::color::rgba(200, 200, 200, 0);
      particle.lifespan = afk::random::randomInt(400, 500);
      particle.startSize = 3.0f;
      particle.endSize = 1.0f;
      physics.velocity = {afk::random::randomFloat(-40.0f, 40.0f),
                          afk::random::randomFloat(-40.0f, 40.0f)};
      physics.acceleration = {0, 200.0f};
    }

    // FPS label
    fpsLabel = createEntity();
    createComponent<afk::Transform>(fpsLabel, afk::Vec3(10, 5, 0));
    auto& fpsLabelComponent = createComponent<afk::Label>(fpsLabel);
    fpsLabelComponent.font = "freesans";
    fpsLabelComponent.color = afk::color::white;

    countLabel = createEntity();
    createComponent<afk::Transform>(countLabel, afk::Vec3(10, 20, 0));
    auto& countLabelComponent = createComponent<afk::Label>(countLabel);
    countLabelComponent.font = "freesans";
    countLabelComponent.color = afk::color::white;
  }

  void update(uint32_t delta) override {
    Scene::update(delta);

    // Move smoke to mouse
    auto& smoke_transform = getComponent<afk::Transform>(emitterEntity3);
    smoke_transform.position.x = input.mouseX();
    smoke_transform.position.y = input.mouseY();

    // Set fps label
    int fps = display.getFps();
    auto& fpsLabelComponent = getComponent<afk::Label>(fpsLabel);
    fpsLabelComponent.text = "FPS: " + std::to_string(fps);

    // Set count label
    int count = 0;
    getRegistry().view<afk::Particle>().each([&count](auto&) { count++; });
    auto& countLabelComponent = getComponent<afk::Label>(countLabel);
    countLabelComponent.text = "Count: " + std::to_string(count);
  }

  void stop() override { logger.log("Stopping!"); }

 private:
  afk::Entity emitterEntity1;
  afk::Entity emitterEntity2;
  afk::Entity emitterEntity3;
  afk::Entity emitterEntity4;

  afk::Entity fpsLabel;
  afk::Entity countLabel;
};

int main(int argv, char** args) {
  afk::Game game = afk::Game();

  afk::SceneService& scenes = afk::Services::getSceneService();
  scenes.addScene<DemoScene>("demo");
  scenes.setNextScene("demo");

  game.start();
  return 0;
}
