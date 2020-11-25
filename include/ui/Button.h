/**
 * Button
 * Danny Van Stemp and Allan Legemaate
 * UI Button
 * 11/04/2017
 **/

#ifndef ENGINE_UI_BUTTON_H
#define ENGINE_UI_BUTTON_H

#include "UIElement.h"

#include "../textures/Texture.h"

class Button : public UIElement {
 public:
  Button();
  Button(Scene& scene,
         const int x,
         const int y,
         const int z,
         const std::string& text,
         const std::string& font);

  Button(Scene& scene,
         const int x,
         const int y,
         const int z,
         const std::string& imageId);

  virtual void draw() override;

 private:
  Texture image;
};

#endif  // ENGINE_UI_BUTTON_H
