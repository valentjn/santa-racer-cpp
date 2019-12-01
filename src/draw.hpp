/*      
 *      Santa Racer
 *      draw.hpp
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

#ifndef SANTA_DRAW_H
#define SANTA_DRAW_H

#include <SDL/SDL.h>

namespace Santa {
    namespace Draw {
        void blit(SDL_Surface *src_surface, int src_x, int src_y, int src_w,
                  int src_h, SDL_Surface *dst_surface, int dst_x, int dst_y);
        void copy(SDL_Surface *src_surface, SDL_Surface *dst_surface,
                  int dst_x, int dst_y);
        void set_alpha(SDL_Surface *surface, Uint8 alpha);
    }
}

#endif
