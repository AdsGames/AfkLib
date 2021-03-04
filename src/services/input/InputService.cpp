#include "services/input/InputService.h"

#include "common/Exceptions.h"
#include "services/Locator.h"

const float JOYSTICK_DEADZONE = 0.6f;

// Install core input services
InputService::InputService() {
  // Register service
  Locator::getEventQueue().registerService(this);

  // Set joystick enabled
  joystick_state.enabled = SDL_NumJoysticks() > 0;

  // Open joystick if enabled
  if (joystick_state.enabled) {
    SDL_JoystickOpen(0);
  }
}

InputService::~InputService() {
  // Unregister self
  Locator::getEventQueue().unregisterService(this);
}

// Get the name of service
std::string InputService::getName() const {
  return "Input Service";
}

// Process event
void InputService::notify(const SDL_Event& event) {
  switch (event.type) {
    case SDL_USEREVENT:
      if (event.user.code == 1) {
        update();
      }
      break;
    case SDL_KEYDOWN:
    case SDL_KEYUP:
      onKeyboardEvent(event.type, event.key);
      break;
    case SDL_JOYBUTTONDOWN:
    case SDL_JOYBUTTONUP:
      onJoystickEvent(event.type, event.jbutton);
      break;
    case SDL_JOYDEVICEADDED:
    case SDL_JOYDEVICEREMOVED:
      onJoystickReconfigureEvent();
      break;
    case SDL_MOUSEMOTION:
      onMouseEvent(event.motion);
      break;
    case SDL_MOUSEWHEEL:
      onMouseEvent(event.wheel);
      break;
    case SDL_MOUSEBUTTONUP:
    case SDL_MOUSEBUTTONDOWN:
      onMouseEvent(event.type, event.button);
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
void InputService::onJoystickEvent(const Uint32 event_type,
                                   const SDL_JoyButtonEvent event) {
  switch (event_type) {
    case SDL_JOYBUTTONDOWN:
      joystick_state.button[event.button] = true;
      break;
    case SDL_JOYBUTTONUP:
      joystick_state.button[event.button] = false;
      break;
    default:
      break;
  }
}

// Joystick axis event
void InputService::onJoystickEvent(const Uint32 event_type,
                                   const SDL_JoyAxisEvent event) {
  // Translated axis
  const int trans_axis = (JOY_MAX_AXES + event.axis) * 2;

  // Check if moved enough
  if (event.value > JOYSTICK_DEADZONE) {
    joystick_state.stick[trans_axis] = true;
  } else if (event.value < -JOYSTICK_DEADZONE) {
    joystick_state.stick[trans_axis + 1] = true;
  } else {
    joystick_state.stick[trans_axis] = false;
    joystick_state.stick[trans_axis + 1] = false;
  }
}

// Joystick reconfig event
void InputService::onJoystickReconfigureEvent() {
  joystick_state.enabled = SDL_NumJoysticks() > 0;

  // Open joystick if enabled
  if (joystick_state.enabled) {
    SDL_JoystickOpen(0);
  }
}

// Keyboard event
void InputService::onKeyboardEvent(const Uint32 event_type,
                                   const SDL_KeyboardEvent event) {
  switch (event_type) {
    case SDL_KEYDOWN:
      keyboard_state.key[event.keysym.scancode] = true;
      break;
    case SDL_KEYUP:
      keyboard_state.key[event.keysym.scancode] = false;
      break;
    default:
      break;
  }
}

// Mouse axis handler
void InputService::onMouseEvent(const SDL_MouseMotionEvent event) {
  mouse_state.x = (event.x - Locator::getDisplay().getTranslationX()) /
                  Locator::getDisplay().getScaleX();
  mouse_state.y = (event.y - Locator::getDisplay().getTranslationY()) /
                  Locator::getDisplay().getScaleY();
}

// Mouse axis handler
void InputService::onMouseEvent(const SDL_MouseWheelEvent event) {
  mouse_state.z = event.y;
}

// Mouse button handler
void InputService::onMouseEvent(const Uint32 event_type,
                                const SDL_MouseButtonEvent event) {
  switch (event_type) {
    case SDL_MOUSEBUTTONUP:
      if (event.button < MAX_MOUSE_BUTTONS) {
        mouse_state.button[event.button] = false;
      }
      break;
    case SDL_MOUSEBUTTONDOWN:
      if (event.button < MAX_MOUSE_BUTTONS) {
        mouse_state.button[event.button] = true;
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
