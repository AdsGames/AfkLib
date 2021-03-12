/**
 * @file AudioService.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Default audio service, can actually play audio.
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
 * @brief Implementation of audio service
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
   * @param gain Gain from 0 to 1
   * @param pan Pan from -1 to 1
   * @param speed Speed (unused)
   * @param loop Loop mode
   */
  void playSound(const std::string& key,
                 const float gain = 1.0f,
                 const float pan = 0.0f,
                 const float speed = 1.0f,
                 const bool loop = false);

  /**
   * @brief Play audio stream by id
   *
   * @param key Id of stream to play
   * @param loop Loop mode, true for looping, false for one shot
   */
  void playStream(const std::string& key, const bool loop = false);

  /**
   * @brief Stop stream by id. Stops all instances of stream currently playing.
   *
   * @param key Id of stream to stop
   */
  void stopStream(const std::string& key);
};

}  // namespace afk

#endif  // INCLUDE_SERVICES_AUDIO_AUDIOSERVICE_H_
