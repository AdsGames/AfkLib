#ifndef ENTITIES_UI_UIELEMENT
#define ENTITIES_UI_UIELEMENT

#include <functional>
#include <string>

#include "../../assets/Font.h"
#include "../GameObject.h"

namespace afk {

/**
 * @brief Parent class for other UI elements such as buttons and labels.
 *
 * @author Allan Legemaate
 * @date 01/11/2020
 */
class UIElement : public GameObject {
 public:
  /**
   * @brief Construct a new UIElement object
   *
   * @param scene Scene to add element to
   * @param x X position of element
   * @param y Y position of element
   * @param z Z position of element (for sorting)
   * @param text Text to display, if applicable
   * @param font Font to use to display text
   */
  UIElement(Scene& scene,
            const float x,
            const float y,
            const int z,
            const std::string& text,
            const std::string& font);

  /**
   * @brief Draw the ui element to the screen. Can be overriden by other ui
   * elements.
   *
   */
  virtual void draw() override;

  /**
   * @brief Update ui element. Checks for collisions and clicks.
   *
   */
  virtual void update() override;

  /**
   * @brief Set the visibility of element. When invisible, they will not be
   * drawn or interactive.
   *
   * @param visible visibility of element
   */
  void setVisible(const bool visible);

  /**
   * @brief Set the font to use for displaying text
   *
   * @param font id of font to render text with
   */
  void setFont(const std::string& font);

  /**
   * @brief Set the text to display on ui element
   *
   * @param text to display
   */
  void setText(const std::string& text);

  /**
   * @brief Set the onClick function which will be called when element is
   * clicked
   *
   * @param func function to assign to onClick
   */
  void setOnClick(std::function<void(void)> func);

 protected:
  /// Visibility
  bool visible;

  /// Font to use for displaying text
  Font font;

  /// Text to display where applicable
  std::string text;

  /// Holds reference to onClick function
  std::function<void(void)> onClick;
};

}  // namespace afk

#endif  // ENTITIES_UI_UIELEMENT
