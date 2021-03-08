/**
 * @file DefaultAudioService.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Default audio service, can actually play audio.
 * @version 0.1
 * @date 2020-10-30
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INCLUDE_SERVICES_AUDIO_DEFAULTAUDIOSERVICE_H_
#define INCLUDE_SERVICES_AUDIO_DEFAULTAUDIOSERVICE_H_

#include <string>

#include "AudioService.h"

namespace afk {

/**
 * @brief Implementation of audio service
 *
 **/
class DefaultAudioService : public AudioService {
 public:
  /**
   * @brief Implementation of playSound
   *
   */
  void playSound(const std::string& key,
                 const PlaySoundConfig& config) override;

  /**
   * @brief Implementation of playStream
   *
   */
  void playStream(const std::string& key, const bool loop = false) override;

  /**
   * @brief Implementation of stopStream
   *
   */
  void stopStream(const std::string& key) override;
};

}  // namespace afk

#endif  // INCLUDE_SERVICES_AUDIO_DEFAULTAUDIOSERVICE_H_
