
#ifndef ENGINE_INPUT_JOYSTICK_STATE_H
#define ENGINE_INPUT_JOYSTICK_STATE_H

#include <allegro5/allegro.h>

#include "JoystickCodes.h"

/// Max sticks
const int JOY_MAX_STICKS = _AL_MAX_JOYSTICK_STICKS;

/// Max axes
const int JOY_MAX_AXES = _AL_MAX_JOYSTICK_AXES;

/// Max sticks
const int JOY_MAX_STICK_BOOLEANS =
    _AL_MAX_JOYSTICK_STICKS * _AL_MAX_JOYSTICK_AXES * 2;

/// Max buttons
const int JOY_MAX_BUTTONS = _AL_MAX_JOYSTICK_BUTTONS;

/**
 * @brief Joystick state
 *
 */
struct JoystickState {
  bool button[JOY_MAX_BUTTONS] = {false};
  bool buttonPressed[JOY_MAX_BUTTONS] = {false};
  bool buttonReleased[JOY_MAX_BUTTONS] = {false};

  int lastButtonPressed = -1;
  int lastButtonReleased = -1;
  bool anyButtonPressed = false;

  bool stick[JOY_MAX_STICK_BOOLEANS] = {false};
  bool stickMoved[JOY_MAX_STICK_BOOLEANS] = {false};
  bool stickReleased[JOY_MAX_STICK_BOOLEANS] = {false};

  bool lastTicksButton[JOY_MAX_BUTTONS] = {false};
  bool lastTicksStick[JOY_MAX_STICK_BOOLEANS] = {false};

  bool enabled = false;

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

#endif  // ENGINE_INPUT_JOYSTICK_STATE_H
