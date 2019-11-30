/*      
 *      Santa Racer
 *      gift.cpp
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
#include "gift.hpp"
#include "draw.hpp"
#include "random.hpp"

Santa::Gift::Gift(void) {
    int i;
    
    m_surfaces[0] = Setup::images["gift1"];
    m_surfaces[1] = Setup::images["gift2"];
    m_surfaces[2] = Setup::images["gift3"];
    
    for (i = 0; i < 3; i++) {
        m_widths[i] = m_surfaces[i]->w / frame_count;
        m_heights[i] = m_surfaces[i]->h;
    }
    
    m_big_star_surface = Setup::images["big_star"];
    m_big_star_width = m_big_star_surface->w / big_star_frame_count;
    m_big_star_height = m_big_star_surface->h;
    
    m_points_surfaces[0] = Setup::images["10"];
    m_points_surfaces[1] = Setup::images["15"];
    m_points_surfaces[2] = Setup::images["20"];
    
    reset();
}

void Santa::Gift::reinit(void) {
    m_exists = true;
    
    m_level_x = Setup::game->sleigh->get_x() +
                Setup::game->level->get_offset();
    
    m_y = Setup::game->sleigh->get_y() + Setup::game->sleigh->get_height();
    m_speed_x = Setup::game->level->get_speed();
    m_type = Random::rnd(0, 2);
    m_frame = Random::rnd(0, frame_count - 1);
    m_time = SDL_GetTicks();
    m_hit_ground = false;
    m_hit_chimney = false;
    m_points = 0;
    m_success = false;
    m_big_star_time = 0;
    m_double_points = false;
}

void Santa::Gift::reset(void) {
    m_exists = false;
    m_level_x = 0;
    m_y = 0;
    m_speed_x = 0;
    m_type = 0;
    m_frame = 0;
    m_time = 0;
    m_hit_ground = false;
    m_hit_chimney = false;
    m_points = 0;
    m_success = false;
    m_big_star_time = 0;
    m_double_points = false;
}

void Santa::Gift::draw(void) {
    int x;
    int y;
    
    if (!m_exists) {
        return;
    }
    
    if (m_success) {
        x = get_level_x() - Setup::game->level->get_offset() -
            m_big_star_width / 2;
        y = get_y() - m_big_star_height / 2;
        
        if (m_double_points) {
            draw_big_star(x, y);
            draw_big_star(x + double_points_x_offset,
                          y + double_points_x_offset);
            draw_points(x, y);
            draw_points(x + double_points_x_offset,
                        y + double_points_y_offset);
        } else {
            draw_big_star(x, y);
            draw_points(x, y);
        }
        
        return;
    }
    
    Draw::blit(m_surfaces[m_type], m_widths[m_type] * get_frame(),
      0, m_widths[m_type], m_heights[m_type], Setup::screen,
      get_level_x() - Setup::game->level->get_offset(), get_y());
}

void Santa::Gift::draw_big_star(int x, int y) {
    int big_star_frame;
    
    big_star_frame = get_big_star_frame();
    if (big_star_frame >= big_star_vframe_count) {
        big_star_frame = big_star_vframe_count - 1;
    }
    
    if (big_star_frame < 10) {
        Draw::blit(m_big_star_surface,
          m_big_star_width * big_star_frame,
          0, m_big_star_width, m_big_star_height, Setup::screen,
          x + big_star1_x_offset, y + big_star1_y_offset);
    }
    
    if ((big_star_frame >= 2) && (big_star_frame < 12)) {
        Draw::blit(m_big_star_surface,
          m_big_star_width * (big_star_frame - 2),
          0, m_big_star_width, m_big_star_height, Setup::screen,
          x + big_star2_x_offset, y + big_star2_y_offset);
    }
    
    if (big_star_frame >= 4) {
        Draw::blit(m_big_star_surface,
          m_big_star_width * (big_star_frame - 4),
          0, m_big_star_width, m_big_star_height, Setup::screen,
          x + big_star3_x_offset, y + big_star3_y_offset);
    }
}

void Santa::Gift::draw_points(int x, int y) {
    int points_surface_index;
    
    if (m_points == gift_points_easy) {
        points_surface_index = 0;
    } else if (m_points == gift_points_medium) {
        points_surface_index = 1;
    } else if (m_points == gift_points_hard) {
        points_surface_index = 2;
    }
    
    Draw::copy(m_points_surfaces[points_surface_index], Setup::screen,
      x + points_x_offset + m_big_star_width / 2,
      y + points_y_offset + m_big_star_height / 2);
}

void Santa::Gift::move(void) {
    int level_x;
    int y;
    
    int tile_x;
    int tile_y;
    int start_x;
    int tiles_to_draw;
    int height;
    int tile_width;
    int tile_height;
    
    int chimney_x;
    int chimney_y;
    
    int chimney_int_x;
    int chimney_int_y;
    int chimney_int_width;
    int chimney_int_height;
    int points;
    
    int **level_map;
    int map_index;
    
    Chimney **chimneys;
    int chimney_count;
    
    int i;
    
    if (!m_exists) {
        return;
    }
    
    if (m_success) {
        if (get_big_star_frame() >= big_star_vframe_count) {
            reset();
        }
        
        return;
    }
    
    level_x = get_level_x();
    y = get_y();
    
    if (y >= Setup::screen_height) {
        hit_ground();
        return;
    }
    
    start_x = int(Setup::game->level->get_offset()) /
              Setup::game->level->tile_width;
    tiles_to_draw = Setup::game->level->get_tiles_to_draw();
    height = Setup::game->level->get_height();
    level_map = Setup::game->level->get_map();
    tile_width = Setup::game->level->get_tile_width();
    tile_height = Setup::game->level->get_tile_width();
    
    chimneys = Setup::chimneys;
    chimney_count = Setup::chimney_count;
    chimney_int_height = Chimney::chimney_height;
    
    for (tile_y = 0; tile_y < height; tile_y++) {
        for (tile_x = start_x; tile_x < start_x + tiles_to_draw;
             tile_x++) {
            
            map_index = level_map[tile_y][tile_x];
            if (map_index == 0) {
                continue;
            }
            
            chimney_x = tile_x * tile_width;
            chimney_y = tile_y * tile_height;
            
            for (i = 0; i < chimney_count; i++) {
                if (chimneys[i]->get_map_index() != map_index) {
                    continue;
                }
                
                chimney_int_x = chimneys[i]->get_x();
                chimney_int_y = chimneys[i]->get_y();
                chimney_int_width = chimneys[i]->get_width();
                
                if ((level_x >= chimney_x + chimney_int_x) &&
                  (y + m_heights[m_type] / 2 >= chimney_y + chimney_int_y) &&
                  (level_x <= chimney_x + chimney_int_x + chimney_int_width) &&
                  (y <= chimney_y + chimney_int_y + chimney_int_height)) {
                    
                    if (tile_y == 1) {
                        points = gift_points_easy;
                    } else if (tile_y == 2) {
                        points = gift_points_medium;
                    } else if (tile_y == 3) {
                        points = gift_points_hard;
                    }
                    
                    hit_chimney(points);
                    return;
                }
            }
        }
    }
}

void Santa::Gift::hit_ground(void) {
    m_hit_ground = true;
}

void Santa::Gift::hit_chimney(int points) {
    m_points = points;
    m_big_star_time = SDL_GetTicks();
    
    m_level_x = get_level_x();
    m_y = get_y();
    
    m_success = true;
    m_hit_chimney = true;
}

void Santa::Gift::double_points(void) {
    m_double_points = true;
}

int Santa::Gift::get_level_x(void) {
    if (m_success) {
        return m_level_x;
    }
    
    return m_level_x + int((SDL_GetTicks() - m_time) / 1000.0 * m_speed_x);
}

int Santa::Gift::get_y(void) {
    float time_diff;
    
    if (m_success) {
        return m_y;
    }
    
    time_diff = (SDL_GetTicks() - m_time) / 1000.0;
    
    return m_y + speed_y_start * time_diff +
           0.5 * gravity_acceleration * time_diff * time_diff;
}

int Santa::Gift::get_frame(void) {
    return int((SDL_GetTicks() - m_time) / 1000.0 * frame_speed + m_frame) %
           frame_count;
}

int Santa::Gift::get_big_star_frame(void) {
    return int((SDL_GetTicks() - m_big_star_time) / 1000.0 *
           big_star_vframe_speed);
}

bool Santa::Gift::exists(void) {
    return m_exists;
}

bool Santa::Gift::query_hit_ground(void) {
    if (m_hit_ground) {
        reset();
        return true;
    } else {
        return false;
    }
}

bool Santa::Gift::query_hit_chimney(void) {
    bool hit_chimney;
    
    hit_chimney = m_hit_chimney;
    m_hit_chimney = false;
    
    return hit_chimney;
}

int Santa::Gift::get_points(void) {
    return m_points;
}
