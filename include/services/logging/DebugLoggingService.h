#ifndef SERVICES_LOGGING_DEBUG_LOGGING_SERVICE_H
#define SERVICES_LOGGING_DEBUG_LOGGING_SERVICE_H

#include "LoggingService.h"

/**
 * Debug Logger
 * @brief Actually logs messages
 *
 * @author Allan Legemaate
 * @date 06/10/2020
 **/
class DebugLoggingService : public LoggingService {
 public:
  /**
   * @brief Log message to console
   *
   * @param msg Message to log
   */
  virtual void log(const std::string& msg) override;
};

#endif  // SERVICES_LOGGING_DEBUG_LOGGING_SERVICE_H
