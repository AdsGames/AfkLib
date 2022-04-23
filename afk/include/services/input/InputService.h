/**
 * @file InputService.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief General Purpose input listener. Handles Mouse, Keyboard, Joystick
 * @version 0.1
 * @date 2020-11-07
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef AFK_INPUTSERVICE_H
#define AFK_INPUTSERVICE_H

#include <SDL2/SDL_events.h>
#include <iostream>
#include <string>

#include "../../common/Vec.h"
#include "../Service.h"
#include "JoystickState.h"
#include "KeyboardState.h"
#include "MouseState.h"

namespace afk {

/**
 * @brief General Purpose input listener
 *
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
  std::string getName() const override;

  /**
   * @brief Notify input service of recent event
   *
   * @param event SDL event to process
   */
  void notify(const SDL_Event& event) override;

  /**
   * @brief Get key just down state
   *
   * @param key Key to check state of
   *
   * @return Key state
   */
  bool keyPressed(Keys key) const;

  /**
   * @brief Get key just up state
   *
   * @param key Key to check state of
   *
   * @return Key state
   */
  bool keyReleased(Keys key) const;

  /**
   * @brief Get key down state
   *
   * @param key Key to check state of
   *
   * @return Key state
   */
  bool keyDown(Keys key) const;

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
  bool mousePressed(MouseButtons button) const;

  /**
   * @brief Get mouse button just up state
   *
   * @param button Button to check state of
   *
   * @return Key state
   */
  bool mouseReleased(MouseButtons button) const;

  /**
   * @brief Get mouse button down state
   *
   * @param button Button to check state of
   *
   * @return Key state
   */
  bool mouseDown(MouseButtons button) const;

  /**
   * @brief Get whether mouse is over a given area
   *
   * @param position Position to check
   * @param size Size of area
   *
   * @return Over state
   */
  bool mouseOver(Vec2 position, Vec2 size) const;

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
  bool joyPressed(JoystickButtons button) const;

  /**
   * @brief Get joy button just up state
   *
   * @param button Button to check state of
   *
   * @return Key state
   */
  bool joyReleased(JoystickButtons button) const;

  /**
   * @brief Get joy button down state
   *
   * @param button Button to check state of
   *
   * @return Key state
   */
  bool joyDown(JoystickButtons button) const;

 private:
  /**
   * @brief Joystick button event handler
   *
   * @param eventType Type of sdl event
   * @param event Sdl event to be processed
   */
  void onJoystickEvent(uint32_t eventType, SDL_JoyButtonEvent event);

  /**
   * @brief Joystick axis and stick event handler
   *
   * @param event_type Type of sdl event
   * @param event Sdl event to be processed
   */
  void onJoystickEvent(SDL_JoyAxisEvent event);

  /**
   * @brief Joystick configuration event
   *
   */
  void onJoystickReconfigureEvent();

  /**
   * @brief Keyboard event handler
   *
   * @param eventType Type of sdl event
   * @param event Sdl event to be processed
   */
  void onKeyboardEvent(uint32_t eventType, SDL_KeyboardEvent event);

  /**
   * @brief Mouse axis handler
   *
   * @param event Sdl event to be processed
   */
  void onMouseEvent(SDL_MouseWheelEvent event);

  /**
   * @brief Mouse wheel handler
   *
   * @param event Sdl event to be processed
   */
  void onMouseEvent(SDL_MouseMotionEvent event);

  /**
   * @brief Mouse button handler
   *
   * @param eventType Type of sdl event
   * @param event Sdl event to be processed
   */
  void onMouseEvent(uint32_t eventType, SDL_MouseButtonEvent event);

  /// Current keyboard state
  KeyboardState keyboardState;

  /// Current mouse state
  MouseState mouseState;

  /// Current joystick state
  JoystickState joystickState;
};

}  // namespace afk

#endif  // AFK_INPUTSERVICE_H

/**
 * @example ex_mouse.cpp
 * This example shows how to use the mouse
 */

/**
 * @example ex_keyboard.cpp
 * This example shows how to use the keyboard
 */
