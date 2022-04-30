/**
 * @file DebugLoggingService.cpp
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Implementation of DebugLoggingService
 * @version 0.1
 * @date 2020-10-06
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "services/logging/DebugLoggingService.h"

#include <iostream>

namespace afk {

// Log message
void DebugLoggingService::log(const std::string& message) {
  std::cout << message << std::endl;
}

}  // namespace afk
