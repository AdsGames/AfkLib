/**
 * @file Service.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Service subscriber that can listen for events
 * @version 0.1
 * @date 2020-11-27
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef AFK_SERVICE_H
#define AFK_SERVICE_H

#include <SDL2/SDL_events.h>
#include <string>

namespace afk {

/**
 * @brief Service parent type, interface to allow listening for events
 */
class Service {
 public:
  /**
   * @brief Virtual notify to be called by the queue
   *
   * @param event SDL event to be processed
   */
  virtual void notify(const SDL_Event& event) = 0;

  /**
   * @brief Get the Name of the service
   *
   * @return Name
   */
  virtual std::string getName() const = 0;
};

}  // namespace afk

#endif  // AFK_SERVICE_H
