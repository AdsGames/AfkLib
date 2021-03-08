/**
 * @file AudioService.cpp
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Implementation of AudioService
 * @version 0.1
 * @date 2020-10-30
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "services/audio/AudioService.h"

#include "services/Services.h"

namespace afk {

void AudioService::playSound(const std::string& key,
                             const PlaySoundConfig& config) {
  Sound sound = Services::getAssetService().getAudio(key);
  sound.play(config);
}

void AudioService::playStream(const std::string& key, const bool loop) {
  Stream stream = Services::getAssetService().getStream(key);
  stream.play(loop);
}

void AudioService::stopStream(const std::string& key) {
  Stream stream = Services::getAssetService().getStream(key);
  stream.stop();
}

}  // namespace afk
