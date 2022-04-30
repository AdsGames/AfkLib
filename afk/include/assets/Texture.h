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
#ifndef AFK_TEXTURE_H
#define AFK_TEXTURE_H

#include <SDL2/SDL.h>
#include <string>

#include "../common/Color.h"
#include "../common/Vec.h"

namespace afk {

/**
 * @brief Flags to pass to draw mode
 *
 */
enum class TextureDrawMode {
  Default = 0,
  FlipH = 2,
  FlipV = 1,
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
  void create(int width, int height);

  /**
   * @brief Draw bitmap to screen
   *
   * @param x X position to draw to
   * @param y Y position to draw to
   * @see drawScaled
   */
  void draw(int x, int y) const;

  /**
   * @brief Draw scaled texture to screen
   *
   * @param x X position to draw to
   * @param y Y position to draw to
   * @param width Width to scale to
   * @param height Height to scale to
   * @param angle Rotation of draw
   * @param mode Optional draw mode
   */
  void drawEx(int x,
              int y,
              int width,
              int height,
              float angle = 0.0f,
              TextureDrawMode mode = TextureDrawMode::Default) const;

  /**
   * @brief Get the size of the texture
   *
   * @return Size of texture
   */
  Vec2 getSize();

  /**
   * @brief Check if texture has been loaded
   *
   * @return Loaded status, true if bitmap exists, false otherwise
   */
  bool exists() const;

 private:
  /**
   * @brief Calculate and set size of texture
   *
   */
  void calculateSize();

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

  /// Size of texture
  Vec2 size;
};

}  // namespace afk

#endif  // AFK_TEXTURE_H
