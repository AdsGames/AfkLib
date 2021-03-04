
#ifndef SERVICES_INPUT_JOYSTICK_STATE_H
#define SERVICES_INPUT_JOYSTICK_STATE_H

#include <SDL2/SDL_events.h>

#include "JoystickCodes.h"

/// Max sticks
const int JOY_MAX_STICKS = 128;

/// Max axes
const int JOY_MAX_AXES = 128;

/// Max sticks
const int JOY_MAX_STICK_BOOLEANS = JOY_MAX_STICKS * JOY_MAX_AXES * 2;

/// Max buttons
const int JOY_MAX_BUTTONS = 128;

/**
 * @brief Joystick state
 *
 */
struct JoystickState {
  /// Individual button states
  bool button[JOY_MAX_BUTTONS] = {false};

  /// Buttons just pressed
  bool buttonPressed[JOY_MAX_BUTTONS] = {false};

  /// Buttons just released
  bool buttonReleased[JOY_MAX_BUTTONS] = {false};

  /// Id of last button pressed
  int lastButtonPressed = -1;

  /// Id of last button released
  int lastButtonReleased = -1;

  /// True if any button down
  bool anyButtonPressed = false;

  /// Stick axis is active
  bool stick[JOY_MAX_STICK_BOOLEANS] = {false};

  /// Stick axis just moved
  bool stickMoved[JOY_MAX_STICK_BOOLEANS] = {false};

  /// Stick axis just moved back
  bool stickReleased[JOY_MAX_STICK_BOOLEANS] = {false};

  /// Previous button states
  bool lastTicksButton[JOY_MAX_BUTTONS] = {false};

  /// Previous stick states
  bool lastTicksStick[JOY_MAX_STICK_BOOLEANS] = {false};

  /// Joystick is enabled or not
  bool enabled = false;

  /**
   * @brief Update the joystick state
   *
   */
  void update() {
    // Reset last button
    lastButtonPressed = -1;
    lastButtonReleased = -1;
    anyButtonPressed = false;

    // Check stick just moved
    for (int i = 0; i < JOY_MAX_STICK_BOOLEANS; i++) {
      // Clear old values
      stickMoved[i] = false;
      stickReleased[i] = false;

      // Pressed since last tick?
      if (stick[i] == true && lastTicksStick[i] == false) {
        stickMoved[i] = true;
      }

      // Released since last tick?
      if (stick[i] == false && lastTicksStick[i] == true) {
        stickReleased[i] = true;
      }

      // Update last stick
      lastTicksStick[i] = stick[i];
    }

    // Check button just pressed
    for (int i = 0; i < JOY_MAX_BUTTONS; i++) {
      // Clear old values
      buttonPressed[i] = false;
      buttonReleased[i] = false;

      if (button[i]) {
        anyButtonPressed = true;
      }

      // Pressed since last tick?
      if (button[i] == true && lastTicksButton[i] == false) {
        buttonPressed[i] = true;
        lastButtonPressed = i;
      }

      // Released since last tick?
      if (button[i] == false && lastTicksButton[i] == true) {
        buttonReleased[i] = true;
        lastButtonReleased = i;
      }

      // Update last button
      lastTicksButton[i] = button[i];
    }
  }
};

#endif  // SERVICES_INPUT_JOYSTICK_STATE_H
