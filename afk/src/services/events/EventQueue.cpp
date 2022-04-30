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

#include "services/Services.h"

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
  services.erase(std::remove(services.begin(), services.end(), service), services.end());
}

// Register user timer
SDL_TimerID EventQueue::registerTimer(const uint32_t time, const char code) {
  void* c = malloc(sizeof(code));
  memcpy(c, &code, sizeof(code));

  SDL_TimerID timerId = SDL_AddTimer(time, EventQueue::timerCallback, c);
  return timerId;
}

// Unregister user timer
void EventQueue::unregisterTimer(const SDL_TimerID timerId) {
  SDL_RemoveTimer(timerId);
}

// Timer callback
uint32_t EventQueue::timerCallback(uint32_t interval, void* param) {
  SDL_Event event;
  SDL_UserEvent userEvent;

  char code = *(reinterpret_cast<char*>(param));

  userEvent.type = SDL_USEREVENT;
  userEvent.code = code;
  userEvent.data1 = nullptr;
  userEvent.data2 = nullptr;

  event.type = SDL_USEREVENT;
  event.user = userEvent;

  SDL_PushEvent(&event);
  return interval;
}

}  // namespace afk
