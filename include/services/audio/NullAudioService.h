#ifndef SERVICES_AUDIO_NULL_AUDIO_SERVICE_H
#define SERVICES_AUDIO_NULL_AUDIO_SERVICE_H

#include "AudioService.h"

namespace afk {

/**
 * @brief Null audio service, disables audio
 *
 * @author Allan Legemaate
 * @date 30/10/2020
 */
class NullAudioService : public AudioService {
 public:
  virtual ~NullAudioService(){};

  /**
   * @brief Does nothing
   *
   */
  virtual void playSound(const std::string& key,
                         const PlaySoundConfig& config = PlaySoundConfig());

  /**
   * @brief Does nothing
   *
   */
  virtual void playStream(const std::string& key, const bool loop = false);

  /**
   * @brief Does nothing
   *
   */
  virtual void stopStream(const std::string& key);
};

}  // namespace afk

#endif  // SERVICES_AUDIO_NULL_AUDIO_SERVICE_H