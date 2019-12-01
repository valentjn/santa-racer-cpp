/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

namespace SantaRacer {
namespace LevelObject {

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

}  // namespace LevelObject
}  // namespace SantaRacer
