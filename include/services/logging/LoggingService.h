#ifndef INCLUDE_SERVICES_LOGGING_LOGGINGSERVICE_H_
#define INCLUDE_SERVICES_LOGGING_LOGGINGSERVICE_H_

#include <string>
namespace afk {

/**
 * Logging Service
 * @brief Default logger class, can be overridden
 *
 * @author Allan Legemaate
 * @date 06/10/2020
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
