#ifndef ENGINE_LOGGIN_LOGGER_H
#define ENGINE_LOGGIN_LOGGER_H

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
   * @brief Create a new instance of logger
   *
   * @constructor
   */
  Logger(){};

  /**
   * Destroy instance of logger
   *
   * @destructor
   */
  virtual ~Logger(){};

  /**
   * @brief Does nothing
   *
   * @param msg Message to log
   */
  virtual void log(const std::string& msg);
};

#endif  // ENGINE_LOGGIN_LOGGER_H
