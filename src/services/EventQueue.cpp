#include <SDL2/SDL_events.h>
#include <algorithm>

#include "services/EventQueue.h"
#include "services/Locator.h"

// Create event queue
EventQueue::EventQueue() {
  Locator::getLogger().log("[Event Queue]: Starting up");

  // Events
  event_queue = al_create_event_queue();
}

EventQueue::~EventQueue() {
  Locator::getLogger().log("[Event Queue]: Shutting down");
}

void EventQueue::process() {
  SDL_Event ev;
  SDL_PollEvent(&ev);

  for (Service* service : services) {
    service->notify(ev);
  }
}

// Register service with event queue
void EventQueue::registerService(Service* service) {
  services.push_back(service);
}

// Unregister service from event queue
void EventQueue::unregisterService(Service* service) {
  services.erase(std::remove(services.begin(), services.end(), service));
}

// Add to queue
void EventQueue::registerSource(ALLEGRO_EVENT_SOURCE* source) {
  al_register_event_source(event_queue, source);
}

// Remove from queue
void EventQueue::unregisterSource(ALLEGRO_EVENT_SOURCE* source) {
  al_unregister_event_source(event_queue, source);
}
