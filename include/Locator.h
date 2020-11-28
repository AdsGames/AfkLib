#ifndef ENGINE_LOCATOR_H
#define ENGINE_LOCATOR_H

#include <memory>

#include "EventQueue.h"
#include "assets/AssetManager.h"
#include "audio/AudioService.h"
#include "display/Window.h"
#include "input/Input.h"
#include "logging/Logger.h"
#include "scene/SceneManager.h"
#include "settings/SettingManager.h"

/**
 * @brief Core service locator for engine features
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
   * @brief Provide instance of asset manager
   *
   * @tparam T Type of asset manager to provide, must be of type AssetManager
   * @tparam Args Ctor arguments for T
   * @param args Argument values to be forwarded to constructor of T
   */
  template <class T, class... Args>
  static void provideAssetManager(Args&&... args) {
    asset_service = std::make_unique<T>((args)...);
  }

  /**
   * @brief Provide instance of window manager
   *
   * @tparam T Type of window to provide, must be of type Window
   * @tparam Args Ctor arguments for T
   * @param args Argument values to be forwarded to constructor of T
   */
  template <class T, class... Args>
  static void provideWindow(Args&&... args) {
    window_service = std::make_unique<T>((args)...);
  }

  /**
   * @brief Provide instance of settings manager
   *
   * @tparam T Type of settings manager to provide, must be of type
   * SettingManager
   * @tparam Args Ctor arguments for T
   * @param args Argument values to be forwarded to constructor of T
   */
  template <class T, class... Args>
  static void provideSettings(Args&&... args) {
    setting_service = std::make_unique<T>((args)...);
  }

  /**
   * @brief Provide instance of logger
   *
   * @tparam T Type of logger to provide, must be of type Logger
   * @tparam Args Ctor arguments for T
   * @param args Argument values to be forwarded to constructor of T
   */
  template <class T, class... Args>
  static void provideLogger(Args&&... args) {
    logger_service = std::make_unique<T>((args)...);
  }

  /**
   * @brief Provide instance of input
   *
   * @tparam T Type of logger to provide, must be of type Input
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
   * @brief Provide instance of scene manager
   *
   * @tparam T Type of logger to provide, must be of type Scene Manager
   * @tparam Args Ctor arguments for T
   * @param args Argument values to be forwarded to constructor of T
   */
  template <class T, class... Args>
  static void provideSceneManager(Args&&... args) {
    scene_service = std::make_unique<T>((args)...);
  }

  /**
   * @brief Get the AudioService object
   *
   * @return AudioService& Reference to current audio service
   */
  static AudioService& getAudio();

  /**
   * @brief Get the AssetManager object
   *
   * @return AssetManager&
   */
  static AssetManager& getAsset();

  /**
   * @brief Get the Window object
   *
   * @return Window& Reference to current window
   */
  static Window& getWindow();

  /**
   * @brief Get the SettingManager object
   *
   * @return SettingManager& Reference to current setting manager
   */
  static SettingManager& getSettings();

  /**
   * @brief Get the Logger object
   *
   * @return Logger& Reference to current setting manager
   */
  static Logger& getLogger();

  /**
   * @brief Get the Input object
   *
   * @return Logger& Reference to current setting manager
   */
  static Input& getInput();

  /**
   * @brief Get the event queue object
   *
   * @return EventQueue& Reference to current event queue
   */
  static EventQueue& getEventQueue();

  /**
   * @brief Get the scene manager object
   *
   * @return EventQueue& Reference to current scene manager
   */
  static SceneManager& getSceneManager();

 private:
  /// Internal pointer to current AudioService instance
  static inline std::unique_ptr<AudioService> audio_service;

  /// Internal pointer to current AssetManager instance
  static inline std::unique_ptr<AssetManager> asset_service;

  /// Internal pointer to current Window instance
  static inline std::unique_ptr<Window> window_service;

  /// Internal pointer to current SettingManager instance
  static inline std::unique_ptr<SettingManager> setting_service;

  /// Internal pointer to current Logger instance
  static inline std::unique_ptr<Logger> logger_service;

  /// Internal pointer to current Input instance
  static inline std::unique_ptr<Input> input_service;

  /// Internal pointer to current Event queue instance
  static inline std::unique_ptr<EventQueue> event_service;

  /// Internal pointer to current Event queue instance
  static inline std::unique_ptr<SceneManager> scene_service;
};

#endif  // ENGINE_LOCATOR_H