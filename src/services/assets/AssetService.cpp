#include "services/assets/AssetService.h"

#include <allegro5/allegro_acodec.h>
#include <allegro5/allegro_primitives.h>
#include <allegro5/allegro_ttf.h>
#include <algorithm>

#include "common/Exceptions.h"
#include "services/Locator.h"

// Constant defining number of samples to reserve
const int NUM_SAMPLES = 20;

// Constructor
AssetService::AssetService() {
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
AssetService::~AssetService() {}

// Load image from disk and assign key
void AssetService::loadImage(const std::string& key, const std::string& path) {
  Locator::getLogger().log("[Asset Manager] Loading image: " + key);

  try {
    loaded_image[key] = Texture(path);
  } catch (...) {
    throw FileIOException("Could not load image " + key);
  }
}

// Load audio from disk and assign key
void AssetService::loadAudio(const std::string& key, const std::string& path) {
  Locator::getLogger().log("[Asset Manager] Loading audio: " + key);

  try {
    loaded_audio[key] = Sound(path);
  } catch (...) {
    throw FileIOException("Could not load sound " + key);
  }
}

// Load font from disk and assign key
void AssetService::loadFont(const std::string& key,
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
void AssetService::loadStream(const std::string& key, const std::string& path) {
  Locator::getLogger().log("[Asset Manager] Loading stream: " + key);

  try {
    loaded_stream[key] = Stream(path);
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
