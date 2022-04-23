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
#ifndef AFK_JOYSTICKCODES_H
#define AFK_JOYSTICKCODES_H

namespace afk {

enum class JoystickButtons {
  A = 0,
  B = 1,
  X = 2,
  Y = 3,
  BumperRight = 4,
  BumperLeft = 5,
  Back = 8,
  Start = 9,
  PadRight = 10,
  PadLeft = 11,
  PadDown = 12,
  PadUp = 13
};

enum class JoystickSticks {
  LeftStickLeft = 1,
  LeftStickRight = 0,
  LeftStickDown = 2,
  LeftStickUp = 3,
  RightStickLeft = 7,
  RightStickRight = 6,
  RightStickDown = 8,
  RightStickUp = 9,
  LeftTrigger = 12,
  RightTrigger = 18
};

}  // namespace afk

#endif  // AFK_JOYSTICKCODES_H
