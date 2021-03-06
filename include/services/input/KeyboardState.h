
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
  bool key[Keys::KEY_MAX] = {false};

  /// keys just pressed
  bool keyPressed[Keys::KEY_MAX] = {false};

  /// keys just released
  bool keyReleased[Keys::KEY_MAX] = {false};

  /// Id of last key pressed
  int lastKeyPressed = -1;

  /// Id of last key released
  int lastKeyReleased = -1;

  /// True if any key down
  bool anyKeyPressed = -1;

  /// Previous key states
  bool lastTicksKey[Keys::KEY_MAX] = {false};

  /**
   * @brief Update the keyboard state
   *
   */
  void update() {
    // Reset last key
    lastKeyPressed = -1;
    lastKeyReleased = -1;
    anyKeyPressed = false;

    // Check key just pressed
    for (int i = 0; i < Keys::KEY_MAX; i++) {
      // Clear old values
      keyPressed[i] = false;
      keyReleased[i] = false;

      if (key[i]) {
        anyKeyPressed = true;
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
