#ifndef SERVICES_INPUT_INPUT_SERVICE_H
#define SERVICES_INPUT_INPUT_SERVICE_H

#include <SDL2/SDL_events.h>

#include "../Service.h"
#include "JoystickState.h"
#include "KeyboardState.h"
#include "MouseState.h"

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
   * @brief Get the name of service
   *
   * @return name
   */
  std::string getName() const;

  /**
   * @brief Notify input service of recent event
   *
   * @param event to process
   */
  void notify(const SDL_Event& event);

  /**
   * @brief Get keyboard state
   *
   * @return Keyboard state
   */
  const KeyboardState& keyboard();

  /**
   * @brief Get mouse state
   *
   * @return Mouse state
   */
  const MouseState& mouse();

  /**
   * @brief Get joystick state
   *
   * @return Joystick state
   */
  const JoystickState& joystick();

 private:
  /**
   * @brief Update last keys/buttons etc.
   *
   */
  void update();

  /**
   * @brief Joystick button event handler
   *
   * @param event_type Type of sdl event
   * @param keycode Keycode pressed
   */
  void onJoystickEvent(const Uint32 event_type, const SDL_JoyButtonEvent event);

  /**
   * @brief Joystick axis and stick event handler
   *
   * @param event_type Type of sdl event
   * @param stick Stick moved
   * @param axis Axis moved
   * @param position Axis/Stick position
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
   * @param keycode Keycode
   */
  void onKeyboardEvent(const Uint32 event_type, const SDL_KeyboardEvent event);

  /**
   * @brief Mouse axis handler
   *
   * @param event motion event
   */
  void onMouseEvent(const SDL_MouseWheelEvent event);

  /**
   * @brief Mouse wheel handler
   *
   * @param button button changed
   */
  void onMouseEvent(const SDL_MouseMotionEvent event);

  /**
   * @brief Mouse button handler
   *
   * @param event_type Type of sdl event
   * @param event button event
   */
  void onMouseEvent(const Uint32 event_type, const SDL_MouseButtonEvent event);

  /// Current keyboard state
  KeyboardState keyboard_state;

  /// Current mouse state
  MouseState mouse_state;

  /// Current joystick state
  JoystickState joystick_state;
};

#endif  // SERVICES_INPUT_INPUT_SERVICE_H
