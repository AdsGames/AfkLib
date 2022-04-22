/**
 * @file RandomGenerator.cpp
 * @author Allan Legemaate (alegemaate@gmail.com)
 * @brief Implementation of Random class methods
 * @version 0.1
 * @date 2020-08-11
 *
 * @copyright Copyright (c) 2021
 *
 */
#include "common/random.h"

#include <chrono>

namespace afk::random {

// Init generator
std::mt19937 rng = std::mt19937(std::random_device{}());

// Random Float
float randomFloat(const float min, const float max) {
  std::uniform_real_distribution<float> float_dist{min, max};
  return float_dist(rng);
}

// Random Int
int randomInt(const int min, const int max) {
  std::uniform_int_distribution<int> int_dist{min, max};
  return int_dist(rng);
}

}  // namespace afk::random
