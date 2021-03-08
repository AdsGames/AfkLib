#include "assets/Stream.h"

#include "common/Exceptions.h"

namespace afk {

// Buffer count
const size_t BUFFER_COUNT = 4;

// Samples
const size_t SAMPLES = 2048;

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

  Mix_PlayChannel(-1, stream, loop);
}

// Stop stream
void Stream::stop() {
  if (!stream) {
    return;
  }

  // al_detach_audio_stream(stream);
}

// Return if the audio is playing
bool Stream::isPlaying() const {
  return false;  // al_get_audio_stream_playing(stream);
}

// Load allegro sample from file
Mix_Chunk* Stream::loadStream(const std::string& path) {
  // Attempt to load
  Mix_Chunk* temp_stream = Mix_LoadWAV(path.c_str());

  // Throw exception if file is not loaded
  if (!temp_stream) {
    throw FileIOException("There was an error loading stream " + path + " (" +
                          Mix_GetError() + ")");
  }

  return temp_stream;
}

}