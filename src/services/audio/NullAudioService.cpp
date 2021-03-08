/**
 * @file NullAudioService.cpp
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Implementation of NullAudioService
 * @version 0.1
 * @date 2020-10-30
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "services/audio/NullAudioService.h"

namespace afk {

void NullAudioService::playSound(const std::string& key,
                                 const PlaySoundConfig& config) {
  (void)(key);
  (void)(config);
}

void NullAudioService::playStream(const std::string& key, const bool loop) {
  (void)(key);
  (void)(loop);
}

void NullAudioService::stopStream(const std::string& key) {
  (void)(key);
}

}  // namespace afk
