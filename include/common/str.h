/**
 * @file str.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Helpers which can manipulate or get data from strings
 * @version 0.1
 * @date 2021-03-08
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INCLUDE_COMMON_STR_H_
#define INCLUDE_COMMON_STR_H_

#include <memory>
#include <string>

#include "Exceptions.h"

namespace afk {
namespace str {

/**
 * @brief Check if string is an integer
 *
 * @param str String to check
 * @return True if the string is an integer
 * @see toInteger
 */
extern bool isInteger(const std::string& str);

/**
 * @brief Check if string is a boolean
 *
 * @param str String to check
 * @return True if the string is a boolean
 * @see toBoolean
 */
extern bool isBoolean(const std::string& str);

/**
 * @brief Check if string is a float
 *
 * @param str String to check
 * @return True if the string is a float
 * @see toFloat
 */
extern bool isFloat(const std::string& str);

/**
 * @brief Convert string to integer. Should check first with isInteger if it can
 * be converted.
 *
 * @param str String to convert
 * @return Integer value of string
 * @throws std::invalid_argument exception if it could not be converted
 * @see isInteger
 */
extern int toInteger(const std::string& str);

/**
 * @brief Convert string to boolean
 *
 * @param str String to convert
 * @return True of string is "true" false otherwise
 * @see isBoolean
 */
extern bool toBoolean(const std::string& str);

/**
 * @brief Convert string to float. Should check first with isFloat if it can
 * be converted.
 *
 * @param str String to convert
 * @return Float value of string
 * @throws std::invalid_argument exception if it could not be converted
 * @see isFloat
 */
extern float toFloat(const std::string& str);

/**
 * @brief Format string according to arguments. Uses snprintf internally
 *
 * @tparam Args Format arg types
 * @param format String to format
 * @param args Arguments to format against
 * @return Formatted string
 * @throws InvalidParameterException thrown if the string could not be formatted
 */
template <typename... Args>
std::string format(const std::string& format, Args... args) {
  int size = snprintf(nullptr, 0, format.c_str(), args...) + 1;
  if (size <= 0) {
    throw InvalidParameterException("Error during formatting.");
  }
  std::unique_ptr<char[]> buf(new char[size]);
  snprintf(buf.get(), size, format.c_str(), args...);
  return std::string(buf.get(), buf.get() + size - 1);
}

}  // namespace str
}  // namespace afk

#endif  // INCLUDE_COMMON_STR_H_
