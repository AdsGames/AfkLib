#ifndef ENGINE_FONTS_FONT
#define ENGINE_FONTS_FONT

#include <allegro5/allegro.h>
#include <allegro5/allegro_font.h>
#include <string>

/**
 * @brief Easy interface to interact with allegro fonts
 *
 * @author Allan Legemaate
 * @date 10/08/2020
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
   * @param colour Allegro colour to colour text
   * @param flags Additional ALLEGRO_FONT flags
   */
  void draw(const int x,
            const int y,
            const std::string& text,
            const ALLEGRO_COLOR colour = al_map_rgb(0, 0, 0),
            const int flags = 0);

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
   * @brief Helper which loads an ALLEGRO_FONT* from a file
   *
   * @param file Path to file
   * @return ALLEGRO_FONT* File that has been loaded
   * @throws FileIOException If font can not be found at path
   */
  static ALLEGRO_FONT* loadFont(const std::string& file, const int size);

  /// Pointer to referenced font
  ALLEGRO_FONT* font;

  /// Size of font
  int font_size;
};

#endif  // ENGINE_FONTS_FONT
