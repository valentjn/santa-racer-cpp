/*      
 *      Santa Racer
 *      angel.cpp
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

#include <SDL.h>

#include "globals.hpp"
#include "angel.hpp"
#include "level_object.hpp"
#include "draw.hpp"

Santa::Angel::Angel(void *parent) {
    m_parent = parent;
}

Santa::Angel::~Angel(void) {
    return;
}

void Santa::Angel::reinit(int tile_x, int tile_y) {
    LevelObject *object;
    SDL_Surface *surface;
    
    object = (LevelObject *)m_parent;
    surface = Setup::images["angel"];
    
    m_level_x = (tile_x + 0.5) * Setup::game->level->tile_width -
                (surface->w / frame_count) / 2;
    m_y = (tile_y + 0.5) * Setup::game->level->tile_height -
          surface->h / 2;
    
    object->set_surface(surface);
    object->set_frame_count(frame_count);
    
    m_time = SDL_GetTicks();
    m_frame = 0;
}

void Santa::Angel::draw(void) {
    LevelObject *object;
    SDL_Surface *surface;
    int frame;
    int width;
    int height;
    
    int level_x;
    int y;
    
    object = (LevelObject *)m_parent;
    surface = object->get_surface();
    width = object->get_width();
    height = object->get_height();
    
    level_x = get_level_x();
    y = get_y();
    frame = get_frame();
    
    Draw::blit(surface, width * frame, 0, width, height,
               Setup::screen, level_x - Setup::game->level->get_offset(), y);
}

void Santa::Angel::move(void) {
    return;
}

int Santa::Angel::get_level_x(void) {
    return m_level_x;
}

int Santa::Angel::get_y(void) {
    return m_y;
}

int Santa::Angel::get_frame(void) {
    float time_diff;
    int frame;
    
    time_diff = (SDL_GetTicks() - m_time) / 1000.0;
    frame = int(time_diff * frame_speed + m_frame) % frame_count;
    
    return frame;
}
