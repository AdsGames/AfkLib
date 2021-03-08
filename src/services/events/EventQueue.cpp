/**
 * @file EventQueue.cpp
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Implementation of EventQueue
 * @version 0.1
 * @date 2020-11-27
 *
 * @copyright Copyright (c) 2021
 *
 */
#include <SDL2/SDL_events.h>
#include <algorithm>
#include <functional>

#include "services/Services.h"
#include "services/events/EventQueue.h"

namespace afk {

// Create event queue
EventQueue::EventQueue() {
  Services::getLoggingService().log("[Event Queue]: Starting up");
}

EventQueue::~EventQueue() {
  Services::getLoggingService().log("[Event Queue]: Shutting down");
}

void EventQueue::process() {
  SDL_Event ev;
  while (SDL_PollEvent(&ev)) {
    for (Service* service : services) {
      service->notify(ev);
    }
  }
}

// Register service with event queue
void EventQueue::registerService(Service* service) {
  Services::getLoggingService().log("[" + service->getName() + "] Starting up");
  services.push_back(service);
}

// Unregister service from event queue
void EventQueue::unregisterService(Service* service) {
  Services::getLoggingService().log("[" + service->getName() +
                                    "] Shutting down");
  services.erase(std::remove(services.begin(), services.end(), service));
}

// Register user timer
SDL_TimerID EventQueue::registerTimer(const Uint32 time, const char code) {
  void* c = malloc(sizeof(code));
  memcpy(c, &code, sizeof(code));

  SDL_TimerID timer_id = SDL_AddTimer(time, EventQueue::timerCallback, c);
  return timer_id;
}

// Unregister user timer
void EventQueue::unregisterTimer(const SDL_TimerID timer_id) {
  SDL_RemoveTimer(timer_id);
}

// Timer callback
Uint32 EventQueue::timerCallback(Uint32 interval, void* param) {
  SDL_Event event;
  SDL_UserEvent userevent;

  char code = *(reinterpret_cast<char*>(param));

  userevent.type = SDL_USEREVENT;
  userevent.code = code;
  userevent.data1 = NULL;
  userevent.data2 = NULL;

  event.type = SDL_USEREVENT;
  event.user = userevent;

  SDL_PushEvent(&event);
  return interval;
}

}  // namespace afk
