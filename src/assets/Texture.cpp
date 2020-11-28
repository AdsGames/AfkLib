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
  bitmap = al_create_bitmap(width, height);
}

// Return height of loaded texture
int Texture::getHeight() const {
  if (!bitmap) {
    return 0;
  }

  return al_get_bitmap_height(bitmap);
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

  return al_get_bitmap_width(bitmap);
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
ALLEGRO_COLOR Texture::getPixel(const int x, const int y) const {
  return al_get_pixel(this->bitmap, x, y);
}

// Load allegro bitmap from file
ALLEGRO_BITMAP* Texture::loadBitmap(const std::string& path) {
  // Attempt to load
  ALLEGRO_BITMAP* temp_bitmap = al_load_bitmap(path.c_str());

  if (!temp_bitmap) {
    throw FileIOException("There was an error loading texture " + path);
  }

  return temp_bitmap;
}