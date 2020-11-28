#ifndef ENGINE_EVENT_QUEUE_H
#define ENGINE_EVENT_QUEUE_H

#include <allegro5/allegro.h>
#include <vector>

#include "Service.h"

/**
 * @brief Houses event queue and works as
 *
 * @author Allan Legemaate
 * @date 27/11/2020
 */
class EventQueue {
 public:
  /**
   * @brief Construct a new Event Queue object
   *
   */
  EventQueue();

  /**
   * @brief Destroy the Event Queue object
   *
   */
  virtual ~EventQueue();

  /**
   * @brief Process events in event queue
   *
   */
  void process();

  /**
   * @brief Register service to be notified
   *
   * @param service to hook into queue
   */
  void registerService(Service* service);

  /**
   * @brief Unregister service from queue
   *
   * @param service to remove from queue
   */
  void unregisterService(Service* service);

  /**
   * @brief Register source with queue
   *
   * @param source to hook into queue
   */
  void registerSource(ALLEGRO_EVENT_SOURCE* source);

  /**
   * @brief Unregister source with queue
   *
   * @param source to remove from queue
   */
  void unregisterSource(ALLEGRO_EVENT_SOURCE* source);

 private:
  /// Main event queue
  ALLEGRO_EVENT_QUEUE* event_queue = nullptr;

  /// List of services which must be notified
  std::vector<Service*> services;
};

#endif  // ENGINE_EVENT_QUEUE_H