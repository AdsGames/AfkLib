#ifndef ENGINE_LOGGING_LOGGER_H
#define ENGINE_LOGGING_LOGGER_H

#include <string>

/**
 * Logger
 * @brief Default logger class, can be overridden
 *
 * @author Allan Legemaate
 * @date 06/10/2020
 **/
class Logger {
 public:
  /**
   * @brief Does nothing
   *
   * @param msg Message to log
   */
  virtual void log(const std::string& msg);
};

#endif  // ENGINE_LOGGING_LOGGER_H
