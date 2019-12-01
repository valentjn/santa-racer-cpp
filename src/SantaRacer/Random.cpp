/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include "SantaRacer/Globals.hpp"
#include "SantaRacer/Random.hpp"

namespace SantaRacer {
namespace Random {

// both min and max inclusive
int rnd(int min, int max) {
  return int(rand() / (float(RAND_MAX) + 1) * (max - min + 1)) + min;
}

void seed(void) { srand(time(nullptr)); }

}  // namespace Random
}  // namespace SantaRacer
