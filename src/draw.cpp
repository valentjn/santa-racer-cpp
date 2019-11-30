/*      
 *      Santa Racer
 *      draw.cpp
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

#include "globals.hpp"
#include "draw.hpp"

void Santa::Draw::blit(SDL_Surface *src_surface, int src_x, int src_y,
  int src_w, int src_h, SDL_Surface *dst_surface, int dst_x, int dst_y) {
    
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

void Santa::Draw::copy(SDL_Surface *src_surface, SDL_Surface *dst_surface,
                       int dst_x, int dst_y) {
    
    SDL_Rect dst_rect;
    
    dst_rect.x = dst_x;
    dst_rect.y = dst_y;
    SDL_BlitSurface(src_surface, NULL, dst_surface, &dst_rect);
}

void Santa::Draw::set_alpha(SDL_Surface *surface, Uint8 alpha) {
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
