#include "common/str.h"

#include <algorithm>

namespace afk::str {

// Checks
bool isInteger(std::string str) {
  try {
    std::stoi(str);
    return true;
  } catch (...) {
    return false;
  }
}

bool isBoolean(std::string str) {
  std::transform(str.begin(), str.end(), str.begin(), ::tolower);
  return str == "true" || str == "false";
}

bool isFloat(std::string str) {
  try {
    std::stof(str);
    return true;
  } catch (...) {
    return false;
  }
}

// Conversions
int toInteger(std::string str) {
  return std::stoi(str);
}

bool toBoolean(std::string str) {
  std::transform(str.begin(), str.end(), str.begin(), ::tolower);
  return str == "true";
}

float toFloat(std::string str) {
  return std::stof(str);
}

}