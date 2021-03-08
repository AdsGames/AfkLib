#ifndef INCLUDE_SERVICES_INPUT_MOUSESTATE_H_
#define INCLUDE_SERVICES_INPUT_MOUSESTATE_H_

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>

namespace afk {

enum class MouseButtons {
  LEFT = 1,
  CENTER = 2,
  RIGHT = 3,
  MAX = 4,
};

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
  bool button[static_cast<int>(MouseButtons::MAX)] = {false};

  /// Buttons just pressed
  bool down[static_cast<int>(MouseButtons::MAX)] = {false};

  /// Buttons just released
  bool up[static_cast<int>(MouseButtons::MAX)] = {false};

  /// Mouse just moved
  bool moved = false;

  /// Previous button states
  bool button_old[static_cast<int>(MouseButtons::MAX)] = {false};

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
    for (int i = 0; i < static_cast<int>(MouseButtons::MAX); i++) {
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

}  // namespace afk

#endif  // INCLUDE_SERVICES_INPUT_MOUSESTATE_H_
