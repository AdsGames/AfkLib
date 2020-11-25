#ifndef ENGINE_LOGGIN_DEBUG_LOGGER_H
#define ENGINE_LOGGIN_DEBUG_LOGGER_H

#include "Logger.h"

/**
 * Debug Logger
 * @brief Actually logs messages
 *
 * @author Allan Legemaate
 * @date 06/10/2020
 **/
class DebugLogger : public Logger {
 public:
  /**
   * @brief Log message to console
   *
   * @param msg Message to log
   */
  virtual void log(const std::string& msg) override;
};

#endif  // ENGINE_LOGGIN_DEBUG_LOGGER_H
