/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

namespace SantaRacer {
namespace LevelObject {

class GoblinSnowball {
 public:
  GoblinSnowball(void *parent);
  ~GoblinSnowball(void);

  void reinit(int tile_x, int tile_y);
  void draw(void);
  void move(void);

  int get_level_x(void);
  int get_y(void);
  int get_frame(void);

 private:
  static const int frame_count = 1;

  static const int gravity_acceleration = 80;
  static const int speed_x = -200;
  static const int speed_y_start = -250;

  static const int offset_x = 45;
  static const int offset_y = 40;

  void *m_parent;

  int m_level_x;
  int m_y;
  int m_frame;
  int m_time;
};

}  // namespace LevelObject
}  // namespace SantaRacer
