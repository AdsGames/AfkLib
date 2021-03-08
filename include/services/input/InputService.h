#ifndef INCLUDE_SERVICES_INPUT_INPUTSERVICE_H_
#define INCLUDE_SERVICES_INPUT_INPUTSERVICE_H_

#include <SDL2/SDL_events.h>
#include <iostream>
#include <string>

#include "../Service.h"
#include "JoystickState.h"
#include "KeyboardState.h"
#include "MouseState.h"

namespace afk {

/**
 * @brief General Purpose input listener
 *
 * @date 2020-11-07
 * @author Allan Legemaate (alegemaate@gmail.com)
 */
class InputService : public Service {
 public:
  /**
   * @brief Construct a new InputService object
   * Installs core input services on first init
   *
   */
  InputService();

  /**
   * @brief Destroy the Input object
   *
   */
  virtual ~InputService();

  /**
   * @brief Update last keys/buttons etc.
   *
   */
  void update();

  /**
   * @brief Get the name of service
   *
   * @return name
   */
  std::string getName() const;

  /**
   * @brief Notify input service of recent event
   *
   * @param event SDL event to process
   */
  void notify(const SDL_Event& event);

  /**
   * @brief Get key just down state
   *
   * @param key Key to check state of
   *
   * @return Key state
   */
  bool keyPressed(const Keys key) const;

  /**
   * @brief Get key just up state
   *
   * @param key Key to check state of
   *
   * @return Key state
   */
  bool keyReleased(const Keys key) const;

  /**
   * @brief Get key down state
   *
   * @param key Key to check state of
   *
   * @return Key state
   */
  bool keyDown(const Keys key) const;

  /**
   * @brief Get if any key is down
   *
   * @return Key down state
   */
  bool anyKeyDown() const;

  /**
   * @brief Get last key down
   *
   * @return Last key
   */
  int lastKeyPressed() const;

  /**
   * @brief Get last key released
   *
   * @return Last key
   */
  int lastKeyReleased() const;

  /**
   * @brief Get mouse button just down state
   *
   * @param button Button to check state of
   *
   * @return Key state
   */
  bool mousePressed(const MouseButtons button) const;

  /**
   * @brief Get mouse button just up state
   *
   * @param button Button to check state of
   *
   * @return Key state
   */
  bool mouseReleased(const MouseButtons button) const;

  /**
   * @brief Get mouse button down state
   *
   * @param button Button to check state of
   *
   * @return Key state
   */
  bool mouseDown(const MouseButtons button) const;

  /**
   * @brief Get mouse x position
   *
   * @return Mouse x position
   */
  int mouseX() const;

  /**
   * @brief Get mouse y position
   *
   * @return Mouse y position
   */
  int mouseY() const;

  /**
   * @brief Get joystick status
   *
   * @return Joystick enabled status
   */
  bool joyEnabled() const;

  /**
   * @brief Get joy button just down state
   *
   * @param button Button to check state of
   *
   * @return Key state
   */
  bool joyPressed(const JoystickButtons button) const;

  /**
   * @brief Get joy button just up state
   *
   * @param button Button to check state of
   *
   * @return Key state
   */
  bool joyReleased(const JoystickButtons button) const;

  /**
   * @brief Get joy button down state
   *
   * @param button Button to check state of
   *
   * @return Key state
   */
  bool joyDown(const JoystickButtons button) const;

 private:
  /**
   * @brief Joystick button event handler
   *
   * @param event_type Type of sdl event
   * @param event Sdl event to be processed
   */
  void onJoystickEvent(const Uint32 event_type, const SDL_JoyButtonEvent event);

  /**
   * @brief Joystick axis and stick event handler
   *
   * @param event_type Type of sdl event
   * @param event Sdl event to be processed
   */
  void onJoystickEvent(const SDL_JoyAxisEvent event);

  /**
   * @brief Joystick configuration event
   *
   */
  void onJoystickReconfigureEvent();

  /**
   * @brief Keyboard event handler
   *
   * @param event_type Type of sdl event
   * @param event Sdl event to be processed
   */
  void onKeyboardEvent(const Uint32 event_type, const SDL_KeyboardEvent event);

  /**
   * @brief Mouse axis handler
   *
   * @param event Sdl event to be processed
   */
  void onMouseEvent(const SDL_MouseWheelEvent event);

  /**
   * @brief Mouse wheel handler
   *
   * @param event Sdl event to be processed
   */
  void onMouseEvent(const SDL_MouseMotionEvent event);

  /**
   * @brief Mouse button handler
   *
   * @param event_type Type of sdl event
   * @param event Sdl event to be processed
   */
  void onMouseEvent(const Uint32 event_type, const SDL_MouseButtonEvent event);

  /// Current keyboard state
  KeyboardState keyboard_state;

  /// Current mouse state
  MouseState mouse_state;

  /// Current joystick state
  JoystickState joystick_state;
};

}  // namespace afk

#endif  // INCLUDE_SERVICES_INPUT_INPUTSERVICE_H_
