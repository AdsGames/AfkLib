#include "services/input/InputService.h"

#include "common/Exceptions.h"
#include "services/Services.h"

const float JOYSTICK_DEADZONE = 0.6f;

namespace afk {

// Install core input services
InputService::InputService() {
  // Register service
  Services::getEventQueue().registerService(this);

  // Set joystick enabled
  joystick_state.enabled = SDL_NumJoysticks() > 0;

  // Open joystick if enabled
  if (joystick_state.enabled) {
    SDL_JoystickOpen(0);
  }
}

InputService::~InputService() {
  // Unregister self
  Services::getEventQueue().unregisterService(this);
}

// Get the name of service
std::string InputService::getName() const {
  return "Input Service";
}

// Process event
void InputService::notify(const SDL_Event& event) {
  switch (event.type) {
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
void InputService::onJoystickEvent(const SDL_JoyAxisEvent event) {
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
  mouse_state.x = (event.x - Services::getDisplayService().getTranslationX()) /
                  Services::getDisplayService().getScaleX();
  mouse_state.y = (event.y - Services::getDisplayService().getTranslationY()) /
                  Services::getDisplayService().getScaleY();
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
      if (event.button < (int)MouseButtons::BUTTON_MAX) {
        mouse_state.button[event.button] = false;
      }
      break;
    case SDL_MOUSEBUTTONDOWN:
      if (event.button < (int)MouseButtons::BUTTON_MAX) {
        mouse_state.button[event.button] = true;
      }
      break;
    default:
      break;
  }
}

// Get key just down state
bool InputService::keyPressed(const Keys key) const {
  if (key > Keys::KEY_MAX) {
    return false;
  }
  return keyboard_state.keyPressed[(int)key];
}

// Get key just up state
bool InputService::keyReleased(const Keys key) const {
  if (key > Keys::KEY_MAX) {
    return false;
  }
  return keyboard_state.keyReleased[(int)key];
}

// Get key down state
bool InputService::keyDown(const Keys key) const {
  if (key > Keys::KEY_MAX) {
    return false;
  }
  return keyboard_state.key[(int)key];
}

// Get any key down state
bool InputService::anyKeyDown() const {
  return keyboard_state.anyKeyDown;
}

// Get last key pressed
int InputService::lastKeyPressed() const {
  return keyboard_state.lastKeyPressed;
}

// Get last key pressed
int InputService::lastKeyReleased() const {
  return keyboard_state.lastKeyReleased;
}

// Get mouse button just down state
bool InputService::mousePressed(const MouseButtons button) const {
  if (button > MouseButtons::BUTTON_MAX) {
    return false;
  }
  return mouse_state.down[(int)button];
}

// Get mouse button just up state
bool InputService::mouseReleased(const MouseButtons button) const {
  if (button > MouseButtons::BUTTON_MAX) {
    return false;
  }
  return mouse_state.up[(int)button];
}

// Get mouse button down state
bool InputService::mouseDown(const MouseButtons button) const {
  if (button > MouseButtons::BUTTON_MAX) {
    return false;
  }
  return mouse_state.button[(int)button];
}

// Get mouse x position
int InputService::mouseX() const {
  return mouse_state.x;
}

// Get mouse y position
int InputService::mouseY() const {
  return mouse_state.y;
}

// Check if joystick enabled
bool InputService::joyEnabled() const {
  return joystick_state.enabled;
}

// Get joy button just down state
bool InputService::joyPressed(const JoystickButtons button) const {
  return joystick_state.buttonPressed[(int)button];
}

// Get joy button just up state
bool InputService::joyReleased(const JoystickButtons button) const {
  return joystick_state.buttonReleased[(int)button];
}

// Get joy button down state
bool InputService::joyDown(const JoystickButtons button) const {
  return joystick_state.button[(int)button];
}

}  // namespace afk