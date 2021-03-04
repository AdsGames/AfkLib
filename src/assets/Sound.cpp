#include "assets/Sound.h"

#include "common/Exceptions.h"

// Set channel counter to 0
unsigned int Sound::channel_counter = 0;

// Default constructor
Sound::Sound() : sample(nullptr) {
  channel = channel_counter;
  Sound::channel_counter++;
}

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

  // TODO: Frequency
  Mix_SetPanning(channel, config.pan, 255 - config.pan);
  Mix_Volume(channel, config.gain);
  Mix_PlayChannel(channel, sample, config.loop);
}

// Load sample from file
Mix_Chunk* Sound::loadSample(const std::string& path) {
  // Attempt to load
  Mix_Chunk* temp_sample = Mix_LoadWAV(path.c_str());

  // Throw exception if file is not loaded
  if (!temp_sample) {
    throw FileIOException("There was an error loading sound " + path);
  }

  return temp_sample;
}