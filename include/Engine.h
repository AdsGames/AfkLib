#ifndef ENGINE_ENGINE_H
#define ENGINE_ENGINE_H

#include <allegro5/allegro5.h>
#include <string>

#include "Service.h"

/**
 * @brief Core engine class, manages scenes and sets up locator and allegro
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
   * @brief Sets up core engine features and allegro 5
   *
   */
  void setup();

  /// Set to true on close from escape or x button
  bool closing = false;
};

#endif  // ENGINE_ENGINE_H