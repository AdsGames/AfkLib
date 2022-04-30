/**
 * @file InputService.cpp
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Implementation of InputService. Handles mouse, keyboard and
 * joystick.
 * @version 0.1
 * @date 2021-03-08
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "services/input/InputService.h"

#include "common/Exceptions.h"
#include "services/Services.h"

const float JOYSTICK_DEAD_ZONE = 0.6f;

namespace afk {

// Install core input services
InputService::InputService() {
  // Register service
  Services::getEventQueue().registerService(this);

  // Set joystick enabled
  joystickState.enabled = SDL_NumJoysticks() > 0;

  // Open joystick if enabled
  if (joystickState.enabled) {
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
  mouseState.update();
  keyboardState.update();
  joystickState.update();
}

// Joystick button event
void InputService::onJoystickEvent(const uint32_t eventType,
                                   const SDL_JoyButtonEvent event) {
  switch (eventType) {
    case SDL_JOYBUTTONDOWN:
      joystickState.button[event.button] = true;
      break;
    case SDL_JOYBUTTONUP:
      joystickState.button[event.button] = false;
      break;
    default:
      break;
  }
}

// Joystick axis event
void InputService::onJoystickEvent(const SDL_JoyAxisEvent event) {
  // Translated axis
  const int transAxis = (JOY_MAX_AXES + event.axis) * 2;

  // Check if moved enough
  if (event.value > JOYSTICK_DEAD_ZONE) {
    joystickState.stick[transAxis] = true;
  } else if (event.value < -JOYSTICK_DEAD_ZONE) {
    joystickState.stick[transAxis + 1] = true;
  } else {
    joystickState.stick[transAxis] = false;
    joystickState.stick[transAxis + 1] = false;
  }
}

// Joystick reconfigure event
void InputService::onJoystickReconfigureEvent() {
  joystickState.enabled = SDL_NumJoysticks() > 0;

  // Open joystick if enabled
  if (joystickState.enabled) {
    SDL_JoystickOpen(0);
  }
}

// Keyboard event
void InputService::onKeyboardEvent(const uint32_t eventType,
                                   const SDL_KeyboardEvent event) {
  switch (eventType) {
    case SDL_KEYDOWN:
      keyboardState.key[event.keysym.scancode] = true;
      break;
    case SDL_KEYUP:
      keyboardState.key[event.keysym.scancode] = false;
      break;
    default:
      break;
  }
}

// Mouse axis handler
void InputService::onMouseEvent(const SDL_MouseMotionEvent event) {
  mouseState.x = (event.x - Services::getDisplayService().getTranslationX()) /
                  Services::getDisplayService().getScaleX();
  mouseState.y = (event.y - Services::getDisplayService().getTranslationY()) /
                  Services::getDisplayService().getScaleY();
}

// Mouse axis handler
void InputService::onMouseEvent(const SDL_MouseWheelEvent event) {
  mouseState.z = event.y;
}

// Mouse button handler
void InputService::onMouseEvent(const uint32_t eventType,
                                const SDL_MouseButtonEvent event) {
  switch (eventType) {
    case SDL_MOUSEBUTTONUP:
      if (event.button < static_cast<int>(MouseButtons::Max)) {
        mouseState.button[event.button] = false;
      }
      break;
    case SDL_MOUSEBUTTONDOWN:
      if (event.button < static_cast<int>(MouseButtons::Max)) {
        mouseState.button[event.button] = true;
      }
      break;
    default:
      break;
  }
}

// Get key just down state
bool InputService::keyPressed(const Keys key) const {
  if (key > Keys::Max) {
    return false;
  }
  return keyboardState.keyPressed[static_cast<int>(key)];
}

// Get key just up state
bool InputService::keyReleased(const Keys key) const {
  if (key > Keys::Max) {
    return false;
  }
  return keyboardState.keyReleased[static_cast<int>(key)];
}

// Get key down state
bool InputService::keyDown(const Keys key) const {
  if (key > Keys::Max) {
    return false;
  }
  return keyboardState.key[static_cast<int>(key)];
}

// Get any key down state
bool InputService::anyKeyDown() const {
  return keyboardState.anyKeyDown;
}

// Get last key pressed
int InputService::lastKeyPressed() const {
  return keyboardState.lastKeyPressed;
}

// Get last key pressed
int InputService::lastKeyReleased() const {
  return keyboardState.lastKeyReleased;
}

// Get mouse button just down state
bool InputService::mousePressed(const MouseButtons button) const {
  if (button > MouseButtons::Max) {
    return false;
  }
  return mouseState.down[static_cast<int>(button)];
}

// Get mouse button just up state
bool InputService::mouseReleased(const MouseButtons button) const {
  if (button > MouseButtons::Max) {
    return false;
  }
  return mouseState.up[static_cast<int>(button)];
}

// Get mouse button down state
bool InputService::mouseDown(const MouseButtons button) const {
  if (button > MouseButtons::Max) {
    return false;
  }
  return mouseState.button[static_cast<int>(button)];
}

// Get mouse button down state
bool InputService::mouseOver(const Vec2 position, const Vec2 size) const {
  if (mouseState.x < position.x || mouseState.x > position.x + size.x ||
      mouseState.y < position.y || mouseState.y > position.y + size.y) {
    return false;
  }
  return true;
}

// Get mouse x position
int InputService::mouseX() const {
  return mouseState.x;
}

// Get mouse y position
int InputService::mouseY() const {
  return mouseState.y;
}

// Check if joystick enabled
bool InputService::joyEnabled() const {
  return joystickState.enabled;
}

// Get joy button just down state
bool InputService::joyPressed(const JoystickButtons button) const {
  return joystickState.buttonPressed[static_cast<int>(button)];
}

// Get joy button just up state
bool InputService::joyReleased(const JoystickButtons button) const {
  return joystickState.buttonReleased[static_cast<int>(button)];
}

// Get joy button down state
bool InputService::joyDown(const JoystickButtons button) const {
  return joystickState.button[static_cast<int>(button)];
}

}  // namespace afk
