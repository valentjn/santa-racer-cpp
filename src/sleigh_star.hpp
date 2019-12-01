/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#ifndef SANTA_SLEIGH_STAR_H
#define SANTA_SLEIGH_STAR_H

#include <SDL/SDL.h>

namespace SantaRacer {

class SleighStar {
 public:
  SleighStar(void);
  void reinit(bool first_init = false);
  void draw(void);
  void move(void);
  int get_frame(void);

 private:
  int m_level_x;
  int m_y;
  int m_width;
  int m_height;
  int m_frame;
  int m_max_frame;
  int m_time;

  SDL_Surface *m_surface;
  SDL_Surface *m_surface_drunken;

  static const int frame_count = 17;
  static const int max_frame_count = 30;
  static const int frame_speed = 2 * frame_count;
  static const int min_x_offset = -10;
  static const int max_x_offset = 140;
  static const int min_y_offset = 0;
  static const int max_y_offset = 10;
};

}  // namespace SantaRacer

#endif
