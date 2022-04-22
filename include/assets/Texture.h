/**
 * @file Texture.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Easy interface to interact with sdl bitmaps
 * @version 0.1
 * @date 2020-08-10
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INCLUDE_ASSETS_TEXTURE_H_
#define INCLUDE_ASSETS_TEXTURE_H_

#include <SDL2/SDL.h>
#include <string>

#include "../common/Color.h"

namespace afk {

/**
 * @brief Flags to pass to draw mode
 *
 */
enum class TextureDrawMode {
  DEFAULT = 0,
  FLIP_H = 2,
  FLIP_V = 1,
};

/**
 * @brief Easy interface to interact with sdl bitmaps
 *
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
   * @see drawScaled
   */
  void draw(const int x, const int y) const;

  /**
   * @brief Draw scaled texture to screen
   *
   * @param x X position to draw to
   * @param y Y position to draw to
   * @param width Width to scale to
   * @param height Height to scale to
   * @param angle Rotation of draw
   * @param mode Optinal draw mode
   */
  void drawEx(const int x,
              const int y,
              const int width,
              const int height,
              const float angle = 0.0f,
              const TextureDrawMode mode = TextureDrawMode::DEFAULT) const;

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
   * @brief Helper which loads an SDL_Texture* from a file
   *
   * @param path Path to file
   * @return SDL_Texture* File that has been loaded
   * @throws FileIOException If texture can not be found at path
   */
  static SDL_Texture* loadTexture(const std::string& path);

  /// Pointer to referenced texture
  SDL_Texture* texture;
};

}  // namespace afk

#endif  // INCLUDE_ASSETS_TEXTURE_H_
