#ifndef ENGINE_AUDIO_SOUND_H
#define ENGINE_AUDIO_SOUND_H

#include <allegro5/allegro_audio.h>
#include <string>

/**
 * @brief Configuration for playing audio file
 *
 */
struct PlaySoundConfig {
  /// Floating point gain
  const float gain = 1.0f;
  /// Left right balance
  const float pan = 0.0f;
  /// Speed, and effectively frequency
  const float speed = 1.0f;
  /// Loop mode
  const bool loop = false;
};

const PlaySoundConfig defaultConfig;

/**
 * @brief Wrapper for allegro sample. Easy interface to interact with samples.
 *
 * @author Danny Van Stemp and Allan Legemaate
 * @date 23/11/2018
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
   * @param config PlaySoundConfig object defining play mode
   */
  void play(const PlaySoundConfig& config = defaultConfig);

 private:
  /**
   * @brief Helper which loads an ALLEGRO_SAMPLE* from a file
   *
   * @param file Path to file
   * @return ALLEGRO_SAMPLE* File that has been loaded
   * @throws FileIOException If sound can not be found at path
   */
  static ALLEGRO_SAMPLE* loadSample(const std::string& file);

  /// Pointer to ALLEGRO_SAMPLE
  ALLEGRO_SAMPLE* sample;
};

#endif  // ENGINE_AUDIO_SOUND_H
