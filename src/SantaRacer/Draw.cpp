/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include "SantaRacer/Draw.hpp"

#include "SantaRacer/Globals.hpp"

void SantaRacer::Draw::blit(SDL_Surface *src_surface, int src_x, int src_y,
                       int src_w, int src_h, SDL_Surface *dst_surface,
                       int dst_x, int dst_y) {
  SDL_Rect src_rect;
  SDL_Rect dst_rect;

  src_rect.x = src_x;
  src_rect.y = src_y;
  src_rect.w = src_w;
  src_rect.h = src_h;
  dst_rect.x = dst_x;
  dst_rect.y = dst_y;
  SDL_BlitSurface(src_surface, &src_rect, dst_surface, &dst_rect);
}

void SantaRacer::Draw::copy(SDL_Surface *src_surface, SDL_Surface *dst_surface,
                       int dst_x, int dst_y) {
  SDL_Rect dst_rect;

  dst_rect.x = dst_x;
  dst_rect.y = dst_y;
  SDL_BlitSurface(src_surface, nullptr, dst_surface, &dst_rect);
}

void SantaRacer::Draw::set_alpha(SDL_Surface *surface, Uint8 alpha) {
  int x;
  int y;
  Uint8 r;
  Uint8 g;
  Uint8 b;
  Uint8 a;
  Uint32 *pixel;
  int width;
  int height;
  unsigned int color;

  width = surface->w;
  height = surface->h;

  SDL_LockSurface(surface);

  for (y = 0; y < height; y++) {
    for (x = 0; x < width; x++) {
      pixel = (Uint32 *)surface->pixels + y * surface->pitch / 4 + x;
      SDL_GetRGBA(*pixel, surface->format, &r, &g, &b, &a);
      if (a != 0) {
        color = SDL_MapRGBA(surface->format, r, g, b, alpha);
        *pixel = color;
      }
    }
  }

  SDL_UnlockSurface(surface);
}
