
#ifndef SERVICES_INPUT_KEYBOARD_STATE_H
#define SERVICES_INPUT_KEYBOARD_STATE_H

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_keyboard.h>
#include <SDL2/SDL_keycode.h>

/**
 * @brief Keyboard state
 *
 */
struct KeyboardState {
  /// Individual key states
  bool key[SDL_NUM_SCANCODES] = {false};

  /// keys just pressed
  bool keyPressed[SDL_NUM_SCANCODES] = {false};

  /// keys just released
  bool keyReleased[SDL_NUM_SCANCODES] = {false};

  /// Id of last key pressed
  int lastKeyPressed = -1;

  /// Id of last key released
  int lastKeyReleased = -1;

  /// True if any key down
  bool anyKeyPressed = -1;

  /// Previous key states
  bool lastTicksKey[SDL_NUM_SCANCODES] = {false};

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
    for (int i = 0; i < SDL_NUM_SCANCODES; i++) {
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

#endif  // SERVICES_INPUT_KEYBOARD_STATE_H
