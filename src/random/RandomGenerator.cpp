#include "random/RandomGenerator.h"

#include <chrono>

// Init generator
std::mt19937 RandomGenerator::rng = std::mt19937(std::random_device{}());

// Random Float
float RandomGenerator::randomFloat(const float min, const float max) {
  std::uniform_real_distribution<float> float_dist{min, max};
  return float_dist(rng);
}

// Random Int
int RandomGenerator::randomInt(const int min, const int max) {
  std::uniform_int_distribution<int> int_dist{min, max};
  return int_dist(rng);
}