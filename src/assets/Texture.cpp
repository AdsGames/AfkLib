#include <SDL2/SDL_image.h>

#include "assets/Texture.h"

#include "common/Exceptions.h"
#include "services/Locator.h"

// Constructor
Texture::Texture() : bitmap(nullptr) {}

// Constructor with path
Texture::Texture(const std::string& path) {
  load(path);
}

// Load texture from file
void Texture::load(const std::string& path) {
  bitmap = loadBitmap(path);
}

// Create texture with specified dimensions
void Texture::create(const int width, const int height) {
  SDL_Surface* temp_surface =
      SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0, 0);
  if (!temp_surface) {
    throw InitException("There was an error creating surface ");
  }

  SDL_Renderer* renderer = Locator::getDisplay().getRenderer();

  SDL_Texture* temp_texture =
      SDL_CreateTextureFromSurface(renderer, temp_surface);
  if (!temp_texture) {
    throw InitException("There was an error creating texture ");
  }
  SDL_FreeSurface(temp_surface);

  bitmap = temp_texture;
}

// Return height of loaded texture
int Texture::getHeight() const {
  if (!bitmap) {
    return 0;
  }

  int h;
  SDL_QueryTexture(bitmap, nullptr, nullptr, nullptr, &h);
  return h;
}

// Return if it exists
bool Texture::exists() const {
  return bitmap != nullptr;
}

// Return width of loaded texture
int Texture::getWidth() const {
  if (!bitmap) {
    return 0;
  }

  int w;
  SDL_QueryTexture(bitmap, nullptr, nullptr, &w, nullptr);
  return w;
}

// Draw texture to screen
void Texture::draw(const int x, const int y) const {
  if (!bitmap) {
    return;
  }

  SDL_Renderer* renderer = Locator::getDisplay().getRenderer();

  SDL_Rect target = {x, y, getWidth(), getHeight()};
  SDL_RenderCopy(renderer, bitmap, nullptr, &target);
}

// Draw scaled texture to screen
void Texture::drawScaled(const int x,
                         const int y,
                         const int width,
                         const int height,
                         const int flags) const {
  if (!bitmap) {
    return;
  }

  SDL_Renderer* renderer = Locator::getDisplay().getRenderer();

  SDL_Rect target = {x, y, width, height};
  SDL_RenderCopy(renderer, bitmap, nullptr, &target);
}

// Get colour at pixel
SDL_Color Texture::getPixel(const int x, const int y) const {
  SDL_Color rgb = {0, 0, 0};
  return rgb;
}

// Load allegro bitmap from file
SDL_Texture* Texture::loadBitmap(const std::string& path) {
  // Attempt to load
  SDL_Surface* temp_surface = IMG_Load(path.c_str());
  if (!temp_surface) {
    throw FileIOException("There was an error loading surface " + path);
  }

  SDL_Renderer* renderer = Locator::getDisplay().getRenderer();

  SDL_Texture* temp_texture =
      SDL_CreateTextureFromSurface(renderer, temp_surface);
  if (!temp_texture) {
    throw InitException("There was an error creating texture " + path);
  }
  SDL_FreeSurface(temp_surface);

  return temp_texture;
}