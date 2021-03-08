#ifndef RANDOM_RANDOM_GENERATOR_H
#define RANDOM_RANDOM_GENERATOR_H

#include <random>

namespace afk {

/**
 * @brief Random number generator
 * @author Allan Legemaate
 * @date 11/08/2020
 */
class Random {
 public:
  /**
   * @brief Returns a random float between two numbers
   *
   * @param min Min number
   * @param max Max number
   * @return Random number
   */
  static float randomFloat(const float min, const float max);

  /**
   * @brief Returns a random int between two numbers
   *
   * @param min Min number
   * @param max Max number
   * @return Random number
   */
  static int randomInt(const int min, const int max);

 private:
  /// Random number generator
  static std::mt19937 rng;
};

}  // namespace afk

#endif  // RANDOM_RANDOM_GENERATOR_H
