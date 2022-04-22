/**
 * @file MessageBox.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Native message box
 * @version 0.1
 * @date 2020-11-27
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INCLUDE_ENTITIES_UI_MESSAGEBOX_H_
#define INCLUDE_ENTITIES_UI_MESSAGEBOX_H_

#include <string>

namespace afk {

/**
 * @brief Allowed types for message box
 *
 */
enum class MessageBoxType {
  WARN,
  ERROR,
  INFO,
};

/**
 * @brief Native message box
 *
 */
class MessageBox {
 public:
  /**
   * @brief Construct a new Message Box object
   *
   */
  explicit MessageBox(MessageBoxType type);

  /**
   * @brief Set the title of the message box
   *
   * @param title string title
   */
  void setTitle(const std::string& title);

  /**
   * @brief Set the body text of the message box
   *
   * @param text string text
   */
  void setText(const std::string& text);

  /**
   * @brief Show the message box on screen
   *
   */
  int show();

 private:
  /// Title of message box
  std::string title;

  /// Text of message box
  std::string text;

  /// Type of box
  MessageBoxType type;

  /**
   * @brief Resolve type of box in sdl terms
   *
   * @returns Type that sdl understands
   */
  int resolveType();
};

}  // namespace afk

#endif  // INCLUDE_ENTITIES_UI_MESSAGEBOX_H_

/**
 * @example ex_ui.cpp
 * This example shows how to use various ui elements
 */

/**
 * @example ex_message_box.cpp
 * This example shows how to use advanced MessageBox features
 */
