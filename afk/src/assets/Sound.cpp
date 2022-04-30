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
uint32_t Sound::channelCounter = 0;

// Default constructor
Sound::Sound() : sample(nullptr) {
  channel = channelCounter;
  Sound::channelCounter++;
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
  int intPan = static_cast<int>((pan + 1.0f) * 128.0f);
  int intGain = static_cast<int>(gain * 255.0f);

  Mix_SetPanning(channel, intPan, 255 - intPan);
  Mix_Volume(channel, intGain);
  Mix_PlayChannel(channel, sample, loop);
}

// Load sample from file
Mix_Chunk* Sound::loadSample(const std::string& path) {
  // Attempt to load
  Mix_Chunk* tempSample = Mix_LoadWAV(path.c_str());

  // Throw exception if file is not loaded
  if (!tempSample) {
    throw FileIoException("There was an error loading sound " + path + " (" +
                          Mix_GetError() + ")");
  }

  return tempSample;
}

}  // namespace afk
