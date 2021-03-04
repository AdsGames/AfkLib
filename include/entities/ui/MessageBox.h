
#ifndef ENTITIES_UI_MESSAGE_BOX
#define ENTITIES_UI_MESSAGE_BOX

#include <string>

/**
 * @brief Allowed types for message box
 *
 */
enum MessageBoxType {
  WARN,
  ERROR,
  INFO,
};

/**
 * @brief Native message box
 *
 * @author Allan Legemaate
 * @date 27/11/2020
 */
class MessageBox {
 public:
  /**
   * @brief Construct a new Message Box object
   *
   */
  MessageBox(MessageBoxType type);

  /**
   * @brief Set the title of the message box
   *
   * @param title string title
   */
  void setTitle(const std::string& title);

  /**
   * @brief Set the heading of the message box
   *
   * @param heading string heading
   */
  void setHeading(const std::string& heading);

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

  /// Heading of message box
  std::string heading;

  /// Text of message box
  std::string text;

  /// Type of box
  MessageBoxType type;

  /**
   * @brief Resolve type of box in allegro terms
   *
   * @returns Type that allegro understands
   */
  int resolveType();
};

#endif  // ENTITIES_UI_MESSAGE_BOX
