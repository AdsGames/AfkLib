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
#ifndef AFK_LOGGINGSERVICE_H
#define AFK_LOGGINGSERVICE_H

#include <string>
namespace afk {

/**
 * Logging Service
 * @brief Default logger class, can be overridden
 *
 **/
class LoggingService {
 public:
  virtual ~LoggingService() = default;

  /**
   * @brief Does nothing
   *
   * @param msg Message to log
   */
  virtual void log(const std::string& msg);
};

}  // namespace afk

#endif  // AFK_LOGGINGSERVICE_H
