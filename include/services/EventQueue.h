#ifndef SERVICES_EVENT_QUEUE_H
#define SERVICES_EVENT_QUEUE_H

#include <SDL2/SDL.h>
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
   * @brief Register user timer
   *
   * @param source to hook into queue
   */
  SDL_TimerID registerTimer(const Uint32 time, const char code);

  /**
   * @brief Unregister user timer
   *
   * @param source to remove from queue
   */
  void unregisterTimer(const SDL_TimerID code);

  /**
   * @brief Timer callback for registered timers
   *
   * @param interval to run at
   * @param param user defined params
   */
  static Uint32 timerCallback(Uint32 interval, void* param);

 private:
  /// List of services which must be notified
  std::vector<Service*> services;
};

#endif  // SERVICES_EVENT_QUEUE_H