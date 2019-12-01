/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#ifndef SANTA_ANGEL_H
#define SANTA_ANGEL_H

namespace SantaRacer {

class Angel {
 public:
  Angel(void *parent);
  ~Angel(void);

  void reinit(int tile_x, int tile_y);
  void draw(void);
  void move(void);

  int get_level_x(void);
  int get_y(void);
  int get_frame(void);

 private:
  static const int frame_count = 13;
  static const int frame_speed = frame_count;

  void *m_parent;

  int m_level_x;
  int m_y;
  int m_frame;
  int m_time;
};

}  // namespace SantaRacer

#endif
