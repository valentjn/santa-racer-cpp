/*      
 *      Santa Racer
 *      level.cpp
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
#include "level.hpp"
#include "draw.hpp"

Santa::Level::Level(int **map, int **level_object_map,
                    int width, int height) {
    
    int i;
    
    m_surface = Setup::images["level"];
    m_mask = new Mask(m_surface, m_surface->w / tile_width);
    m_width = width;
    m_height = height;
    m_offset = 0.0;
    m_time = SDL_GetTicks();
    m_tiles_to_draw = Setup::screen_width / tile_width + 1;
    m_menu_mode = true;
    m_pause = false;
    
    m_map = map;
    m_level_object_map = level_object_map;
    
    m_level_objects = new LevelObject*[max_level_object_count];
    for (i = 0; i < max_level_object_count; i++) {
        m_level_objects[i] = new LevelObject();
    }
}

Santa::Level::~Level(void) {
    int i;
    
    for (i = 0; i < max_level_object_count; i++) {
        delete m_level_objects[i];
    }
    delete[] m_level_objects;
}

void Santa::Level::draw(void) {
    int start_x;
    int x;
    int y;
    int index;
    
    start_x = int(get_offset()) / tile_width;
    
    for (y = 0; y < m_height; y++) {
        for (x = start_x; x < start_x + m_tiles_to_draw; x++) {
            index = m_map[y][x];
            
            if (index != 0) {
                Draw::blit(m_surface, index * tile_width, 0, tile_width,
                  tile_height, Setup::screen, x * tile_width - m_offset,
                  y * tile_height);
            }
        }
    }
}

void Santa::Level::draw_ballons(void) {
    int i;
    LevelObject *object;
    
    for (i = 0; i < max_level_object_count; i++) {
        object = m_level_objects[i];
        if (object->exists() &&
            (object->get_type() == LevelObject::BalloonObject)) {
            
            object->draw();
        }
    }
}

void Santa::Level::draw_objects(void) {
    int i;
    LevelObject *object;
    
    for (i = 0; i < max_level_object_count; i++) {
        object = m_level_objects[i];
        if (object->exists() &&
            (object->get_type() != LevelObject::BalloonObject)) {
            
            object->draw();
        }
    }
}

void Santa::Level::move(void) {
    m_offset = get_offset();
    m_time = SDL_GetTicks();
}

void Santa::Level::move_objects(void) {
    int start_x;
    int x;
    int y;
    int i;
    int index;
    LevelObject *object;
    
    start_x = int(get_offset()) / tile_width;
    
    for (y = 0; y < m_height; y++) {
        for (x = start_x; x < start_x + m_tiles_to_draw + 1; x++) {
            index = m_level_object_map[y][x];
            
            if (index != 0) {
                move_object(x, y);
            }
        }
    }
    
    for (i = 0; i < max_level_object_count; i++) {
        object = m_level_objects[i];
        
        if (object->exists()) {
            if ((object->get_tile_x() < start_x - 1) ||
                (object->get_y() > (2 * Setup::screen_height))) {
                
                object->reset();
            }
        }
    }
}

void Santa::Level::move_object(int tile_x, int tile_y) {
    int i;
    int index;
    LevelObject *object;
    bool object_moved;
    
    object_moved = false;
    
    for (i = 0; i < max_level_object_count; i++) {
        object = m_level_objects[i];
            /*if ((tile_x == 7) && (tile_y == 2)) {
                Output::debug("move_goblin_object! %i\n", SDL_GetTicks());
                if (object->exists()) {
                    Output::debug("object exists\n");
                } else {
                    Output::debug("!object exists\n");
                }
                if (object->get_tile_x() == tile_x) {
                    Output::debug("object tile_x\n");
                } else {
                    Output::debug("!object tile_x %i, %i\n", object->get_tile_x(), tile_x);
                }
                if (object->get_tile_y() == tile_y) {
                    Output::debug("object tile_y\n");
                } else {
                    Output::debug("!object tile_y %i, %i\n", object->get_tile_y(), tile_y);
                }
            }*/
        
        if (object->exists() && (object->get_tile_x() == tile_x) &&
                                (object->get_tile_y() == tile_y)) {
            
            /*if ((tile_x == 7) && (tile_y == 2)) {
        Output::debug("real_move_goblin_object! %i\n", SDL_GetTicks());
            }*/
            object->move();
            object_moved = true;
        }
    }
    
    if (object_moved) {
        return;
    }
    
    index = m_level_object_map[tile_y][tile_x];
    
    for (i = 0; i < max_level_object_count; i++) {
        object = m_level_objects[i];
        if (!object->exists()) {
            object->reinit(tile_x, tile_y, index);
            return;
        }
    }
}

void Santa::Level::clear_objects(void) {
    int i;
    LevelObject *object;
    
    for (i = 0; i < max_level_object_count; i++) {
        object = m_level_objects[i];
        if (object->exists()) {
            object->reset();
        }
    }
}

float Santa::Level::get_offset(void) {
    if (m_pause) {
        return m_offset;
    }
    
    return m_offset + (SDL_GetTicks() - m_time) / 1000.0 * get_speed();
}

void Santa::Level::set_offset(float offset) {
    m_offset = offset;
    m_time = SDL_GetTicks();
}

float Santa::Level::get_speed(void) {
    if (m_pause) {
        return 0.0;
    }
    
    if (m_menu_mode) {
        return menu_speed;
    } else {
        return Setup::game->sleigh->get_x() /
          float(Setup::screen_width - Setup::game->sleigh->get_width()) *
          (max_speed - min_speed) + min_speed;
    }
}

int Santa::Level::get_tiles_to_draw(void) {
    return m_tiles_to_draw;
}

int Santa::Level::get_tile_width(void) {
    return tile_width;
}

int Santa::Level::get_tile_height(void) {
    return tile_height;
}

int Santa::Level::get_width(void) {
    return m_width;
}

int Santa::Level::get_height(void) {
    return m_height;
}

Santa::Mask *Santa::Level::get_mask(void) {
    return m_mask;
}

int **Santa::Level::get_map(void) {
    return m_map;
}

Santa::LevelObject *Santa::Level::get_level_object(int index) {
    return m_level_objects[index];
}

void Santa::Level::set_menu_mode(bool menu_mode) {
    m_menu_mode = menu_mode;
}

bool Santa::Level::get_pause(void) {
    return m_pause;
}

void Santa::Level::set_pause(bool pause) {
    if ((pause && !m_pause) || (!pause && m_pause)) {
        m_offset = get_offset();
        m_time = SDL_GetTicks();
    }
    
    m_pause = pause;
}
