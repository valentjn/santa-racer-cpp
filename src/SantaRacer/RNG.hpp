/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

#include <random>

namespace SantaRacer {

class RNG {
 public:
  int getInteger(int min, int max);
  void seed();
  void seed(size_t seed);

 protected:
  std::mt19937 engine;
};

}  // namespace SantaRacer
