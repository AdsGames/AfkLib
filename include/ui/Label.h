/**
 * Label
 * Danny Van Stemp and Allan Legemaate
 * UI Button
 * 25/11/2018
 **/

#ifndef ENGINE_UI_LABEL_H
#define ENGINE_UI_LABEL_H

#include "UIElement.h"

class Label : public UIElement {
 public:
  // Detailed constructor
  Label(Scene& scene,
        const int x,
        const int y,
        const int z,
        const std::string& text,
        const std::string& font);

  // Draw
  virtual void draw() override;
};

#endif  // ENGINE_UI_LABEL_H
