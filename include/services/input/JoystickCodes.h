/**
 * @file JoystickCodes.h
 * @author Danny Van Stemp (dannyvanstemp@gmail.com)
 * @brief Defines for codes used for joystick
 * @version 0.1
 * @date 2018-11-20
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INCLUDE_SERVICES_INPUT_JOYSTICKCODES_H_
#define INCLUDE_SERVICES_INPUT_JOYSTICKCODES_H_

namespace afk {

enum class JoystickButtons {
  A = 0,
  B = 1,
  X = 2,
  Y = 3,
  BUMPER_RIGHT = 4,
  BUMPER_LEFT = 5,
  BACK = 8,
  START = 9,
  PAD_RIGHT = 10,
  PAD_LEFT = 11,
  PAD_DOWN = 12,
  PAD_UP = 13
};

enum class JoystickSticks {
  LEFT_STICK_LEFT = 1,
  LEFT_STICK_RIGHT = 0,
  LEFT_STICK_DOWN = 2,
  LEFT_STICK_UP = 3,
  RIGHT_STICK_LEFT = 7,
  RIGHT_STICK_RIGHT = 6,
  RIGHT_STICK_DOWN = 8,
  RIGHT_STICK_UP = 9,
  LEFT_TRIGGER = 12,
  RIGHT_TRIGGER = 18
};

}  // namespace afk

#endif  // INCLUDE_SERVICES_INPUT_JOYSTICKCODES_H_
