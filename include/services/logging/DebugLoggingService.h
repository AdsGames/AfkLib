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
#ifndef AFK_DEBUGLOGGINGSERVICE_H
#define AFK_DEBUGLOGGINGSERVICE_H

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

#endif  // AFK_DEBUGLOGGINGSERVICE_H
