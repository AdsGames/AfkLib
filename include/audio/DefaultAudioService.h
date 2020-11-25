#ifndef ENGINE_AUDIO_DEFAULT_AUDIO_SERVICE_H
#define ENGINE_AUDIO_DEFAULT_AUDIO_SERVICE_H

#include "AudioService.h"

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
   * @override
   */
  virtual void playSound(const std::string& key,
                         const PlaySoundConfig& config) override;

  /**
   * @brief Implementation of playStream
   *
   * @override
   */
  virtual void playStream(const std::string& key,
                          const bool loop = false) override;

  /**
   * @brief Implementation of stopStream
   *
   * @override
   */
  virtual void stopStream(const std::string& key) override;
};

#endif  // ENGINE_AUDIO_DEFAULT_AUDIO_SERVICE_H