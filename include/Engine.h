#ifndef ENGINE_H
#define ENGINE_H

#include <string>

#include "services/Service.h"

/**
 * @brief Core engine class, manages scenes and sets up locator and sdl
 *
 * @author Allan Legemaate
 * @date 7/11/2020
 */
class Engine : public Service {
 public:
  /**
   * @brief Construct a new Engine object
   *
   */
  Engine();

  /**
   * @brief Starts the main game loop
   *
   * @param scene_id Initial scene to start with
   */
  void start();

  /**
   * @brief Notify about changes in queue
   *
   * @param ev event to be processed
   */
  void notify(const ALLEGRO_EVENT& ev);

 private:
  /**
   * @brief Sets up core engine features and sdl2
   *
   */
  void setup();

  /// Set to true on close from escape or x button
  bool closing = false;
};

#endif  // ENGINE_H