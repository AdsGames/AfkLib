
#ifndef ENGINE_INPUT_KEYBOARD_STATE_H
#define ENGINE_INPUT_KEYBOARD_STATE_H

#include <allegro5/allegro.h>

/**
 * @brief Keyboard state
 *
 */
struct KeyboardState {
  bool key[ALLEGRO_KEY_MAX] = {false};
  bool keyPressed[ALLEGRO_KEY_MAX] = {false};
  bool keyReleased[ALLEGRO_KEY_MAX] = {false};

  int lastKeyPressed = -1;
  int lastKeyReleased = -1;
  bool anyKeyPressed = -1;

  bool lastTicksKey[ALLEGRO_KEY_MAX] = {false};

  void update() {
    // Reset last key
    lastKeyPressed = -1;
    lastKeyReleased = -1;
    anyKeyPressed = false;

    // Check key just pressed
    for (int i = 0; i < ALLEGRO_KEY_MAX; i++) {
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

#endif  // ENGINE_INPUT_KEYBOARD_STATE_H
