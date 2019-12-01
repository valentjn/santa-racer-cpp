/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

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
