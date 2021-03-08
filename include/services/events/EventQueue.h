/**
 * @file EventQueue.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Handles SDL_Events from main SDL_Queue.
 * Can be hooked  into by other services and notified when changes happen.
 * @version 0.1
 * @date 2020-11-27
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INCLUDE_SERVICES_EVENTS_EVENTQUEUE_H_
#define INCLUDE_SERVICES_EVENTS_EVENTQUEUE_H_

#include <SDL2/SDL.h>
#include <vector>

#include "../Service.h"

namespace afk {

/**
 * @brief Houses event queue and works as
 *
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
   * @param service Service to hook into queue
   */
  void registerService(Service* service);

  /**
   * @brief Unregister service from queue
   *
   * @param service Service to remove from queue
   */
  void unregisterService(Service* service);

  /**
   * @brief Register user timer
   *
   * @param time Time in ms to call timer at
   * @param code User defined code to inject into timer
   */
  SDL_TimerID registerTimer(const Uint32 time, const char code);

  /**
   * @brief Unregister user timer
   *
   * @param timer Timer to remove from queue
   */
  void unregisterTimer(const SDL_TimerID timer);

  /**
   * @brief Timer callback for registered timers
   *
   * @param interval MS per call, interval to run at
   * @param param User defined params
   */
  static Uint32 timerCallback(Uint32 interval, void* param);

 private:
  /// List of services which must be notified
  std::vector<Service*> services;
};

}  // namespace afk

#endif  // INCLUDE_SERVICES_EVENTS_EVENTQUEUE_H_
