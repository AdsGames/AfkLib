/**
 * @file RandomGenerator.h
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Static helper class that can create random numbers.
 * @version 0.1
 * @date 2020-08-11
 *
 * @copyright Copyright (c) 2021
 *
 */
#ifndef INCLUDE_RANDOM_RANDOMGENERATOR_H_
#define INCLUDE_RANDOM_RANDOMGENERATOR_H_

#include <random>

namespace afk::random {

/**
 * @brief Returns a random float between two numbers
 *
 * @param min Min number
 * @param max Max number
 * @return Random number
 */
float randomFloat(const float min, const float max);

/**
 * @brief Returns a random int between two numbers
 *
 * @param min Min number
 * @param max Max number
 * @return Random number
 */
int randomInt(const int min, const int max);

/// Random number generator
extern std::mt19937 rng;

}  // namespace afk::random

#endif  // INCLUDE_RANDOM_RANDOMGENERATOR_H_
