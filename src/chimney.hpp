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

#ifndef SANTA_CHIMNEY_H
#define SANTA_CHIMNEY_H

namespace SantaRacer {

class Chimney {
 public:
  static const int chimney_height = 5;

  Chimney(int map_index, int x, int width, int y);
  ~Chimney(void);

  int get_map_index(void);
  int get_x(void);
  int get_width(void);
  int get_y(void);

 private:
  int m_map_index;
  int m_x;
  int m_width;
  int m_y;
};

}  // namespace SantaRacer

#endif
