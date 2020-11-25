/*
 * Ui Element
 * Parent class for other ui elements
 * Allan Legemaate
 * 01/11/2020
 */

#ifndef ENGINE_UI_UIELEMENT
#define ENGINE_UI_UIELEMENT

#include <functional>
#include <string>

#include "../entities/GameObject.h"
#include "../fonts/Font.h"

class UIElement : public GameObject {
 public:
  // Constructor
  UIElement(Scene& scene,
            const float x,
            const float y,
            const int z,
            const std::string& text,
            const std::string& font);

  // Draws the object to screen
  virtual void draw() override;

  // Runs updates
  virtual void update() override;

  // Set visiblity
  void setVisible(const bool visible);

  // Set font
  void setFont(const std::string& font);

  // Set text
  void setText(const std::string& text);

  // Set on click
  void setOnClick(std::function<void(void)> func);

 protected:
  // Visibility
  bool visible;

  // Font
  Font font;

  // Text
  std::string text;

  // On Click
  std::function<void(void)> onClick;
};

#endif  // ENGINE_UI_UIELEMENT
