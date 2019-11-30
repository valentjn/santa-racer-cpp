/*      
 *      Santa Racer
 *      landscape.cpp
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

#include <math.h>

#include "globals.hpp"
#include "landscape.hpp"
#include "draw.hpp"

Santa::Landscape::Landscape(void) {
    m_surface = Setup::images["landscape"];
    reset();
}

void Santa::Landscape::reset(void) {
    m_offset = 0.0;
    m_time = SDL_GetTicks();
    m_speed = 5.0;
    m_pause = false;
}

void Santa::Landscape::draw(void) {
    int offset;
    
    offset = get_offset();
    
    Draw::blit(m_surface, offset, 0, m_surface->w - offset,
               m_surface->h, Setup::screen, 0, 0);
    Draw::blit(m_surface, 0, 0, offset, m_surface->h,
               Setup::screen, m_surface->w - offset, 0);
}

void Santa::Landscape::move(void) {
    m_offset = get_offset();
    m_time = SDL_GetTicks();
}

float Santa::Landscape::get_offset(void) {
    if (m_pause) {
        return m_offset;
    }
    
    return fmod(m_offset + (SDL_GetTicks() - m_time) / 1000.0 *
                            get_speed(), m_surface->w);
}

float Santa::Landscape::get_speed(void) {
    if (m_pause) {
        return 0.0;
    }
    
    return Setup::game->level->get_speed() / 10.0;
}

bool Santa::Landscape::get_pause(void) {
    return m_pause;
}

void Santa::Landscape::set_pause(bool pause) {
    if ((pause && !m_pause) || (!pause && m_pause)) {
        m_offset = get_offset();
        m_time = SDL_GetTicks();
    }
    
    m_pause = pause;
}
