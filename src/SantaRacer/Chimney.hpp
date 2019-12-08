/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

#include <cstdlib>

namespace SantaRacer {

class Chimney {
 public:
  Chimney(size_t mapValue, int x, size_t width, int y);

  size_t getMapValue() const;
  int getX() const;
  size_t getWidth() const;
  int getY() const;
  size_t getHeight() const;

 protected:
  const size_t height = 5;

  size_t mapValue;
  int x;
  size_t width;
  int y;
};

}  // namespace SantaRacer
