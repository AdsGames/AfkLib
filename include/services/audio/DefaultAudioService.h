#ifndef SERVICES_AUDIO_DEFAULT_AUDIO_SERVICE_H
#define SERVICES_AUDIO_DEFAULT_AUDIO_SERVICE_H

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
  virtual void playSound(const std::string& key,
                         const PlaySoundConfig& config) override;

  /**
   * @brief Implementation of playStream
   *
   */
  virtual void playStream(const std::string& key,
                          const bool loop = false) override;

  /**
   * @brief Implementation of stopStream
   *
   */
  virtual void stopStream(const std::string& key) override;
};

}  // namespace afk

#endif  // SERVICES_AUDIO_DEFAULT_AUDIO_SERVICE_H