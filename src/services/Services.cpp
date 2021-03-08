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

namespace afk {

AudioService& Services::getAudioService() {
  return audio_service;
}

AssetService& Services::getAssetService() {
  return asset_service;
}

DisplayService& Services::getDisplayService() {
  return display_service;
}

ConfigService& Services::getConfigService() {
  return config_service;
}

LoggingService& Services::getLoggingService() {
  return logging_service;
}

InputService& Services::getInputService() {
  return input_service;
}

SceneService& Services::getSceneService() {
  return scene_service;
}

EventQueue& Services::getEventQueue() {
  return event_service;
}

}  // namespace afk
