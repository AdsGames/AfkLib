#include "input/Input.h"

#include "Locator.h"

const float JOYSTICK_DEADZONE = 0.6f;

// Create and register input queue
void Input::registerEvents(ALLEGRO_EVENT_QUEUE* queue) {
  // Register listeners
  al_register_event_source(queue, al_get_keyboard_event_source());
  al_register_event_source(queue, al_get_joystick_event_source());
  al_register_event_source(queue, al_get_mouse_event_source());

  // Set joystick enabled
  joystick_state.enabled = al_get_num_joysticks() > 0;
}

// Handle events
void Input::processEvent(const ALLEGRO_EVENT& event) {
  switch (event.type) {
    case ALLEGRO_EVENT_TIMER:
      update();
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
void Input::update() {
  mouse_state.update();
  keyboard_state.update();
  joystick_state.update();
}

// Joystick button event
void Input::onJoystickEvent(ALLEGRO_EVENT_TYPE event_type, const int keycode) {
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
void Input::onJoystickEvent(ALLEGRO_EVENT_TYPE event_type,
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
void Input::onJoystickReconfigureEvent() {
  al_reconfigure_joysticks();
  joystick_state.enabled = al_get_num_joysticks() > 0;
}

// Keyboard event
void Input::onKeyboardEvent(ALLEGRO_EVENT_TYPE event_type, const int keycode) {
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
void Input::onMouseEvent(ALLEGRO_EVENT_TYPE event_type,
                         const int x,
                         const int y,
                         const int z) {
  switch (event_type) {
    case ALLEGRO_EVENT_MOUSE_AXES:
      mouse_state.x = (x - Locator::getWindow().getTranslationX()) /
                      Locator::getWindow().getScaleX();
      mouse_state.y = (y - Locator::getWindow().getTranslationY()) /
                      Locator::getWindow().getScaleY();
      mouse_state.z = z;
      break;
    default:
      break;
  }
}

// Mouse button handler
void Input::onMouseEvent(ALLEGRO_EVENT_TYPE event_type,
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
const KeyboardState& Input::keyboard() {
  return keyboard_state;
}

// Get mouse state
const MouseState& Input::mouse() {
  return mouse_state;
}

// Get joystick state
const JoystickState& Input::joystick() {
  return joystick_state;
}
