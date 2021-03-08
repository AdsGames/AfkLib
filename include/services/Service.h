#ifndef SERVICES_SERVICE_H
#define SERVICES_SERVICE_H

#include <SDL2/SDL_events.h>
#include <string>

namespace afk {

/**
 * @brief Service parent type
 *
 * @author Allan Legemaate
 * @date 27/11/2020
 */
class Service {
 public:
  /**
   * @brief Virtual notify to be called by the queue
   *
   * @param event Allegero event to be processed
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

#endif  // SERVICES_SERVICE_H