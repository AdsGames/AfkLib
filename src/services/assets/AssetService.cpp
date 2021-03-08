/**
 * @file AssetService.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Implementation of AssetService
 * @version 0.1
 * @date 2020-08-05
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "services/assets/AssetService.h"

#include <SDL2/SDL_image.h>
#include <SDL2/SDL_mixer.h>
#include <SDL2/SDL_ttf.h>
#include <algorithm>

#include "common/Exceptions.h"
#include "services/Services.h"

namespace afk {

// Constructor
AssetService::AssetService() {
  // Images
  if (!IMG_Init(IMG_INIT_PNG)) {
    throw InitException("Could not init image addon");
  }

  // Fonts
  if (TTF_Init()) {
    throw InitException("Could not init ttf addon");
  }

  // Audio
  if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 2048) < 0) {
    throw InitException("Could not init audio addon");
  }
}

// Destructor
AssetService::~AssetService() {
  // Todo cleanup
}

// Load image from disk and assign key
void AssetService::loadImage(const std::string& key, const std::string& path) {
  Services::getLoggingService().log("[Asset Manager] Loading image: " + key);

  try {
    loaded_image[key] = Texture(path);
  } catch (const std::runtime_error& e) {
    throw FileIOException(e.what());
  } catch (...) {
    throw FileIOException("Could not load image " + key);
  }
}

// Load audio from disk and assign key
void AssetService::loadAudio(const std::string& key, const std::string& path) {
  Services::getLoggingService().log("[Asset Manager] Loading audio: " + key);

  try {
    loaded_audio[key] = Sound(path);
  } catch (const std::runtime_error& e) {
    throw FileIOException(e.what());
  } catch (...) {
    throw FileIOException("Could not load sound " + key);
  }
}

// Load font from disk and assign key
void AssetService::loadFont(const std::string& key,
                            const std::string& path,
                            const int size) {
  Services::getLoggingService().log("[Asset Manager] Loading font: " + key);

  try {
    loaded_font[key] = Font(path, size);
  } catch (const std::runtime_error& e) {
    throw FileIOException(e.what());
  } catch (...) {
    throw FileIOException("Could not load font " + key);
  }
}

// Load stream from disk and assign key
void AssetService::loadStream(const std::string& key, const std::string& path) {
  Services::getLoggingService().log("[Asset Manager] Loading stream: " + key);

  try {
    loaded_stream[key] = Stream(path);
  } catch (const std::runtime_error& e) {
    throw FileIOException(e.what());
  } catch (...) {
    throw FileIOException("Could not load stream " + key);
  }
}

// Get image reference
const Texture& AssetService::getImage(const std::string& key) {
  try {
    return loaded_image.at(key);
  } catch (const std::out_of_range&) {
    throw KeyLookupException("Could not find image " + key);
  }
}

// Get audio reference
const Sound& AssetService::getAudio(const std::string& key) {
  try {
    return loaded_audio.at(key);
  } catch (const std::out_of_range&) {
    throw KeyLookupException("Could not find sound " + key);
  }
}

// Get font reference
const Font& AssetService::getFont(const std::string& key) {
  try {
    return loaded_font.at(key);
  } catch (const std::out_of_range&) {
    throw KeyLookupException("Could not find font " + key);
  }
}

// Get stream reference
const Stream& AssetService::getStream(const std::string& key) {
  try {
    return loaded_stream.at(key);
  } catch (const std::out_of_range&) {
    throw KeyLookupException("Could not find stream " + key);
  }
}

}  // namespace afk
