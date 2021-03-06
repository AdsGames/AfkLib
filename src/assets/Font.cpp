/**
 * @file Font.cpp
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Implementation of Font
 * @version 0.1
 * @date 2020-08-10
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "assets/Font.h"

#include "color/Color.h"
#include "common/Exceptions.h"
#include "services/Services.h"

namespace afk {

// Constructor
Font::Font() : font(nullptr), font_size(0) {}

// Constructor with path
Font::Font(const std::string& path, const int size)
    : font(nullptr), font_size(size) {
  load(path, size);
}

// Load Font from file
void Font::load(const std::string& path, const int size) {
  font = loadFont(path, size);
}

// Return line height for given text
int Font::getHeight() {
  if (!font) {
    return 0;
  }

  SDL_Renderer* renderer = Services::getDisplayService().getRenderer();
  SDL_Texture* texture = renderText(renderer, "a", color::black);

  int h;
  SDL_QueryTexture(texture, nullptr, nullptr, nullptr, &h);

  SDL_DestroyTexture(texture);

  return h;
}

// Get Size of font
int Font::getSize() {
  return font_size;
}

// Check if exists
bool Font::exists() const {
  return font != nullptr;
}

// Return width given text
int Font::getWidth(const std::string& text) {
  if (!font || text == "") {
    return 0;
  }

  SDL_Renderer* renderer = Services::getDisplayService().getRenderer();
  SDL_Texture* texture = renderText(renderer, text.c_str(), color::black);

  int w;
  SDL_QueryTexture(texture, nullptr, nullptr, &w, nullptr);

  SDL_DestroyTexture(texture);

  return w;
}

// Draw Font to screen
void Font::draw(const int x,
                const int y,
                const std::string& text,
                const color::Color colour,
                const TextAlign align) {
  if (!font) {
    return;
  }

  SDL_Renderer* renderer = Services::getDisplayService().getRenderer();
  SDL_Texture* texture = renderText(renderer, text.c_str(), colour);

  int w, h;
  SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);

  SDL_Rect target = {x, y, w, h};

  switch (align) {
    case TextAlign::LEFT:
      SDL_RenderCopy(renderer, texture, NULL, &target);
      break;
    case TextAlign::RIGHT:
      target.x = x - w;
      SDL_RenderCopy(renderer, texture, NULL, &target);
      break;
    case TextAlign::CENTER:
      target.x = x - w / 2;
      SDL_RenderCopy(renderer, texture, NULL, &target);
      break;
    default:
      break;
  }

  SDL_DestroyTexture(texture);
}

// Load font from file
TTF_Font* Font::loadFont(const std::string& path, const int size) {
  // Attempt to load
  TTF_Font* temp_font = TTF_OpenFont(path.c_str(), size);

  if (!temp_font) {
    throw FileIOException("There was an error loading font " + path + " (" +
                          TTF_GetError() + ")");
  }

  return temp_font;
}

// Render font to texture
SDL_Texture* Font::renderText(SDL_Renderer* renderer,
                              const std::string text,
                              const color::Color colour) {
  SDL_Surface* surface = TTF_RenderText_Solid(
      font, text.c_str(), {colour.r, colour.g, colour.b, colour.a});
  SDL_Texture* texture = SDL_CreateTextureFromSurface(renderer, surface);
  SDL_FreeSurface(surface);

  return texture;
}

}  // namespace afk
