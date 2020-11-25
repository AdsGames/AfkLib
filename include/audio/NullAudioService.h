#ifndef ENGINE_AUDIO_NULL_AUDIO_SERVICE_H
#define ENGINE_AUDIO_NULL_AUDIO_SERVICE_H

#include "AudioService.h"

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
   * @override
   */
  virtual void playSound(const std::string& key,
                         const PlaySoundConfig& config = PlaySoundConfig());

  /**
   * @brief Does nothing
   *
   * @override
   */
  virtual void playStream(const std::string& key, const bool loop = false);

  /**
   * @brief Does nothing
   *
   * @override
   */
  virtual void stopStream(const std::string& key);
};

#endif  // ENGINE_AUDIO_NULL_AUDIO_SERVICE_H