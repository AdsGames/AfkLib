/**
 * @file KeyboardState.h
 * @author
 *   Allan Legemaate (alegemaate@gmail.com)
 *   Danny Van Stemp (dannyvanstemp@gmail.com)
 * @brief Container for storing Keyboard state
 * @version 0.1
 * @date 2021-03-08
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef AFK_KEYBOARDSTATE_H
#define AFK_KEYBOARDSTATE_H

#include "KeyboardKeys.h"

namespace afk {

/**
 * @brief Keyboard state
 *
 */
struct KeyboardState {
  /// Individual key states
  bool key[static_cast<int>(Keys::Max)] = {false};

  /// keys just pressed
  bool keyPressed[static_cast<int>(Keys::Max)] = {false};

  /// keys just released
  bool keyReleased[static_cast<int>(Keys::Max)] = {false};

  /// Id of last key pressed
  int lastKeyPressed = static_cast<int>(Keys::Unknown);

  /// Id of last key released
  int lastKeyReleased = static_cast<int>(Keys::Unknown);

  /// True if any key down
  bool anyKeyDown = false;

  /// Previous key states
  bool lastTicksKey[static_cast<int>(Keys::Max)] = {false};

  /**
   * @brief Update the keyboard state
   *
   */
  void update() {
    // Reset last key
    lastKeyPressed = static_cast<int>(Keys::Unknown);
    lastKeyReleased = static_cast<int>(Keys::Unknown);
    anyKeyDown = false;

    // Check key just pressed
    for (int i = 0; i < static_cast<int>(Keys::Max); i++) {
      // Clear old values
      keyPressed[i] = false;
      keyReleased[i] = false;

      if (key[i]) {
        anyKeyDown = true;
      }

      // Pressed since last tick?
      if (key[i] && !lastTicksKey[i]) {
        keyPressed[i] = true;
        lastKeyPressed = i;
      }

      // Released since last tick?
      if (!key[i] && lastTicksKey[i]) {
        keyReleased[i] = true;
        lastKeyReleased = i;
      }

      // Update last tick
      lastTicksKey[i] = key[i];
    }
  }
};

}  // namespace afk

#endif  // AFK_KEYBOARDSTATE_H
