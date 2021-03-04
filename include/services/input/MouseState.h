#ifndef SERVICES_INPUT_MOUSE_STATE_H
#define SERVICES_INPUT_MOUSE_STATE_H

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>

const int MAX_MOUSE_BUTTONS = 3;
const int MOUSE_LEFT = 1;
const int MOUSE_RIGHT = 2;
const int MOUSE_CENTER = 4;

/**
 * @brief Mouse State
 *
 */
struct MouseState {
  /// Current mouse x position
  int x = 0;

  /// Current mouse y position
  int y = 0;

  /// Current mouse z position
  int z = 0;

  /// Previous mouse x position
  int old_x = 0;

  /// Previous mouse y position
  int old_y = 0;

  /// Individual button states
  bool button[MAX_MOUSE_BUTTONS] = {false};

  /// Buttons just pressed
  bool down[MAX_MOUSE_BUTTONS] = {false};

  /// Buttons just released
  bool up[MAX_MOUSE_BUTTONS] = {false};

  /// Mouse just moved
  bool moved = false;

  /// Previous button states
  bool button_old[MAX_MOUSE_BUTTONS] = {false};

  /**
   * @brief Update the mouse state
   *
   */
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

#endif  // SERVICES_INPUT_MOUSE_STATE_H
