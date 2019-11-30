/*      
 *      Santa Racer
 *      snowflake.cpp
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
#include "snowflake.hpp"
#include "random.hpp"

Santa::Snowflake::Snowflake(void) {
    reinit(true);
}

void Santa::Snowflake::reinit(bool first_init) {
    m_level_x = Random::rnd(left_margin, 2 * Setup::screen_width) +
                Setup::game->level->get_offset();
    m_z = Random::rnd(0, 255);
    m_color = SDL_MapRGB(Setup::screen->format,
                         255 - m_z, 255 - m_z, 255 - m_z);
    m_time = SDL_GetTicks();
    m_speed_x = Random::rnd(min_speed_x, max_speed_x);
    m_speed_y = Random::rnd(min_speed_y, max_speed_y);
    m_speed_change_time = SDL_GetTicks() + Random::rnd(min_speed_change_time,
                                                       max_speed_change_time);
    
    if (first_init) {
        m_y = Random::rnd(0, Setup::screen_height);
    } else {
        m_y = 0.0;
    }
}

void Santa::Snowflake::draw(void) {
    int x;
    int y;
    Uint32 *bufp;
    
    x = get_level_x() - Setup::game->level->get_offset();
    y = get_y();
    
    if (x < 0 || x >= Setup::screen_width ||
        y < 0 || y >= Setup::screen_height) {
        
        return;
    }
    
    bufp = (Uint32 *)Setup::screen->pixels + y * Setup::screen->pitch / 4 +
            x / 2;
    // FIXME ??
    *bufp = m_color;
}

void Santa::Snowflake::move(void) {
    int level_x;
    int y;
    
    level_x = get_level_x();
    y = get_y();
    
    if (y >= Setup::screen_height ||
        level_x - Setup::game->level->get_offset() < left_margin) {
        reinit();
    } else if (SDL_GetTicks() > m_speed_change_time) {
        m_level_x = level_x;
        m_y = y;
        m_time = SDL_GetTicks();
        change_speed();
    }
}

void Santa::Snowflake::change_speed(void) {
    m_speed_x += Random::rnd(-10, 10);
    if (m_speed_x < min_speed_x) {
        m_speed_x = min_speed_x;
    } else if (m_speed_x > max_speed_x) {
        m_speed_x = max_speed_x;
    }
    
    m_speed_y += Random::rnd(-10, 10);
    if (m_speed_y < min_speed_y) {
        m_speed_y = min_speed_y;
    } else if (m_speed_y > max_speed_y) {
        m_speed_y = max_speed_y;
    }
    
    m_speed_change_time = SDL_GetTicks() + Random::rnd(min_speed_change_time,
                                                       max_speed_change_time);
}

float Santa::Snowflake::get_level_x(void) {
    return m_level_x + m_speed_x * ((SDL_GetTicks() - m_time) / 1000.0);
}

float Santa::Snowflake::get_y(void) {
    return m_y + m_speed_y * (SDL_GetTicks() - m_time) / 1000.0;
}