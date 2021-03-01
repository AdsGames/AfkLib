#include <SDL2/SDL_image.h>

#include "assets/Texture.h"

#include "common/Exceptions.h"

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
  bitmap = SDL_CreateRGBSurface(0, width, height, 32, 0, 0, 0);
}

// Return height of loaded texture
int Texture::getHeight() const {
  if (!bitmap) {
    return 0;
  }

  return bitmap->h;
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

  return bitmap->w;
}

// Draw texture to screen
void Texture::draw(const int x, const int y, const int flags) const {
  if (!bitmap) {
    return;
  }

  al_draw_bitmap(bitmap, x, y, flags);
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

  al_draw_scaled_bitmap(bitmap, 0, 0, getWidth(), getHeight(), x, y, width,
                        height, flags);
}

// Get colour at pixel
SDL_Color Texture::getPixel(const int x, const int y) const {
  int bpp = bitmap->format->BytesPerPixel;

  /* Here p is the address to the pixel we want to retrieve */
  Uint8* p = (Uint8*)bitmap->pixels + y * bitmap->pitch + x * bpp;
  Uint32 data = 0;

  switch (bpp) {
    case 1:
      data = *p;
      break;

    case 2:
      data = *(Uint16*)p;
      break;

    case 3:
      if (SDL_BYTEORDER == SDL_BIG_ENDIAN)
        data = p[0] << 16 | p[1] << 8 | p[2];
      else
        data = p[0] | p[1] << 8 | p[2] << 16;
      break;

    case 4:
      data = *(Uint32*)p;
      break;

    default:
      data = 0;
  }

  SDL_Color rgb;
  SDL_GetRGB(data, bitmap->format, &rgb.r, &rgb.g, &rgb.b);

  return rgb;
}

// Load allegro bitmap from file
SDL_Surface* Texture::loadBitmap(const std::string& path) {
  // Attempt to load
  SDL_Surface* temp_bitmap = IMG_Load(path.c_str());

  if (!temp_bitmap) {
    throw FileIOException("There was an error loading texture " + path);
  }

  return temp_bitmap;
}