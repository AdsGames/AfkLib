/**
 * @file UIElement.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Parent class of many other UIElement subclasses. Handles most things
 * that all UIElements may need.
 * @version 0.1
 * @date 2020-11-01
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INCLUDE_ENTITIES_UI_UIELEMENT_H_
#define INCLUDE_ENTITIES_UI_UIELEMENT_H_

#include <functional>
#include <string>

#include "../../assets/Font.h"
#include "../GameObject.h"

namespace afk {

/**
 * @brief Parent class for other UI elements such as buttons and labels.
 *
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
   */
  UIElement(Scene& scene, const float x, const float y, const int z);

  /**
   * @brief Draw the ui element to the screen. Can be overriden by other ui
   * elements.
   *
   */
  void draw() override;

  /**
   * @brief Update ui element. Checks for collisions and clicks.
   *
   * @param delta Time since last call in ms
   *
   */
  void update(Uint32 delta) override;

  /**
   * @brief Set the font to use for displaying text
   *
   * @param font id of font to render text with
   */
  void setFont(const std::string& font);

  /**
   * @brief Set the text align of font
   *
   * @param align Text align
   */
  void setTextAlign(const TextAlign align);

  /**
   * @brief Set the text to display on ui element
   *
   * @param text to display
   */
  virtual void setText(const std::string& text);

  /**
   * @brief Set the onClick function which will be called when element is
   * clicked
   *
   * @param func function to assign to onClick
   */
  void setOnClick(std::function<void(void)> func);

  /**
   * @brief Get the text
   *
   * @returns text
   */
  std::string getText() const;

 protected:
  /// Font to use for displaying text
  Font font;

  // Font align
  TextAlign text_align;

  /// Text to display where applicable
  std::string text;

  /// Intermediate on click handler
  virtual void handleOnClick();

  /// Holds reference to onClick function
  std::function<void(void)> onClick;

  /// Stores id of focused element
  static ObjId focused;
};

}  // namespace afk

#endif  // INCLUDE_ENTITIES_UI_UIELEMENT_H_

/**
 * @example ex_ui.cpp
 * This example shows how to use various ui elements
 */
