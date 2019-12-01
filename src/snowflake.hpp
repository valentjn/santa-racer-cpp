/*
 *      Santa Racer
 *      snowflake.hpp
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

#ifndef SANTA_SNOWFLAKE_H
#define SANTA_SNOWFLAKE_H

namespace SantaRacer {

class Snowflake {
 public:
  Snowflake(void);
  void reinit(bool first_init = false);
  void draw(void);
  void move(void);
  void change_speed(void);
  float get_level_x(void);
  float get_y(void);

 private:
  int m_z;
  int m_speed_x;
  int m_speed_y;
  int m_speed_change_time;
  int m_time;

  float m_level_x;
  float m_y;

  unsigned int m_color;

  static const int min_speed_x = -40;
  static const int max_speed_x = 40;
  static const int min_speed_y = 40;
  static const int max_speed_y = 160;
  static const int min_speed_change_time = 25;
  static const int max_speed_change_time = 250;
  static const int left_margin = -50;
};

}  // namespace SantaRacer

#endif
