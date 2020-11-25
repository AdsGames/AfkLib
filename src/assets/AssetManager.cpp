#include "assets/AssetManager.h"

#include <algorithm>

#include "Locator.h"
#include "common/Exceptions.h"

// Constructor
AssetManager::AssetManager() {}

// Destructor
AssetManager::~AssetManager() {}

// Load image from disk and assign key
void AssetManager::loadImage(const std::string& key, const std::string& path) {
  Locator::getLogger().log("[Asset Manager] Loading image: " + key);

  try {
    loaded_image[key] = Texture(path);
  } catch (...) {
    throw FileIOException("Could not load image " + key);
  }
}

// Load audio from disk and assign key
void AssetManager::loadAudio(const std::string& key, const std::string& path) {
  Locator::getLogger().log("[Asset Manager] Loading audio: " + key);

  try {
    loaded_audio[key] = Sound(path);
  } catch (...) {
    throw FileIOException("Could not load sound " + key);
  }
}

// Load font from disk and assign key
void AssetManager::loadFont(const std::string& key,
                            const std::string& path,
                            const int size) {
  Locator::getLogger().log("[Asset Manager] Loading font: " + key);

  try {
    loaded_font[key] = Font(path, size);
  } catch (...) {
    throw FileIOException("Could not load font " + key);
  }
}

// Load stream from disk and assign key
void AssetManager::loadStream(const std::string& key, const std::string& path) {
  Locator::getLogger().log("[Asset Manager] Loading stream: " + key);

  try {
    loaded_stream[key] = Stream(path);
  } catch (...) {
    throw FileIOException("Could not load stream " + key);
  }
}

// Get image reference
const Texture& AssetManager::getImage(const std::string& key) {
  try {
    return loaded_image.at(key);
  } catch (std::out_of_range) {
    throw KeyLookupException("Could not find image " + key);
  }
}

// Get audio reference
const Sound& AssetManager::getAudio(const std::string& key) {
  try {
    return loaded_audio.at(key);
  } catch (std::out_of_range) {
    throw KeyLookupException("Could not find sound " + key);
  }
}

// Get font reference
const Font& AssetManager::getFont(const std::string& key) {
  try {
    return loaded_font.at(key);
  } catch (std::out_of_range) {
    throw KeyLookupException("Could not find font " + key);
  }
}

// Get stream reference
const Stream& AssetManager::getStream(const std::string& key) {
  try {
    return loaded_stream.at(key);
  } catch (std::out_of_range) {
    throw KeyLookupException("Could not find stream " + key);
  }
}
