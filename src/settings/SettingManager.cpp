#include "settings/SettingManager.h"

#include <algorithm>
#include <fstream>

#include "Locator.h"
#include "common/Exceptions.h"
#include "common/stringFns.h"

// Constructor
SettingManager::SettingManager() : autosave(false) {}

// Load file
void SettingManager::load(const std::string& path) {
  std::string line;
  std::ifstream fileStream(path);

  if (!fileStream.is_open()) {
    throw FileIOException("Could not open file from " + path);
  }

  while (getline(fileStream, line)) {
    // Split string
    int delimLoc = line.find("=");
    if (delimLoc == -1) {
      continue;
    }

    // Get values
    std::string key = line.substr(0, delimLoc);
    std::string value = line.substr(delimLoc + 1, line.length());

    // Conversion
    if (stringFns::isBoolean(value)) {
      settings[key] = stringFns::toBoolean(value);
    } else if (stringFns::isInteger(value)) {
      settings[key] = stringFns::toInteger(value);
    } else if (stringFns::isFloat(value)) {
      settings[key] = stringFns::toFloat(value);
    } else {
      settings[key] = value;
    }
  }

  fileStream.close();

  // Log
  Locator::getLogger().log("[Setting Manager] Loaded settings from file " +
                           path);

  // Set internal file name
  file_name = path;
}

// Save file
void SettingManager::save() {
  save(file_name);
}

void SettingManager::save(const std::string& path) {
  std::ofstream fileStream(path);

  if (!fileStream.is_open()) {
    throw FileIOException("Could not open file from path " + path);
  }

  for (auto const& [key, value] : this->settings) {
    fileStream << key + "=";
    fileStream << getString(key);
    fileStream << "\n";
  }

  fileStream.close();
}

// Setters
void SettingManager::set(const std::string& key, SettingType value) {
  set({key, value});
}

void SettingManager::set(const Setting pair) {
  settings[pair.first] = pair.second;

  if (autosave) {
    save();
  }
}

// Find
const Setting SettingManager::findSetting(const std::string& key) const {
  auto it = std::find_if(
      settings.begin(), settings.end(),
      [key](const Setting& setting) { return setting.first == key; });

  if (it != settings.end()) {
    return *it;
  }

  throw KeyLookupException("Could not find setting " + key);
}

// Set autosave
void SettingManager::setAutosave(const bool autosave) {
  this->autosave = autosave;
}