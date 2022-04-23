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
#include <utility>

namespace afk {

struct Label {
  /// Constructor
  Label() = default;

  Label(std::string text, std::string font)
      : text(std::move(text)), font(std::move(font)) {}

  /// Text of Label
  std::string text;

  /// Font of label
  std::string font;

  /// Setters
  void setText(const std::string& text) { this->text = text; }

  void setFont(const std::string& font) { this->font = font; }
};

}  // namespace afk

#endif  // AFK_LABEL_H
