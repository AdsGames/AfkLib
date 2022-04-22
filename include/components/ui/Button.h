/**
 * @file Button.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief UI Button
 * @version 0.1
 * @date 2021-03-15
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INCLUDE_COMPONENTS_UI_BUTTON_H_
#define INCLUDE_COMPONENTS_UI_BUTTON_H_

#include <string>

namespace afk {

struct Button {
  /// Constructor
  Button() : text(""), font("") {}

  Button(const std::string& text, const std::string& font)
      : text(text), font(font) {}

  /// Text of Button
  std::string text;

  /// Font of label
  std::string font;

  /// Setters
  void setText(const std::string& text) { this->text = text; }

  void setFont(const std::string& font) { this->font = font; }
};

}  // namespace afk

#endif  // INCLUDE_COMPONENTS_UI_BUTTON_H_
