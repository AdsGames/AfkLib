#include "services/logging/DebugLoggingService.h"

#include <iostream>

// Log message
void DebugLoggingService::log(const std::string& message) {
  std::cout << message << std::endl;
}