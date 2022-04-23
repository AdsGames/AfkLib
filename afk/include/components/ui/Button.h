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
#ifndef AFK_BUTTON_H
#define AFK_BUTTON_H

#include <functional>
#include <string>
#include <utility>

namespace afk {

struct Button {
  /// Constructor
  Button() = default;

  Button(std::string text, std::string font)
      : text(std::move(text)), font(std::move(font)) {}

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
  void setOnClick(std::function<void(void)> func) {
    this->onClick = std::move(func);
  };
};

}  // namespace afk

#endif  // AFK_BUTTON_H
