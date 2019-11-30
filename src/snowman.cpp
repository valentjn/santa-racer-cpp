/*      
 *      Santa Racer
 *      snowman.cpp
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
#include "snowman.hpp"
#include "level_object.hpp"
#include "draw.hpp"
#include "random.hpp"

Santa::Snowman::Snowman(void *parent) {
    m_parent = parent;
    m_stars = NULL;
}

Santa::Snowman::~Snowman(void) {
    int i;
    
    if (m_stars != NULL) {
        for (i = 0; i < star_count; i++) {
            delete m_stars[i];
        }
        delete[] m_stars;
    }
}

void Santa::Snowman::reinit(int tile_x, int tile_y) {
    LevelObject *object;
    SDL_Surface *surface;
    int i;
    
    object = (LevelObject *)m_parent;
    surface = Setup::images["snowman"];
    
    m_level_x = (tile_x + 0.5) * Setup::game->level->tile_width -
                (surface->w / frame_count) / 2;
    m_y = (tile_y + 0.5) * Setup::game->level->tile_height -
          surface->h / 2;
    
    object->set_surface(surface);
    object->set_frame_count(frame_count);
    
    m_trigger_offset = Random::rnd(trigger_offset_min, trigger_offset_max);
    
    m_time = SDL_GetTicks();
    m_frame = 0;
    m_triggered = false;
    m_triggered_query = false;
    
    m_stars = new SnowmanStar*[star_count];
    for (i = 0; i < star_count; i++) {
        m_stars[i] = new SnowmanStar(this);
    }
}

void Santa::Snowman::draw(void) {
    LevelObject *object;
    SDL_Surface *surface;
    int frame;
    int width;
    int height;
    
    int level_x;
    int y;
    
    int i;
    
    for (i = 0; i < star_count; i++) {
        m_stars[i]->draw();
    }
    
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

void Santa::Snowman::move(void) {
    int i;
    
    if (Setup::game->sleigh->get_x() + Setup::game->level->get_offset() >=
            m_level_x - m_trigger_offset) {
        
        if (!m_triggered) {
            m_time = SDL_GetTicks();
            m_triggered = true;
            m_triggered_query = true;
        }
    }
    
    for (i = 0; i < star_count; i++) {
        m_stars[i]->move();
    }
}

int Santa::Snowman::get_level_x(void) {
    if (m_triggered) {
        return m_level_x + int((SDL_GetTicks() - m_time) / 1000.0 * speed_x);
    } else {
        return m_level_x;
    }
}

int Santa::Snowman::get_y(void) {
    if (m_triggered) {
        return m_y + int((SDL_GetTicks() - m_time) / 1000.0 * speed_y);
    } else {
        return m_y;
    }
}

int Santa::Snowman::get_frame(void) {
    float time_diff;
    int frame;
    
    if (m_triggered) {
        time_diff = (SDL_GetTicks() - m_time) / 1000.0;
        frame = int(time_diff * frame_speed + m_frame);
        
        if (frame >= frame_count) {
            return frame_count - 1;
        } else {
            return frame;
        }
    } else {
        return 0;
    }
}

bool Santa::Snowman::is_triggered(void) {
    return m_triggered;
}

bool Santa::Snowman::query_triggered(void) {
    if (m_triggered_query) {
        m_triggered_query = false;
        return true;
    } else {
        return false;
    }
}
