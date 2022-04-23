/**
 * @file MouseState.h
 * @author
 *   Allan Legemaate (alegemaate@gmail.com)
 *   Danny Van Stemp (dannyvanstemp@gmail.com)
 * @brief Container for storing Mouse state
 * @version 0.1
 * @date 2021-03-08
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef AFK_MOUSESTATE_H
#define AFK_MOUSESTATE_H

#include <SDL2/SDL_events.h>
#include <SDL2/SDL_mouse.h>

namespace afk {

enum class MouseButtons {
  Left = 1,
  Center = 2,
  Right = 3,
  Max = 4,
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
  int oldX = 0;

  /// Previous mouse y position
  int oldY = 0;

  /// Individual button states
  bool button[static_cast<int>(MouseButtons::Max)] = {false};

  /// Buttons just pressed
  bool down[static_cast<int>(MouseButtons::Max)] = {false};

  /// Buttons just released
  bool up[static_cast<int>(MouseButtons::Max)] = {false};

  /// Mouse just moved
  bool moved = false;

  /// Previous button states
  bool buttonOld[static_cast<int>(MouseButtons::Max)] = {false};

  /**
   * @brief Update the mouse state
   *
   */
  void update() {
    // Check if just moved
    moved = oldX != x || oldY != y;
    oldX = x;
    oldY = y;

    // Check button just pressed
    for (int i = 0; i < static_cast<int>(MouseButtons::Max); i++) {
      // Just up
      if (buttonOld[i] && !button[i]) {
        up[i] = true;
      }

      // Just down
      if (!buttonOld[i] && button[i]) {
        down[i] = true;
      }

      // Same
      if (buttonOld[i] == button[i]) {
        up[i] = false;
        down[i] = false;
      }

      // Set new old values
      buttonOld[i] = button[i];
    }
  }
};

}  // namespace afk

#endif  // AFK_MOUSESTATE_H
