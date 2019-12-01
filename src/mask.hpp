/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#ifndef SANTA_MASK_H
#define SANTA_MASK_H

#include <SDL/SDL.h>

namespace SantaRacer {

class Mask {
 public:
  Mask(SDL_Surface *surface, int frame_count);
  ~Mask(void);
  bool is_colliding(int x, int y, int frame, Mask *mask2, int x2, int y2,
                    int frame2);
  int get_width(void);
  int get_height(void);
  bool **get_array(void);

 private:
  SDL_Surface *m_surface;
  int m_frame_count;
  int m_complete_width;
  int m_width;
  int m_height;
  bool **m_array;
};

}  // namespace SantaRacer

#endif
