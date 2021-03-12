/**
 * @file Inputbox.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief UI Inputbox
 * @version 0.1
 * @date 2021-03-12
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INCLUDE_ENTITIES_UI_INPUTBOX_H_
#define INCLUDE_ENTITIES_UI_INPUTBOX_H_

#include "UIElement.h"

#include <string>

namespace afk {

/**
 * @brief Implementation of clickable UI Button
 *
 */
class Inputbox : public UIElement {
 public:
  /**
   * @brief Construct a new Inputbox object
   *
   * @param scene Scene to add element to
   * @param x X position of element
   * @param y Y position of element
   * @param z Z position of element (for sorting)
   */
  explicit Inputbox(Scene& scene,
                    const int x = 0,
                    const int y = 0,
                    const int z = 0);

  /**
   * @brief Draw the inputbox to the screen.
   *
   */
  void draw() override;

  /**
   * @brief Update loop override
   *
   */
  void update(Uint32 delta) override;

  /**
   * @brief Set the onChange function which will be called when element text
   * changes
   *
   * @param func function to assign to onChange
   */
  void setOnChange(std::function<void(const std::string& text)> func);

  /**
   * @brief Set the text of the input box
   *
   * @param text Text to insert
   */
  void setText(const std::string& text) override;

 private:
  /// Text iterator
  std::string::iterator iter;

  /// On check callback
  std::function<void(const std::string& text)> onChange;
};

}  // namespace afk

#endif  // INCLUDE_ENTITIES_UI_INPUTBOX_H_
