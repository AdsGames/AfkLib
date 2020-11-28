#ifndef ENGINE_SERVICE_H
#define ENGINE_SERVICE_H

#include <allegro5/allegro.h>

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
  virtual void notify(const ALLEGRO_EVENT& event) = 0;
};

#endif  // ENGINE_SERVICE_H