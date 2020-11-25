#include "common/stringFns.h"

#include <algorithm>

// Checks
bool stringFns::isInteger(std::string str) {
  try {
    std::stoi(str);
    return true;
  } catch (...) {
    return false;
  }
}

bool stringFns::isBoolean(std::string str) {
  std::transform(str.begin(), str.end(), str.begin(), ::tolower);
  return str == "true" || str == "false";
}

bool stringFns::isFloat(std::string str) {
  try {
    std::stof(str);
    return true;
  } catch (...) {
    return false;
  }
}

// Conversions
int stringFns::toInteger(std::string str) {
  return std::stoi(str);
}

bool stringFns::toBoolean(std::string str) {
  std::transform(str.begin(), str.end(), str.begin(), ::tolower);
  return str == "true";
}

float stringFns::toFloat(std::string str) {
  return std::stof(str);
}