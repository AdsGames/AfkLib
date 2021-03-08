/**
 * @file Game.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief The main entry point of a AFK program
 * @version 0.1
 * @date 2020-11-07
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INCLUDE_GAME_H_
#define INCLUDE_GAME_H_

#include <string>

#include "services/Service.h"

namespace afk {

/**
 * @brief Core game class, manages scenes and sets up locator and sdl
 *
 */
class Game : public Service {
 public:
  /**
   * @brief Construct a new Game object
   *
   */
  Game();

  /**
   * @brief Destroy the Game
   *
   */
  ~Game();

  /**
   * @brief Get the name of service
   *
   * @return name
   */
  std::string getName() const;

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
  void notify(const SDL_Event& ev);

 private:
  /**
   * @brief Sets up core engine features and sdl2
   *
   */
  void setup();

  /// Set to true on close from escape or x button
  bool closing = false;
};

}  // namespace afk

#endif  // INCLUDE_GAME_H_
