#include "assets/AssetManager.h"

#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <algorithm>

#include "Locator.h"
#include "common/Exceptions.h"

// Constant defining number of samples to reserve
const int NUM_SAMPLES = 20;

// Constructor
AssetManager::AssetManager() {
  // Fonts
  if (!al_init_font_addon()) {
    throw InitException("Could not init font addon");
  }
  if (!al_init_ttf_addon()) {
    throw InitException("Could not init ttf addon");
  }

  // Graphics
  if (!al_init_image_addon()) {
    throw InitException("Could not init image addon");
  }
  if (!al_init_primitives_addon()) {
    throw InitException("Could not init primitives addon");
  }

  // Audio
  if (!al_install_audio()) {
    throw InitException("Could not init audio addon");
  }
  if (!al_init_acodec_addon()) {
    throw InitException("Could not init acodec addon");
  }

  if (!al_reserve_samples(NUM_SAMPLES)) {
    throw InitException("Could not reserve samples");
  }
}

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
  } catch (const std::out_of_range&) {
    throw KeyLookupException("Could not find image " + key);
  }
}

// Get audio reference
const Sound& AssetManager::getAudio(const std::string& key) {
  try {
    return loaded_audio.at(key);
  } catch (const std::out_of_range&) {
    throw KeyLookupException("Could not find sound " + key);
  }
}

// Get font reference
const Font& AssetManager::getFont(const std::string& key) {
  try {
    return loaded_font.at(key);
  } catch (const std::out_of_range&) {
    throw KeyLookupException("Could not find font " + key);
  }
}

// Get stream reference
const Stream& AssetManager::getStream(const std::string& key) {
  try {
    return loaded_stream.at(key);
  } catch (const std::out_of_range&) {
    throw KeyLookupException("Could not find stream " + key);
  }
}
