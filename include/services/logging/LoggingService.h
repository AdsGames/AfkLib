#ifndef SERVICES_LOGGING_LOGGING_SERVICE_H
#define SERVICES_LOGGING_LOGGING_SERVICE_H

#include <string>

/**
 * Logging Service
 * @brief Default logger class, can be overridden
 *
 * @author Allan Legemaate
 * @date 06/10/2020
 **/
class LoggingService {
 public:
  /**
   * @brief Does nothing
   *
   * @param msg Message to log
   */
  virtual void log(const std::string& msg);
};

#endif  // SERVICES_LOGGING_LOGGING_SERVICE_H
