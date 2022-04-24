/**
 * @file Label.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief UI Label
 * @version 0.1
 * @date 2021-03-15
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef AFK_LABEL_H
#define AFK_LABEL_H

#include <string>
#include "../../common/Color.h"

namespace afk {

struct Label {
  /// Text of Label
  std::string text;

  /// Color of text
  color::Color color = color::black;

  /// Font of label
  std::string font;
};

}  // namespace afk

#endif  // AFK_LABEL_H
