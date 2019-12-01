/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#ifndef SANTA_FINISH_H
#define SANTA_FINISH_H

namespace SantaRacer {

class Finish {
 public:
  Finish(void *parent);
  ~Finish(void);

  void reinit(int tile_x, int tile_y);
  void draw(void);
  void move(void);

  int get_level_x(void);
  int get_y(void);
  int get_frame(void);

  bool reached(void);

 private:
  void *m_parent;

  int m_level_x;
  int m_y;
};

}  // namespace SantaRacer

#endif
