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

namespace afk {

// Init services
DebugLoggingService Services::loggingService;
EventQueue Services::eventService;
SceneService Services::sceneService;
DisplayService Services::displayService;
InputService Services::inputService;
AudioService Services::audioService;
AssetService Services::assetService;
ConfigService Services::configService;

AudioService& Services::getAudioService() {
  return audioService;
}

AssetService& Services::getAssetService() {
  return assetService;
}

DisplayService& Services::getDisplayService() {
  return displayService;
}

ConfigService& Services::getConfigService() {
  return configService;
}

LoggingService& Services::getLoggingService() {
  return loggingService;
}

InputService& Services::getInputService() {
  return inputService;
}

SceneService& Services::getSceneService() {
  return sceneService;
}

EventQueue& Services::getEventQueue() {
  return eventService;
}

}  // namespace afk
