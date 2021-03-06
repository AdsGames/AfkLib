#include "services/logging/DebugLoggingService.h"

#include <iostream>

namespace afk {

// Log message
void DebugLoggingService::log(const std::string& message) {
  std::cout << message << std::endl;
}

}