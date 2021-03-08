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

}