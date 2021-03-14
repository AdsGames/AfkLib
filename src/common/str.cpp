/**
 * @file str.cpp
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Implementation of string function helpers
 * @version 0.1
 * @date 2021-03-08
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "common/str.h"

#include <algorithm>

namespace afk {
namespace str {

// Checks
bool isInteger(const std::string& str) {
  try {
    std::stoi(str);
    return true;
  } catch (...) {
    return false;
  }
}

bool isBoolean(const std::string& str) {
  std::string copy = str;
  std::transform(copy.begin(), copy.end(), copy.begin(), ::tolower);
  return copy == "true" || copy == "false";
}

bool isFloat(const std::string& str) {
  try {
    std::stof(str);
    return true;
  } catch (...) {
    return false;
  }
}

// Conversions
int toInteger(const std::string& str) {
  return std::stoi(str);
}

bool toBoolean(const std::string& str) {
  std::string copy = str;
  std::transform(copy.begin(), copy.end(), copy.begin(), ::tolower);
  return copy == "true";
}

float toFloat(const std::string& str) {
  return std::stof(str);
}

}  // namespace str
}  // namespace afk
