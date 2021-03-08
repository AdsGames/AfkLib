#ifndef INCLUDE_SERVICES_AUDIO_DEFAULTAUDIOSERVICE_H_
#define INCLUDE_SERVICES_AUDIO_DEFAULTAUDIOSERVICE_H_

#include <string>

#include "AudioService.h"

namespace afk {

/**
 * @brief Implementation of audio service
 *
 * @author Allan Legemaate
 * @date 30/10/2020
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
