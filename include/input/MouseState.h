#ifndef ENGINE_INPUT_MOUSE_STATE_H
#define ENGINE_INPUT_MOUSE_STATE_H

const int MAX_MOUSE_BUTTONS = 3;
const int MOUSE_LEFT = 1;
const int MOUSE_RIGHT = 2;
const int MOUSE_CENTER = 4;

/**
 * @brief Mouse State
 *
 */
struct MouseState {
  int x = 0;
  int y = 0;
  int z = 0;

  bool button[MAX_MOUSE_BUTTONS] = {false};
  bool down[MAX_MOUSE_BUTTONS] = {false};
  bool up[MAX_MOUSE_BUTTONS] = {false};
  bool moved = false;

  int old_x = 0;
  int old_y = 0;
  bool button_old[MAX_MOUSE_BUTTONS] = {false};

  void update() {
    // Check if just moved
    moved = old_x != x || old_y != y;
    old_x = x;
    old_y = y;

    // Check button just pressed
    for (int i = 0; i < MAX_MOUSE_BUTTONS; i++) {
      // Just up
      if (button_old[i] && !button[i]) {
        up[i] = true;
      }

      // Just down
      if (!button_old[i] && button[i]) {
        down[i] = true;
      }

      // Same
      if (button_old[i] == button[i]) {
        up[i] = false;
        down[i] = false;
      }

      // Set new old values
      button_old[i] = button[i];
    }
  }
};

#endif  // ENGINE_INPUT_MOUSE_STATE_H
