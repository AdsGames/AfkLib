
#ifndef SERVICES_INPUT_KEYBOARD_STATE_H
#define SERVICES_INPUT_KEYBOARD_STATE_H

#include "KeyboardKeys.h"

namespace afk {

/**
 * @brief Keyboard state
 *
 */
struct KeyboardState {
  /// Individual key states
  bool key[(int)Keys::KEY_MAX] = {false};

  /// keys just pressed
  bool keyPressed[(int)Keys::KEY_MAX] = {false};

  /// keys just released
  bool keyReleased[(int)Keys::KEY_MAX] = {false};

  /// Id of last key pressed
  int lastKeyPressed = (int)Keys::KEY_UNKNOWN;

  /// Id of last key released
  int lastKeyReleased = (int)Keys::KEY_UNKNOWN;

  /// True if any key down
  bool anyKeyDown = -1;

  /// Previous key states
  bool lastTicksKey[(int)Keys::KEY_MAX] = {false};

  /**
   * @brief Update the keyboard state
   *
   */
  void update() {
    // Reset last key
    lastKeyPressed = -1;
    lastKeyReleased = -1;
    anyKeyDown = false;

    // Check key just pressed
    for (int i = 0; i < (int)Keys::KEY_MAX; i++) {
      // Clear old values
      keyPressed[i] = false;
      keyReleased[i] = false;

      if (key[i]) {
        anyKeyDown = true;
      }

      // Pressed since last tick?
      if (key[i] == true && lastTicksKey[i] == false) {
        keyPressed[i] = true;
        lastKeyPressed = i;
      }

      // Released since last tick?
      if (key[i] == false && lastTicksKey[i] == true) {
        keyReleased[i] = true;
        lastKeyReleased = i;
      }

      // Update last tick
      lastTicksKey[i] = key[i];
    }
  }
};

}  // namespace afk

#endif  // SERVICES_INPUT_KEYBOARD_STATE_H
