/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include "SantaRacer/LevelObject/Chimney.hpp"

#include "SantaRacer/Globals.hpp"

namespace SantaRacer {
namespace LevelObject {

Chimney::Chimney(int map_index, int x, int width, int y) {
  m_map_index = map_index;
  m_x = x;
  m_width = width;
  m_y = y;
}

Chimney::~Chimney(void) {}

int Chimney::get_map_index(void) { return m_map_index; }

int Chimney::get_x(void) { return m_x; }

int Chimney::get_width(void) { return m_width; }

int Chimney::get_y(void) { return m_y; }

}  // namespace LevelObject
}  // namespace SantaRacer
