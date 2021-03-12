/**
 * @file Checkbox.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief UI Checkbox
 * @version 0.1
 * @date 2021-03-12
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INCLUDE_ENTITIES_UI_CHECKBOX_H_
#define INCLUDE_ENTITIES_UI_CHECKBOX_H_

#include "UIElement.h"

#include <string>

namespace afk {

/**
 * @brief Implementation of clickable UI Button
 *
 */
class Checkbox : public UIElement {
 public:
  /**
   * @brief Construct a new Checkbox object
   *
   * @param scene Scene to add element to
   * @param x X position of element
   * @param y Y position of element
   * @param z Z position of element (for sorting)
   */
  explicit Checkbox(Scene& scene,
                    const int x = 0,
                    const int y = 0,
                    const int z = 0);

  /**
   * @brief Draw the checkbox to the screen.
   *
   */
  void draw() override;

  /**
   * @brief Check if checkbox checked
   *
   */
  bool getChecked() const;

  /**
   * @brief Set checked state
   *
   */
  void setChecked(const bool checked);

  /**
   * @brief Set the onCheck function which will be called when element is
   * check
   *
   * @param func function to assign to onCheck
   */
  void setOnCheck(std::function<void(bool)> func);

 protected:
  /// Intercept on click
  void handleOnClick() override;

 private:
  /// Checked state
  bool checked;

  /// On check callback
  std::function<void(bool)> onCheck;
};

}  // namespace afk

#endif  // INCLUDE_ENTITIES_UI_CHECKBOX_H_
