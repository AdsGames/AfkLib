#include "services/audio/DefaultAudioService.h"

#include "services/Locator.h"

void DefaultAudioService::playSound(const std::string& key,
                                    const PlaySoundConfig& config) {
  Sound sound = Locator::getAsset().getAudio(key);
  sound.play(config);
}

void DefaultAudioService::playStream(const std::string& key, const bool loop) {
  Stream stream = Locator::getAsset().getStream(key);
  stream.play(loop);
}

void DefaultAudioService::stopStream(const std::string& key) {
  Stream stream = Locator::getAsset().getStream(key);
  stream.stop();
}
