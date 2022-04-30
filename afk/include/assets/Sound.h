/**
 * @file Sound.h
 * @author
 *  Allan Legemaate (alegemaate@gmail.com)
 *  Danny Van Stemp (dannyvanstemp@gmail.com)
 * @brief Wrapper for SDL Mix_Chunk. Easy interface to interact with samples.
 * @version 0.1
 * @date 2018-11-23
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef AFK_SOUND_H
#define AFK_SOUND_H

#include <SDL2/SDL.h>
#include <SDL2/SDL_mixer.h>
#include <cstdint>
#include <string>

namespace afk {

/**
 * @brief Wrapper for SDL Mix_Chunk. Easy interface to interact with samples.
 *
 */
class Sound {
 public:
  /**
   * @brief Default constructor of Sound object
   *
   */
  Sound();

  /**
   * @brief Construct a new Sound object
   *
   * @param path Path to audio file
   * @throws FileIOException If sound can not be found at path
   */
  explicit Sound(const std::string& path);

  /**
   * @brief Load and assign audio file from a given path
   *
   * @param path Location of sound file
   * @throws FileIOException If sound can not be found at path
   */
  void load(const std::string& path);

  /**
   * @brief Play sound if it exists
   *
   * @param gain Gain from 0 to 1
   * @param pan Pan from -1 to 1
   * @param speed Speed (unused)
   * @param loop Loop mode
   */
  void play(float gain = 1.0f,
            float pan = 0.0f,
            float speed = 1.0f,
            bool loop = false);

 private:
  /**
   * @brief Helper which loads an Mix_Chunk* from a file
   *
   * @param path Path to file
   * @return Mix_Chunk* File that has been loaded
   * @throws FileIOException If sound can not be found at path
   */
  static Mix_Chunk* loadSample(const std::string& path);

  /// Pointer to Mix_Chunk
  Mix_Chunk* sample;

  /// Allocated channel
  int32_t channel;

  /// Current number of channels
  static uint32_t channelCounter;
};

}  // namespace afk

#endif  // AFK_SOUND_H
