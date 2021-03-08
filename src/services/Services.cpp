/**
 * @file Services.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Implementation of core Services class.
 * @version 0.1
 * @date 2020-11-07
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "services/Services.h"

#include "common/Exceptions.h"
#include "services/audio/NullAudioService.h"

namespace afk {

// Init audio service
static std::unique_ptr<AudioService> audio_service =
    std::make_unique<NullAudioService>(NullAudioService());

AudioService& Services::getAudioService() {
  if (!audio_service.get()) {
    throw CoreServiceLookupException("Audio service not found");
  }
  return *audio_service;
}

AssetService& Services::getAssetService() {
  if (!asset_service.get()) {
    throw CoreServiceLookupException("Asset service not found");
  }
  return *asset_service;
}

DisplayService& Services::getDisplayService() {
  if (!display_service.get()) {
    throw CoreServiceLookupException("Display service not found");
  }
  return *display_service;
}

ConfigService& Services::getConfigService() {
  if (!config_service.get()) {
    throw CoreServiceLookupException("Config service not found");
  }
  return *config_service;
}

LoggingService& Services::getLoggingService() {
  if (!logging_service.get()) {
    throw CoreServiceLookupException("Logging service not found");
  }
  return *logging_service;
}

InputService& Services::getInputService() {
  if (!input_service.get()) {
    throw CoreServiceLookupException("Input service not found");
  }
  return *input_service;
}

SceneService& Services::getSceneService() {
  if (!scene_service.get()) {
    throw CoreServiceLookupException("Scene service not found");
  }
  return *scene_service;
}

EventQueue& Services::getEventQueue() {
  if (!event_service.get()) {
    throw CoreServiceLookupException("Event queue not found");
  }
  return *event_service;
}

}  // namespace afk
