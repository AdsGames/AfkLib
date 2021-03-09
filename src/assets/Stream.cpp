/**
 * @file Stream.cpp
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Implementation of Stream
 * @version 0.1
 * @date 2020-08-10
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "assets/Stream.h"

#include "common/Exceptions.h"

namespace afk {

// Constructor
Stream::Stream() : stream(nullptr) {}

// Constructor with path
Stream::Stream(const std::string& path) : Stream() {
  load(path);
}

// Load stream from file
void Stream::load(const std::string& path) {
  stream = loadStream(path);
}

// Play stream
void Stream::play(const bool loop) {
  if (!stream) {
    return;
  }

  Mix_PlayMusic(stream, loop);
}

// Stop stream
void Stream::stop() {
  if (!stream) {
    return;
  }

  Mix_HaltMusic();
}

// Return if the audio is playing
bool Stream::isPlaying() const {
  return Mix_PlayingMusic();
}

// Load SDL sample from file
Mix_Music* Stream::loadStream(const std::string& path) {
  // Attempt to load
  Mix_Music* temp_stream = Mix_LoadMUS(path.c_str());

  // Throw exception if file is not loaded
  if (!temp_stream) {
    throw FileIOException("There was an error loading stream " + path + " (" +
                          Mix_GetError() + ")");
  }

  return temp_stream;
}

}  // namespace afk
