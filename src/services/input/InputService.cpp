#include "services/input/InputService.h"

#include "common/Exceptions.h"
#include "services/Locator.h"

const float JOYSTICK_DEADZONE = 0.6f;

// Install core input services
InputService::InputService() {
  Locator::getLogger().log("[Input Service]: Starting up");

  // Install core allegro features
  if (!al_install_keyboard()) {
    throw InitException("Could not init keyboard");
  }
  if (!al_install_mouse()) {
    throw InitException("Could not init mouse");
  }
  if (!al_install_joystick()) {
    throw InitException("Could not init joystick");
  }

  // Register service
  Locator::getEventQueue().registerService(this);
  Locator::getEventQueue().registerSource(al_get_keyboard_event_source());
  Locator::getEventQueue().registerSource(al_get_joystick_event_source());
  Locator::getEventQueue().registerSource(al_get_mouse_event_source());

  // Set joystick enabled
  joystick_state.enabled = al_get_num_joysticks() > 0;
}

InputService::~InputService() {
  Locator::getLogger().log("[Input Service]: Shutting down");

  // Unregister self
  Locator::getEventQueue().unregisterService(this);
}

// Process event
void InputService::notify(const ALLEGRO_EVENT& event) {
  switch (event.type) {
    case ALLEGRO_EVENT_TIMER:
      if (al_get_timer_speed(event.timer.source) == 0.05f) {
        update();
      }
      break;
    case ALLEGRO_EVENT_KEY_DOWN:
    case ALLEGRO_EVENT_KEY_UP:
      onKeyboardEvent(event.type, event.keyboard.keycode);
      break;
    case ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN:
    case ALLEGRO_EVENT_JOYSTICK_BUTTON_UP:
      onJoystickEvent(event.type, event.joystick.button);
      break;
    case ALLEGRO_EVENT_JOYSTICK_CONFIGURATION:
      onJoystickReconfigureEvent();
      break;
    case ALLEGRO_EVENT_MOUSE_AXES:
      onMouseEvent(event.type, event.mouse.x, event.mouse.y, event.mouse.z);
      break;
    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
    case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
      onMouseEvent(event.type, event.mouse.button);
      break;
    default:
      break;
  }
}

// Update routine
void InputService::update() {
  mouse_state.update();
  keyboard_state.update();
  joystick_state.update();
}

// Joystick button event
void InputService::onJoystickEvent(ALLEGRO_EVENT_TYPE event_type,
                                   const int keycode) {
  switch (event_type) {
    case ALLEGRO_EVENT_JOYSTICK_BUTTON_DOWN:
      joystick_state.button[keycode] = true;
      break;
    case ALLEGRO_EVENT_JOYSTICK_BUTTON_UP:
      joystick_state.button[keycode] = false;
      break;
    default:
      break;
  }
}

// Joystick axis event
void InputService::onJoystickEvent(ALLEGRO_EVENT_TYPE event_type,
                                   const int stick,
                                   const int axis,
                                   const float position) {
  // Translated axis
  const int trans_axis = (stick * JOY_MAX_AXES + axis) * 2;

  switch (event_type) {
    case ALLEGRO_EVENT_JOYSTICK_AXIS:
      // Check if moved enough
      if (position > JOYSTICK_DEADZONE) {
        joystick_state.stick[trans_axis] = true;
      } else if (position < -JOYSTICK_DEADZONE) {
        joystick_state.stick[trans_axis + 1] = true;
      } else {
        joystick_state.stick[trans_axis] = false;
        joystick_state.stick[trans_axis + 1] = false;
      }
      break;
    default:
      break;
  }
}

// Joystick reconfig event
void InputService::onJoystickReconfigureEvent() {
  al_reconfigure_joysticks();
  joystick_state.enabled = al_get_num_joysticks() > 0;
}

// Keyboard event
void InputService::onKeyboardEvent(ALLEGRO_EVENT_TYPE event_type,
                                   const int keycode) {
  switch (event_type) {
    case ALLEGRO_EVENT_KEY_DOWN:
      keyboard_state.key[keycode] = true;
      break;
    case ALLEGRO_EVENT_KEY_UP:
      keyboard_state.key[keycode] = false;
      break;
    default:
      break;
  }
}

// Mouse axis handler
void InputService::onMouseEvent(ALLEGRO_EVENT_TYPE event_type,
                                const int x,
                                const int y,
                                const int z) {
  switch (event_type) {
    case ALLEGRO_EVENT_MOUSE_AXES:
      mouse_state.x = (x - Locator::getDisplay().getTranslationX()) /
                      Locator::getDisplay().getScaleX();
      mouse_state.y = (y - Locator::getDisplay().getTranslationY()) /
                      Locator::getDisplay().getScaleY();
      mouse_state.z = z;
      break;
    default:
      break;
  }
}

// Mouse button handler
void InputService::onMouseEvent(ALLEGRO_EVENT_TYPE event_type,
                                const unsigned int button) {
  switch (event_type) {
    case ALLEGRO_EVENT_MOUSE_BUTTON_DOWN:
      if (button < MAX_MOUSE_BUTTONS) {
        mouse_state.button[button] = true;
      }
      break;
    case ALLEGRO_EVENT_MOUSE_BUTTON_UP:
      if (button < MAX_MOUSE_BUTTONS) {
        mouse_state.button[button] = false;
      }
      break;
    default:
      break;
  }
}

// Get keyboard state
const KeyboardState& InputService::keyboard() {
  return keyboard_state;
}

// Get mouse state
const MouseState& InputService::mouse() {
  return mouse_state;
}

// Get joystick state
const JoystickState& InputService::joystick() {
  return joystick_state;
}
