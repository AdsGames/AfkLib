#include "logging/DebugLogger.h"

#include <iostream>

// Log message
void DebugLogger::log(const std::string& message) {
  std::cout << message << std::endl;
}