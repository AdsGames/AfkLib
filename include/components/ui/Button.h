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

#include <functional>
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

  /// On click callback
  std::function<void(void)> onClick;

  /**
   * @brief Set the text to display on ui element
   *
   * @param text to display
   */
  void setText(const std::string& text) { this->text = text; }

  /**
   * @brief Set the font to use for displaying text
   *
   * @param font id of font to render text with
   */
  void setFont(const std::string& font) { this->font = font; }

  /**
   * @brief Set the onClick function which will be called when element is
   * clicked
   *
   * @param func function to assign to onClick
   */
  void setOnClick(std::function<void(void)> func) { this->onClick = func; };
};

}  // namespace afk

#endif  // INCLUDE_COMPONENTS_UI_BUTTON_H_
