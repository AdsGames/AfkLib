#ifndef INCLUDE_SERVICES_LOGGING_DEBUGLOGGINGSERVICE_H_
#define INCLUDE_SERVICES_LOGGING_DEBUGLOGGINGSERVICE_H_

#include <string>

#include "LoggingService.h"

namespace afk {

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
  void log(const std::string& msg) override;
};

}  // namespace afk

#endif  // INCLUDE_SERVICES_LOGGING_DEBUGLOGGINGSERVICE_H_
