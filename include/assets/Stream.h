/**
 * @file Stream.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Wrapper for sdl stream including ability to store stream pointer.
 * Use for single instance sounds like music
 * @version 0.1
 * @date 2020-08-10
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef AFK_STREAM_H
#define AFK_STREAM_H

#include <SDL2/SDL_mixer.h>
#include <string>

namespace afk {

/**
 * @brief Wrapper for sdl stream including ability to store stream pointer.
 * Use for single instance sounds like music
 *
 */
class Stream {
 public:
  /**
   * @brief Construct a new Stream object, default constructor
   *
   */
  Stream();

  /**
   * @brief Construct a new Stream object from asset path
   *
   * @param path Path to audio file
   * @throws FileIOException If stream can not be found at path
   */
  explicit Stream(const std::string& path);

  /**
   * @brief Play stream (if it exists)
   *
   * @param loop Loop mode
   */
  void play(bool loop = false);

  /**
   * @brief Stop this instance of the stream from playing
   *
   */
  void stop();

  /**
   * @brief Load and assign audio file to given path
   *
   * @param path Location of the audio stream to load
   * @throws FileIOException If stream can not be found at path
   */
  void load(const std::string& path);

  /**
   * @brief Returns true if the stream is playing, otherwise false
   *
   * @return Play status of stream
   */
  bool isPlaying() const;

 private:
  /**
   * @brief Load an Mix_Music* from file
   *
   * @param path Path to stream
   * @return Mix_Music* Loaded SDL audio stream
   * @throws FileIOException If stream can not be found at path
   */
  static Mix_Music* loadStream(const std::string& path);

  /// Pointer to associated Mix_Music*
  Mix_Music* stream;
};

}  // namespace afk

#endif  // AFK_STREAM_H
