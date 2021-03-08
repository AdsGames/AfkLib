/**
 * @file Services.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief
 * @version 0.1
 * @date 2020-11-07
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INCLUDE_SERVICES_SERVICES_H_
#define INCLUDE_SERVICES_SERVICES_H_

#include <memory>

#include "assets/AssetService.h"
#include "audio/AudioService.h"
#include "config/ConfigService.h"
#include "display/DisplayService.h"
#include "events/EventQueue.h"
#include "input/InputService.h"
#include "logging/LoggingService.h"
#include "scene/SceneService.h"

namespace afk {

/**
 * @brief Core service locator for engine services
 */
class Services {
 public:
  /**
   * @brief Provide instance of audio service
   *
   * @tparam T Type of audio service to provide, must be child of AudioService
   * class
   * @tparam Args Arguments that correspond to the constructor of T
   * @param args Argument values to be forwarded to constructor of T
   */
  template <class T, class... Args>
  static void provideAudioService(Args&&... args) {
    audio_service = std::make_shared<T>((args)...);
  }

  /**
   * @brief Provide instance of asset service
   *
   * @tparam T Type of asset service to provide, must be of type AssetService
   * @tparam Args Ctor arguments for T
   * @param args Argument values to be forwarded to constructor of T
   */
  template <class T, class... Args>
  static void provideAssetService(Args&&... args) {
    asset_service = std::make_shared<T>((args)...);
  }

  /**
   * @brief Provide instance of display service
   *
   * @tparam T Type of window to provide, must be of type Window
   * @tparam Args Ctor arguments for T
   * @param args Argument values to be forwarded to constructor of T
   */
  template <class T, class... Args>
  static void provideDisplayService(Args&&... args) {
    display_service = std::make_shared<T>((args)...);
  }

  /**
   * @brief Provide instance of config service
   *
   * @tparam T Type of config service to provide, must be of type
   * ConfigService
   * @tparam Args Ctor arguments for T
   * @param args Argument values to be forwarded to constructor of T
   */
  template <class T, class... Args>
  static void provideConfigService(Args&&... args) {
    config_service = std::make_shared<T>((args)...);
  }

  /**
   * @brief Provide instance of logging service
   *
   * @tparam T Type of logging service to provide, must be of type
   * LoggingService
   * @tparam Args Ctor arguments for T
   * @param args Argument values to be forwarded to constructor of T
   */
  template <class T, class... Args>
  static void provideLoggingService(Args&&... args) {
    logging_service = std::make_shared<T>((args)...);
  }

  /**
   * @brief Provide instance of input service
   *
   * @tparam T Type of logger to provide, must be of type InputService
   * @tparam Args Ctor arguments for T
   * @param args Argument values to be forwarded to constructor of T
   */
  template <class T, class... Args>
  static void provideInputService(Args&&... args) {
    input_service = std::make_shared<T>((args)...);
  }

  /**
   * @brief Provide instance of event queue
   *
   * @tparam T Type of logger to provide, must be of type Event Queue
   * @tparam Args Ctor arguments for T
   * @param args Argument values to be forwarded to constructor of T
   */
  template <class T, class... Args>
  static void provideEventQueue(Args&&... args) {
    event_service = std::make_shared<T>((args)...);
  }

  /**
   * @brief Provide instance of scene service
   *
   * @tparam T Type of logger to provide, must be of type SceneService
   * @tparam Args Ctor arguments for T
   * @param args Argument values to be forwarded to constructor of T
   */
  template <class T, class... Args>
  static void provideSceneService(Args&&... args) {
    scene_service = std::make_shared<T>((args)...);
  }

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
  static inline std::shared_ptr<LoggingService> logging_service;

  /// Internal pointer to current Event queue instance
  static inline std::shared_ptr<EventQueue> event_service;

  /// Internal pointer to current SceneService queue instance
  static inline std::shared_ptr<SceneService> scene_service;

  /// Internal pointer to current DisplayService instance
  static inline std::shared_ptr<DisplayService> display_service;

  /// Internal pointer to current InputService instance
  static inline std::shared_ptr<InputService> input_service;

  /// Internal pointer to current AudioService instance
  static inline std::shared_ptr<AudioService> audio_service;

  /// Internal pointer to current AssetService instance
  static inline std::shared_ptr<AssetService> asset_service;

  /// Internal pointer to current ConfigService instance
  static inline std::shared_ptr<ConfigService> config_service;
};

}  // namespace afk

#endif  // INCLUDE_SERVICES_SERVICES_H_
