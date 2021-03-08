/**
 * @file LoggingService.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Default logging service. Does nothing. Use in production.
 * @version 0.1
 * @date 2020-10-06
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INCLUDE_SERVICES_LOGGING_LOGGINGSERVICE_H_
#define INCLUDE_SERVICES_LOGGING_LOGGINGSERVICE_H_

#include <string>
namespace afk {

/**
 * Logging Service
 * @brief Default logger class, can be overridden
 *
 **/
class LoggingService {
 public:
  virtual ~LoggingService() {}

  /**
   * @brief Does nothing
   *
   * @param msg Message to log
   */
  virtual void log(const std::string& msg);
};

}  // namespace afk

#endif  // INCLUDE_SERVICES_LOGGING_LOGGINGSERVICE_H_
