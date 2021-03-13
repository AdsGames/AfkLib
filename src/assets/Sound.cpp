/**
 * @file Sound.h
 * @author
 *  Allan Legemaate (alegemaate@gmail.com)
 *  Danny Van Stemp (dannyvanstemp@gmail.com)
 * @brief Implementation of Sound
 * @version 0.1
 * @date 2018-11-23
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "assets/Sound.h"

#include "common/Exceptions.h"

namespace afk {

// Set channel counter to 0
Uint32 Sound::channel_counter = 0;

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
void Sound::play(const float gain,
                 const float pan,
                 const float speed,
                 const bool loop) {
  if (!sample) {
    return;
  }

  // TODO(alegemaate): Frequency
  int int_pan = (pan + 1.0f) * 128;
  int int_gain = gain * 255;

  Mix_SetPanning(channel, int_pan, 255 - int_pan);
  Mix_Volume(channel, int_gain);
  Mix_PlayChannel(channel, sample, loop);
}

// Load sample from file
Mix_Chunk* Sound::loadSample(const std::string& path) {
  // Attempt to load
  Mix_Chunk* temp_sample = Mix_LoadWAV(path.c_str());

  // Throw exception if file is not loaded
  if (!temp_sample) {
    throw FileIOException("There was an error loading sound " + path + " (" +
                          Mix_GetError() + ")");
  }

  return temp_sample;
}

}  // namespace afk
