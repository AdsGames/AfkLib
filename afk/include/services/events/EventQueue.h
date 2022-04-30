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
#ifndef AFK_EVENTQUEUE_H
#define AFK_EVENTQUEUE_H

#include <SDL2/SDL_timer.h>
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
  SDL_TimerID registerTimer(uint32_t time, char code);

  /**
   * @brief Unregister user timer
   *
   * @param timerId Timer to remove from queue
   */
  void unregisterTimer(SDL_TimerID timerId);

  /**
   * @brief Timer callback for registered timers
   *
   * @param interval MS per call, interval to run at
   * @param param User defined params
   */
  static uint32_t timerCallback(uint32_t interval, void* param);

 private:
  /// List of services which must be notified
  std::vector<Service*> services;
};

}  // namespace afk

#endif  // AFK_EVENTQUEUE_H
