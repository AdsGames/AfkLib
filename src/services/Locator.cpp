#include "services/Locator.h"

#include "common/Exceptions.h"
#include "services/audio/NullAudioService.h"

// Init audio service
static std::unique_ptr<AudioService> audio_service =
    std::make_unique<NullAudioService>(NullAudioService());

AudioService& Locator::getAudio() {
  if (!audio_service.get()) {
    throw CoreServiceLookupException("Audio service not found");
  }
  return *audio_service;
}

AssetService& Locator::getAsset() {
  if (!asset_service.get()) {
    throw CoreServiceLookupException("Asset service not found");
  }
  return *asset_service;
}

DisplayService& Locator::getDisplay() {
  if (!display_service.get()) {
    throw CoreServiceLookupException("Display service not found");
  }
  return *display_service;
}

ConfigService& Locator::getConfig() {
  if (!config_service.get()) {
    throw CoreServiceLookupException("Config service not found");
  }
  return *config_service;
}

LoggingService& Locator::getLogger() {
  if (!logging_service.get()) {
    throw CoreServiceLookupException("Logging service not found");
  }
  return *logging_service;
}

InputService& Locator::getInput() {
  if (!input_service.get()) {
    throw CoreServiceLookupException("Input service not found");
  }
  return *input_service;
}

SceneService& Locator::getScene() {
  if (!scene_service.get()) {
    throw CoreServiceLookupException("Scene service not found");
  }
  return *scene_service;
}

EventQueue& Locator::getEventQueue() {
  if (!event_service.get()) {
    throw CoreServiceLookupException("Event queue not found");
  }
  return *event_service;
}
