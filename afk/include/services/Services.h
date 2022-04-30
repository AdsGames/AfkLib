/**
 * @file Services.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Service locator in charge of finding core engine services.
 * @version 0.1
 * @date 2020-11-07
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef AFK_SERVICES_H
#define AFK_SERVICES_H

#include <memory>

#include "assets/AssetService.h"
#include "audio/AudioService.h"
#include "config/ConfigService.h"
#include "display/DisplayService.h"
#include "events/EventQueue.h"
#include "input/InputService.h"
#include "logging/DebugLoggingService.h"
#include "scene/SceneService.h"

namespace afk {

/**
 * @brief Core service locator for engine services
 */
class Services {
 public:
  /**
   * @brief Get the AudioService
   *
   * @return AudioService& Reference to current audio service
   */
  static AudioService& getAudioService();

  /**
   * @brief Get the AssetService
   *
   * @return AssetService& Reference to current asset service
   */
  static AssetService& getAssetService();

  /**
   * @brief Get the DisplayService
   *
   * @return DisplayService& Reference to current display service
   */
  static DisplayService& getDisplayService();

  /**
   * @brief Get the ConfigService
   *
   * @return ConfigService& Reference to current config service
   */
  static ConfigService& getConfigService();

  /**
   * @brief Get the LoggingService
   *
   * @return LoggingService& Reference to current logging service
   */
  static LoggingService& getLoggingService();

  /**
   * @brief Get the InputService
   *
   * @return InputService& Reference to current input service
   */
  static InputService& getInputService();

  /**
   * @brief Get the EventQueue
   *
   * @return EventQueue& Reference to current event queue
   */
  static EventQueue& getEventQueue();

  /**
   * @brief Get the SceneService
   *
   * @return SceneService& Reference to current scene service
   */
  static SceneService& getSceneService();

 private:
  /// Internal pointer to current LoggingService instance
  static DebugLoggingService loggingService;

  /// Internal pointer to current Event queue instance
  static EventQueue eventService;

  /// Internal pointer to current SceneService queue instance
  static SceneService sceneService;

  /// Internal pointer to current DisplayService instance
  static DisplayService displayService;

  /// Internal pointer to current InputService instance
  static InputService inputService;

  /// Internal pointer to current AudioService instance
  static AudioService audioService;

  /// Internal pointer to current AssetService instance
  static AssetService assetService;

  /// Internal pointer to current ConfigService instance
  static ConfigService configService;
};

}  // namespace afk

#endif  // AFK_SERVICES_H
