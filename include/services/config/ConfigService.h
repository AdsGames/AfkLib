/**
 * @file ConfigService.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Header for default Config Service
 * @version 0.1
 * @date 2020-11-05
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef AFK_CONFIGSERVICE_H
#define AFK_CONFIGSERVICE_H

#include <sstream>
#include <string>
#include <unordered_map>
#include <utility>

namespace afk {

/**
 * @brief Pair defining what a setting pair should look like
 *
 */
typedef std::pair<std::string, std::string> Setting;

/**
 * @brief Class which can load and store setting key pair values in different
 * formats
 *
 */
class ConfigService {
 public:
  /**
   * @brief Construct a new ConfigService object
   *
   */
  ConfigService();

  /**
   * @brief Destroy
   *
   */
  ~ConfigService();

  /**
   * @brief Load settings from file
   *
   * @param path File to load from
   */
  void load(const std::string& path);

  /**
   * @brief Save settings back to file which it was loaded from
   *
   */
  void save();

  /**
   * @brief Save settings to a specific file
   *
   * @param path Path to file to save to
   */
  void save(const std::string& path);

  /**
   * @brief Get setting from setting manager
   *
   * @tparam T Type of setting to get, should be int, float, boolean, string
   * @param key Key of string to lookup
   * @param fallback Fallback value in case the setting was not found
   * @return Setting value or fallback if not found
   */
  template <class T>
  T get(const std::string& key, T fallback) const {
    auto it = settings.find(key);

    if (it == settings.end()) {
      return fallback;
    }

    std::stringstream convert((*it).second);
    T value;
    convert >> value;
    return value;
  }

  /**
   * @brief Set setting value of id key
   *
   * @param key Id of setting
   * @param value Value of setting
   */
  template <class T>
  void set(const std::string& key, const T value) {
    std::string sVal = std::to_string(value);

    settings[key] = sVal;

    if (autoSave) {
      save();
    }
  }

  /**
   * @brief Set the auto save config
   *
   * @param autoSave If set to true, will auto save on each set to the original
   * file path
   */
  void setAutoSave(bool autoSave);

 private:
  /// Name of file for save, and auto save reference
  std::string fileName;

  /// Auto save enabled status
  bool autoSave;

  /// Container which stores all settings
  std::unordered_map<std::string, std::string> settings;
};

}  // namespace afk

#endif  // AFK_CONFIGSERVICE_H
