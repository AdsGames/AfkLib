#ifndef ASSETS_TEXTURE_H
#define ASSETS_TEXTURE_H

#include <SDL2/SDL.h>
#include <string>

/**
 * @brief Easy interface to interact with allegro bitmaps
 *
 * @author Allan Legemaate
 * @date 10/08/2020
 */
class Texture {
 public:
  /**
   * @brief Construct a new Texture object
   *
   */
  Texture();

  /**
   * @brief Construct a new Texture object
   *
   * @param path Path to image file
   * @throws FileIOException If image can not be found at path
   */
  explicit Texture(const std::string& path);

  /**
   * @brief Load and assign image file from a given path
   *
   * @param path Location of image file
   * @throws FileIOException If image can not be found at path
   */
  void load(const std::string& path);

  /**
   * @brief Create a new texture with width and height
   *
   * @param width Width in pixels
   * @param height Height in pixels
   */
  void create(const int width, const int height);

  /**
   * @brief Draw bitmap to screen
   *
   * @param x X position to draw to
   * @param y Y position to draw to
   * @param flags Additional flags to pass to allegro draw routine
   * @see drawScaled
   */
  void draw(const int x, const int y, const int flags = 0) const;

  /**
   * @brief Draw scaled texture to screen
   *
   * @param x X position to draw to
   * @param y Y position to draw to
   * @param width Width to scale to
   * @param height Height to scale to
   * @param flags Additional flags to pass to allegro draw routine
   */
  void drawScaled(const int x,
                  const int y,
                  const int width,
                  const int height,
                  const int flags = 0) const;

  /**
   * @brief Get the color at given position
   *
   * @param x X position to sample
   * @param y Y position to sample
   * @return Colour at pixel x y
   */
  SDL_Color getPixel(const int x, const int y) const;

  /**
   * @brief Get the width of the texture
   *
   * @return Width of texture
   */
  int getWidth() const;

  /**
   * @brief Get the height of the texture
   *
   * @return Height of texture
   */
  int getHeight() const;

  /**
   * @brief Check if texture has been loaded
   *
   * @return Loaded status, true if bitmap exists, false otherwise
   */
  bool exists() const;

 private:
  /**
   * @brief Helper which loads an SDL_Surface* from a file
   *
   * @param path Path to file
   * @return SDL_Surface* File that has been loaded
   * @throws FileIOException If texture can not be found at path
   */
  static SDL_Surface* loadBitmap(const std::string& path);

  /// Pointer to referenced bitmap
  SDL_Surface* bitmap;
};

#endif  // ASSETS_TEXTURE_H
