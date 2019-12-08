/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include "SantaRacer/Chimney.hpp"

namespace SantaRacer {

Chimney::Chimney(size_t mapValue, int x, size_t width, int y) :
    mapValue(mapValue), x(x), width(width), y(y) {
}

size_t Chimney::getMapValue() const {
  return mapValue;
}

int Chimney::getX() const {
  return x;
}

size_t Chimney::getWidth() const {
  return width;
}

int Chimney::getY() const {
  return y;
}

size_t Chimney::getHeight() const {
  return height;
}

}  // namespace SantaRacer
