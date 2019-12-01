/*
 *      Santa Racer
 *      snowman.hpp
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

#ifndef SANTA_SNOWMAN_H
#define SANTA_SNOWMAN_H

#include "snowman_star.hpp"

namespace SantaRacer {

class Snowman {
 public:
  Snowman(void *parent);
  ~Snowman(void);

  void reinit(int tile_x, int tile_y);
  void draw(void);
  void move(void);

  int get_level_x(void);
  int get_y(void);
  int get_frame(void);
  bool is_triggered(void);
  bool query_triggered(void);

 private:
  static const int frame_count = 8;
  static const int frame_speed = frame_count;

  static const int speed_x = -100;
  static const int speed_y = -150;

  static const int trigger_offset_min = 200;
  static const int trigger_offset_max = 400;

  static const int star_count = 20;

  void *m_parent;

  int m_level_x;
  int m_y;
  int m_frame;
  int m_time;
  int m_trigger_offset;
  bool m_triggered;
  bool m_triggered_query;

  SnowmanStar **m_stars;
};

}  // namespace SantaRacer

#endif
