/**
 * @file Font.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Easy interface to interact with SDL fonts
 * @version 0.1
 * @date 2020-08-10
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INCLUDE_ASSETS_FONT_H_
#define INCLUDE_ASSETS_FONT_H_

#include <SDL2/SDL_ttf.h>
#include <string>

#include "../color/Color.h"

namespace afk {

enum class FontAlign { ALIGN_LEFT, ALIGN_RIGHT, ALIGN_CENTER };

/**
 * @brief Easy interface to interact with SDL fonts
 */
class Font {
 public:
  /**
   * @brief Construct a new Font object
   *
   */
  Font();

  /**
   * @brief Construct a new Font object
   *
   * @param path Path to font file
   * @param size Size of font to load
   * @throws FileIOException If font can not be found at path
   */
  Font(const std::string& path, const int size);

  /**
   * @brief Load and assign font from given path
   *
   * @param path Location of font file
   * @param size Size of font to load
   * @throws FileIOException If font can not be found at path
   */
  void load(const std::string& path, const int size);

  /**
   * @brief Draw font at position
   *
   * @param x X position in pixels
   * @param y Y position in pixels
   * @param text Text to draw with font
   * @param colour colour to colour text
   * @param align Text alignment, defaults to left
   */
  void draw(const int x,
            const int y,
            const std::string& text,
            const color::Color colour = color::rgb(0, 0, 0),
            const FontAlign align = FontAlign::ALIGN_LEFT);

  /**
   * @brief Get the height of the font
   *
   * @return Height of font in pixels
   */
  int getHeight();

  /**
   * @brief Get the width of the font with the provided text
   *
   * @param text Text to check width against
   * @return Width in pixels
   */
  int getWidth(const std::string& text);

  /**
   * @brief Get the font size
   *
   * @return Size of font loaded
   */
  int getSize();

 private:
  /**
   * @brief Helper which loads an TTF_Font* from a file
   *
   * @param path Path to file
   * @param size Size of font to generate
   *
   * @return TTF_Font* File that has been loaded
   * @throws FileIOException If font can not be found at path
   */
  static TTF_Font* loadFont(const std::string& path, const int size);

  /// Pointer to referenced font
  TTF_Font* font;

  /// Size of font
  int font_size;

  /**
   * @brief Helper for rendering text
   *
   * @param renderer SDL Renderer to draw to
   * @param text String to draw
   * @param colour Color of text
   * @return SDL_Texture* New texture containing string
   */
  SDL_Texture* renderText(SDL_Renderer* renderer,
                          const std::string text,
                          const color::Color colour);
};

}  // namespace afk

#endif  // INCLUDE_ASSETS_FONT_H_
