#ifndef ENGINE_INPUT_INPUT_H
#define ENGINE_INPUT_INPUT_H

#include <allegro5/allegro.h>

#include "JoystickState.h"
#include "KeyboardState.h"
#include "MouseState.h"

/**
 * @brief General Purpose input listener
 *
 * @date 2020-11-07
 * @author Allan Legemaate (alegemaate@gmail.com)
 */
class Input {
 public:
  /**
   * @brief Construct a new Input object
   *
   */
  Input(){};

  /**
   * @brief Register with allegro queue
   *
   * @param queue Allegro queue
   */
  void registerEvents(ALLEGRO_EVENT_QUEUE* queue);

  /**
   * @brief Process an event from the main thread
   *
   * @param event ALLEGRO_EVENT to process
   */
  void processEvent(const ALLEGRO_EVENT& event);

  /**
   * @brief Get keyboard state
   *
   * @return Keyboard state
   */
  const KeyboardState& keyboard();

  /**
   * @brief Get mouse state
   *
   * @return Mouse state
   */
  const MouseState& mouse();

  /**
   * @brief Get joystick state
   *
   * @return Joystick state
   */
  const JoystickState& joystick();

 private:
  /**
   * @brief Update last keys/buttons etc.
   *
   */
  void update();

  /**
   * @brief Joystick button event handler
   *
   * @param event_type Type of allegro event
   * @param keycode Keycode pressed
   */
  void onJoystickEvent(ALLEGRO_EVENT_TYPE event_type, const int keycode);

  /**
   * @brief Joystick axis and stick event handler
   *
   * @param event_type Type of allegro event
   * @param stick Stick moved
   * @param axis Axis moved
   * @param position Axis/Stick position
   */
  void onJoystickEvent(ALLEGRO_EVENT_TYPE event_type,
                       const int stick,
                       const int axis,
                       const float position);

  /**
   * @brief Joystick configuration event
   *
   */
  void onJoystickReconfigureEvent();

  /**
   * @brief Keyboard event handler
   *
   * @param event_type Type of allegro event
   * @param keycode Keycode
   */
  void onKeyboardEvent(ALLEGRO_EVENT_TYPE event_type, const int keycode);

  /**
   * @brief Mouse axis handler
   *
   * @param event_type Type of allegro event
   * @param x X position of mouse
   * @param y Y position of mouse
   * @param z Z position of mouse
   */
  void onMouseEvent(ALLEGRO_EVENT_TYPE event_type,
                    const int x,
                    const int y,
                    const int z);

  /**
   * @brief Mouse button handler
   *
   * @param event_type Type of allegro event
   * @param button button changed
   */
  void onMouseEvent(ALLEGRO_EVENT_TYPE event_type, const unsigned int button);

  /// Current keyboard state
  KeyboardState keyboard_state;

  /// Current mouse state
  MouseState mouse_state;

  /// Current joystick state
  JoystickState joystick_state;
};

#endif  // ENGINE_INPUT_INPUT_H
