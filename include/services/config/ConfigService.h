#ifndef SERVICES_CONFIG_CONFIG_SERVICE_H
#define SERVICES_CONFIG_CONFIG_SERVICE_H

#include <iostream>
#include <map>
#include <string>
#include <variant>

namespace afk {

/**
 * @brief Varient defining allowed setting types
 *
 */
typedef std::variant<std::string, int, bool, float> SettingType;

/**
 * @brief Pair defining what a setting pair should look like
 *
 */
typedef std::pair<std::string, SettingType> Setting;

/**
 * @brief Class which can load and store setting key pair values in different
 * formats
 *
 * @author Allan Legemaate
 * @date 05/11/2020
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

    if (it != settings.end()) {
      return std::get<T>(it->second);
    }

    return fallback;
  }

  /**
   * @brief Get string value of setting
   *
   * @param key Key of setting to lookup
   * @return std::string String value or empty string if not found
   */
  std::string getString(const std::string& key) const {
    auto it = settings.find(key);

    if (it == settings.end()) {
      return "";
    }

    switch (it->second.index()) {
      case 0:
        return std::get<std::string>(it->second);
      case 1:
        return std::to_string(std::get<int>(it->second));
      case 2:
        return std::get<bool>(it->second) ? "true" : "false";
      case 3:
        return std::to_string(std::get<float>(it->second));
      default:
        return "";
    }
  }

  /**
   * @brief Set setting value of id key
   *
   * @param key Id of setting
   * @param value Value of setting
   */
  void set(const std::string& key, SettingType value);

  /**
   * @brief Set setting value of id key
   *
   * @param pair Setting pair
   */
  void set(const Setting pair);

  /**
   * @brief Set the autosave config
   *
   * @param autosave If set to true, will autosave on each set to the original
   * file path
   */
  void setAutosave(const bool autosave);

 private:
  /// Name of file for save, and autosave reference
  std::string file_name;

  /// Autosave enabled status
  bool autosave;

  /// Container which stores all settings
  std::map<std::string, SettingType> settings;
};

}  // namespace afk

#endif  // SERVICES_CONFIG_CONFIG_SERVICE_H
