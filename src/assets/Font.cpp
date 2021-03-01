#include "assets/Font.h"

#include "common/Exceptions.h"

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

  return al_get_font_line_height(font);
}

// Get Size of font
int Font::getSize() {
  return font_size;
}

// Return width given text
int Font::getWidth(const std::string& text) {
  if (!font) {
    return 0;
  }

  return al_get_text_width(font, text.c_str());
}

// Draw Font to screen
void Font::draw(const int x,
                const int y,
                const std::string& text,
                const ALLEGRO_COLOR colour,
                const int flags) {
  if (!font) {
    return;
  }

  al_draw_text(font, colour, x, y, flags, text.c_str());
}

// Load font from file
ALLEGRO_FONT* Font::loadFont(const std::string& path, const int size) {
  // Attempt to load
  ALLEGRO_FONT* temp_font = al_load_font(path.c_str(), size, 0);

  if (!temp_font) {
    throw FileIOException("There was an error loading font " + path);
  }

  return temp_font;
}