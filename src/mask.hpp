/*
 *      Santa Racer
 *      mask.hpp
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
