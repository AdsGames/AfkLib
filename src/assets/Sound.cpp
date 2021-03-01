#include "assets/Sound.h"

#include "common/Exceptions.h"

// Default constructor
Sound::Sound() : sample(nullptr) {}

// Constructor with path
Sound::Sound(const std::string& path) : Sound() {
  load(path);
}

// Load sound from file
void Sound::load(const std::string& path) {
  sample = loadSample(path);
}

// Play this file with config
void Sound::play(const PlaySoundConfig& config) {
  if (!sample) {
    return;
  }

  ALLEGRO_PLAYMODE playMode =
      config.loop ? ALLEGRO_PLAYMODE_LOOP : ALLEGRO_PLAYMODE_ONCE;

  al_play_sample(sample, config.gain, config.pan, config.speed, playMode,
                 nullptr);
}

// Load sample from file
ALLEGRO_SAMPLE* Sound::loadSample(const std::string& path) {
  // Attempt to load
  ALLEGRO_SAMPLE* temp_sample = al_load_sample(path.c_str());

  // Throw exception if file is not loaded
  if (!temp_sample) {
    throw FileIOException("There was an error loading sound " + path);
  }

  return temp_sample;
}