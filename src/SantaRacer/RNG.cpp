/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include <random>

#include "SantaRacer/RNG.hpp"

namespace SantaRacer {

// both min and max inclusive
int RNG::getInteger(int min, int max) {
  std::uniform_int_distribution<int> distribution(min, max);
  return distribution(engine);
}

void RNG::seed() {
  std::random_device randomDevice;
  seed(randomDevice());
}

void RNG::seed(size_t seed) {
  engine.seed(seed);
}

}  // namespace SantaRacer
