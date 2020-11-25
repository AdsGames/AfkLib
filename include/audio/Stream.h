#ifndef ENGINE_AUDIO_STREAM_H
#define ENGINE_AUDIO_STREAM_H

#include <allegro5/allegro_audio.h>
#include <string>

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
   * @param file Path to stream
   * @return ALLEGRO_AUDIO_STREAM* Loaded allegro audio stream
   * @throws FileIOException If stream can not be found at path
   */
  static ALLEGRO_AUDIO_STREAM* loadStream(const std::string& file);

  /// Pointer to associated ALLEGRO_AUDIO_STREAM*
  ALLEGRO_AUDIO_STREAM* stream;
};

#endif  // ENGINE_AUDIO_STREAM_H
