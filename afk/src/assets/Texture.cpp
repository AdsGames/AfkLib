/**
 * @file Texture.cpp
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Implementation of Texture
 * @version 0.1
 * @date 2020-08-10
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "assets/Texture.h"

#include <SDL2/SDL_image.h>

#include "common/Exceptions.h"
#include "services/Services.h"

namespace afk {

// Constructor
Texture::Texture() : texture(nullptr) {}

// Constructor with path
Texture::Texture(const std::string& path) : texture(nullptr) {
  load(path);
}

// Load texture from file
void Texture::load(const std::string& path) {
  texture = loadTexture(path);
  calculateSize();
}

// Create texture with specified dimensions
void Texture::create(const int width, const int height) {
  SDL_Surface* tempSurface =
      SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
  if (!tempSurface) {
    throw InitException("There was an error creating surface ");
  }

  SDL_Renderer* renderer = Services::getDisplayService().getRenderer();

  SDL_Texture* tempTexture =
      SDL_CreateTextureFromSurface(renderer, tempSurface);
  if (!tempTexture) {
    throw InitException("There was an error creating texture ");
  }
  SDL_FreeSurface(tempSurface);

  texture = tempTexture;

  calculateSize();
}

// Calculate size of texture
void Texture::calculateSize() {
  int w, h;
  SDL_QueryTexture(texture, nullptr, nullptr, &w, &h);
  this->size = Vec2(w, h);
}

// Return if it exists
bool Texture::exists() const {
  return texture != nullptr;
}

// Return width of loaded texture
Vec2 Texture::getSize() {
  return size;
}

// Draw texture to screen
void Texture::draw(const int x, const int y) const {
  if (!texture) {
    return;
  }

  SDL_Renderer* renderer = Services::getDisplayService().getRenderer();

  SDL_Rect target = {x, y, size.x, size.y};
  SDL_RenderCopy(renderer, texture, nullptr, &target);
}

// Draw extended mode
void Texture::drawEx(const int x,
                     const int y,
                     const int width,
                     const int height,
                     const float angle,
                     const TextureDrawMode mode) const {
  if (!texture) {
    return;
  }

  SDL_Renderer* renderer = Services::getDisplayService().getRenderer();

  SDL_Rect target = {x, y, width, height};
  SDL_Point center = {width / 2, height / 2};
  auto flip = static_cast<SDL_RendererFlip>(mode);

  SDL_RenderCopyEx(renderer, texture, nullptr, &target, angle, &center, flip);
}

// Load an SDL texture from file
SDL_Texture* Texture::loadTexture(const std::string& path) {
  // Attempt to load
  SDL_Surface* tempSurface = IMG_Load(path.c_str());
  if (!tempSurface) {
    throw FileIoException("There was an error loading surface " + path + " (" +
                          SDL_GetError() + ")");
  }

  SDL_Renderer* renderer = Services::getDisplayService().getRenderer();

  SDL_Texture* tempTexture =
      SDL_CreateTextureFromSurface(renderer, tempSurface);
  if (!tempTexture) {
    throw InitException("There was an error creating texture " + path + " (" +
                        SDL_GetError() + ")");
  }
  SDL_FreeSurface(tempSurface);

  return tempTexture;
}

}  // namespace afk
