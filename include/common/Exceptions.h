/**
 * @file Exceptions.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Interally used exceptions. These can be handled properly in the main
 * game class.
 * @version 0.1
 * @date 2021-03-08
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INCLUDE_COMMON_EXCEPTIONS_H_
#define INCLUDE_COMMON_EXCEPTIONS_H_

#include <stdexcept>
#include <string>

namespace afk {

/**
 * @brief Exception raised when a file is not found
 *
 */
class FileIOException : public std::runtime_error {
 public:
  /**
   * @brief Construct a new File I O Exception object
   *
   * @param msg Message to pass to runtime_error.
   */
  explicit FileIOException(const std::string& msg) : std::runtime_error(msg) {}
};

/**
 * @brief Exception raised when a core feature can not load
 *
 */
class InitException : public std::runtime_error {
 public:
  /**
   * @brief Construct a new Init Exception object
   *
   * @param msg Message to pass to runtime_error.
   */
  explicit InitException(const std::string& msg) : std::runtime_error(msg) {}
};

/**
 * @brief Exception raised when an item can not be found by key
 *
 */
class KeyLookupException : public std::runtime_error {
 public:
  /**
   * @brief Construct a new Key Lookup Exception object
   *
   * @param msg Message to pass to runtime_error.
   */
  explicit KeyLookupException(const std::string& msg)
      : std::runtime_error(msg) {}
};

/**
 * @brief Exception raised when a core service can not be found
 *
 */
class CoreServiceLookupException : public std::runtime_error {
 public:
  /**
   * @brief Construct a new Core Service Lookup Exception object
   *
   * @param msg Message to pass to runtime_error.
   */
  explicit CoreServiceLookupException(const std::string& msg)
      : std::runtime_error(msg) {}
};

/**
 * @brief Exception raised when a core service can not be found
 *
 */
class InvalidParameterException : public std::runtime_error {
 public:
  /**
   * @brief Construct a new Invalid Parameter Exception object
   *
   * @param msg Message to pass to runtime_error.
   */
  explicit InvalidParameterException(const std::string& msg)
      : std::runtime_error(msg) {}
};

/**
 * @brief Exception raised when a scene can not be found
 *
 */
class SceneLookupException : public std::runtime_error {
 public:
  /**
   * @brief Construct a new Invalid Parameter Exception object
   *
   * @param msg Message to pass to runtime_error.
   */
  explicit SceneLookupException(const std::string& msg)
      : std::runtime_error(msg) {}
};

}  // namespace afk

#endif  // INCLUDE_COMMON_EXCEPTIONS_H_
