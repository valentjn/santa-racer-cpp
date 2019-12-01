/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#ifndef SANTA_DRAW_H
#define SANTA_DRAW_H

#include <SDL/SDL.h>

namespace SantaRacer {
namespace Draw {

void blit(SDL_Surface *src_surface, int src_x, int src_y, int src_w, int src_h,
          SDL_Surface *dst_surface, int dst_x, int dst_y);
void copy(SDL_Surface *src_surface, SDL_Surface *dst_surface, int dst_x,
          int dst_y);
void set_alpha(SDL_Surface *surface, Uint8 alpha);

}  // namespace Draw
}  // namespace SantaRacer

#endif
