#ifndef ASSETS_STREAM_H
#define ASSETS_STREAM_H

#include <SDL2/SDL_mixer.h>
#include <string>

namespace afk {

/**
 * @brief Wrapper for allegro sample including ability to store stream pointer.
 * Use for single instance sounds like music
 *
 * @author Allan Legemaate
 * @date 10/08/2020
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
  void play(const bool loop = false);

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
   * @brief Load an ALLEGRO_AUDIO_STREAM* from file
   *
   * @param path Path to stream
   * @return ALLEGRO_AUDIO_STREAM* Loaded allegro audio stream
   * @throws FileIOException If stream can not be found at path
   */
  static Mix_Chunk* loadStream(const std::string& path);

  /// Pointer to associated ALLEGRO_AUDIO_STREAM*
  Mix_Chunk* stream;
};

}  // namespace afk

#endif  // ASSETS_STREAM_H