/*
 *      Santa Racer
 *      chimney.hpp
 *
 *      Copyright (C) 2010 Julian Valentin.
 *
 *      This program is free software: you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation, either version 3 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "chimney.hpp"

#include "globals.hpp"

Santa::Chimney::Chimney(int map_index, int x, int width, int y) {
  m_map_index = map_index;
  m_x = x;
  m_width = width;
  m_y = y;
}

Santa::Chimney::~Chimney(void) {}

int Santa::Chimney::get_map_index(void) { return m_map_index; }

int Santa::Chimney::get_x(void) { return m_x; }

int Santa::Chimney::get_width(void) { return m_width; }

int Santa::Chimney::get_y(void) { return m_y; }
