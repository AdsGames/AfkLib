/**
 * @file DebugLoggingService.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Logging service that does the logging. Used for development
 * @version 0.1
 * @date 2020-10-06
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INCLUDE_SERVICES_LOGGING_DEBUGLOGGINGSERVICE_H_
#define INCLUDE_SERVICES_LOGGING_DEBUGLOGGINGSERVICE_H_

#include <string>

#include "LoggingService.h"

namespace afk {

/**
 * Debug Logger
 * @brief Actually logs messages
 *
 **/
class DebugLoggingService : public LoggingService {
 public:
  /**
   * @brief Log message to console
   *
   * @param msg Message to log
   */
  void log(const std::string& msg) override;
};

}  // namespace afk

#endif  // INCLUDE_SERVICES_LOGGING_DEBUGLOGGINGSERVICE_H_
