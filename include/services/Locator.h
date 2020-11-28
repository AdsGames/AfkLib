#ifndef SERVICES_LOCATOR_H
#define SERVICES_LOCATOR_H

#include <memory>

#include "EventQueue.h"
#include "assets/AssetService.h"
#include "audio/AudioService.h"
#include "config/ConfigService.h"
#include "display/DisplayService.h"
#include "input/InputService.h"
#include "logging/LoggingService.h"
#include "scene/SceneService.h"

/**
 * @brief Core service locator for engine services
 *
 * @author Allan Legemaate
 * @date 7/11/2020
 */
class Locator {
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
  static void provideAudio(Args&&... args) {
    audio_service = std::make_unique<T>((args)...);
  }

  /**
   * @brief Provide instance of asset service
   *
   * @tparam T Type of asset service to provide, must be of type AssetService
   * @tparam Args Ctor arguments for T
   * @param args Argument values to be forwarded to constructor of T
   */
  template <class T, class... Args>
  static void provideAsset(Args&&... args) {
    asset_service = std::make_unique<T>((args)...);
  }

  /**
   * @brief Provide instance of display service
   *
   * @tparam T Type of window to provide, must be of type Window
   * @tparam Args Ctor arguments for T
   * @param args Argument values to be forwarded to constructor of T
   */
  template <class T, class... Args>
  static void provideDisplay(Args&&... args) {
    display_service = std::make_unique<T>((args)...);
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
  static void provideConfig(Args&&... args) {
    config_service = std::make_unique<T>((args)...);
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
  static void provideLogging(Args&&... args) {
    logging_service = std::make_unique<T>((args)...);
  }

  /**
   * @brief Provide instance of input service
   *
   * @tparam T Type of logger to provide, must be of type InputService
   * @tparam Args Ctor arguments for T
   * @param args Argument values to be forwarded to constructor of T
   */
  template <class T, class... Args>
  static void provideInput(Args&&... args) {
    input_service = std::make_unique<T>((args)...);
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
    event_service = std::make_unique<T>((args)...);
  }

  /**
   * @brief Provide instance of scene service
   *
   * @tparam T Type of logger to provide, must be of type SceneService
   * @tparam Args Ctor arguments for T
   * @param args Argument values to be forwarded to constructor of T
   */
  template <class T, class... Args>
  static void provideScene(Args&&... args) {
    scene_service = std::make_unique<T>((args)...);
  }

  /**
   * @brief Get the AudioService
   *
   * @return AudioService& Reference to current audio service
   */
  static AudioService& getAudio();

  /**
   * @brief Get the AssetService
   *
   * @return AssetService& Reference to current asset service
   */
  static AssetService& getAsset();

  /**
   * @brief Get the DisplayService
   *
   * @return DisplayService& Reference to current display service
   */
  static DisplayService& getDisplay();

  /**
   * @brief Get the ConfigService
   *
   * @return ConfigService& Reference to current config service
   */
  static ConfigService& getConfig();

  /**
   * @brief Get the LoggingService
   *
   * @return LoggingService& Reference to current logging service
   */
  static LoggingService& getLogger();

  /**
   * @brief Get the InputService
   *
   * @return InputService& Reference to current input service
   */
  static InputService& getInput();

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
  static SceneService& getScene();

 private:
  /// Internal pointer to current AudioService instance
  static inline std::unique_ptr<AudioService> audio_service;

  /// Internal pointer to current AssetService instance
  static inline std::unique_ptr<AssetService> asset_service;

  /// Internal pointer to current DisplayService instance
  static inline std::unique_ptr<DisplayService> display_service;

  /// Internal pointer to current ConfigService instance
  static inline std::unique_ptr<ConfigService> config_service;

  /// Internal pointer to current LoggingService instance
  static inline std::unique_ptr<LoggingService> logging_service;

  /// Internal pointer to current InputService instance
  static inline std::unique_ptr<InputService> input_service;

  /// Internal pointer to current Event queue instance
  static inline std::unique_ptr<EventQueue> event_service;

  /// Internal pointer to current SceneService queue instance
  static inline std::unique_ptr<SceneService> scene_service;
};

#endif  // SERVICES_LOCATOR_H