/**
 * @file ConfigService.cpp
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Implementation of default Config Service
 * @version 0.1
 * @date 2020-11-05
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "services/config/ConfigService.h"

#include <algorithm>
#include <fstream>

#include "common/str.h"
#include "services/Services.h"

namespace afk {

// Constructor
ConfigService::ConfigService() : autoSave(false) {
  Services::getLoggingService().log("[Config Service]: Starting up");
}

// Destructor
ConfigService::~ConfigService() {
  Services::getLoggingService().log("[Config Service]: Shutting down");
}

// Load file
void ConfigService::load(const std::string& path) {
  std::string line;
  std::ifstream fileStream(path);

  if (!fileStream.is_open()) {
    throw FileIoException("Could not open file from " + path);
  }

  while (getline(fileStream, line)) {
    // Split string
    int delimiterLocation = line.find('=');
    if (delimiterLocation == -1) {
      continue;
    }

    // Get values
    std::string key = line.substr(0, delimiterLocation);
    std::string value = line.substr(delimiterLocation + 1, line.length());

    // Conversion
    settings[key] = value;
  }

  fileStream.close();

  // Log
  Services::getLoggingService().log(
      "[Setting Manager] Loaded settings from file " + path);

  // Set internal file name
  fileName = path;
}

// Save file
void ConfigService::save() {
  save(fileName);
}

void ConfigService::save(const std::string& path) {
#ifdef __EMSCRIPTEN__
  return;
#endif

  std::ofstream fileStream(path);

  if (!fileStream.is_open()) {
    throw FileIoException("Could not open file from path " + path);
  }

  for (auto const& entry : this->settings) {
    fileStream << entry.first + "=" + entry.second + "\n";
  }

  fileStream.close();
}

// Set auto save
void ConfigService::setAutoSave(const bool autoSave) {
  this->autoSave = autoSave;
}

}  // namespace afk
