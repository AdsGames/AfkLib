/**
 * @file AudioService.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Parent audio service, other audio services should inherit from this
 * @version 0.1
 * @date 2020-10-30
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INCLUDE_SERVICES_AUDIO_AUDIOSERVICE_H_
#define INCLUDE_SERVICES_AUDIO_AUDIOSERVICE_H_

#include <string>

#include "../../assets/Sound.h"
#include "../../assets/Stream.h"

namespace afk {

/**
 * @brief Parent audio service, other audio services should inherit from this
 * class.
 *
 */
class AudioService {
 public:
  /**
   * @brief Destroy the Audio Service
   *
   */
  virtual ~AudioService() {}

  /**
   * @brief Play sound by id
   *
   * @param key Id of sound to play
   * @param config Play configuration
   */
  virtual void playSound(const std::string& key,
                         const PlaySoundConfig& config = PlaySoundConfig()) = 0;

  /**
   * @brief Play audio stream by id
   *
   * @param key Id of stream to play
   * @param loop Loop mode, true for looping, false for one shot
   */
  virtual void playStream(const std::string& key, const bool loop = false) = 0;

  /**
   * @brief Stop stream by id. Stops all instances of stream currently playing.
   *
   * @param key Id of stream to stop
   */
  virtual void stopStream(const std::string& key) = 0;
};

}  // namespace afk

#endif  // INCLUDE_SERVICES_AUDIO_AUDIOSERVICE_H_
