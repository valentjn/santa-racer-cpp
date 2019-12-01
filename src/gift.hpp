/*      
 *      Santa Racer
 *      gift.hpp
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

#ifndef SANTA_GIFT_H
#define SANTA_GIFT_H

#include <SDL/SDL.h>

namespace Santa {
    class Gift {
        public:
            Gift(void);
            
            void reinit(void);
            void reset(void);
            void draw(void);
            void draw_big_star(int x, int y);
            void draw_points(int x, int y);
            void move(void);
            void hit_ground(void);
            void hit_chimney(int points);
            void double_points(void);
            
            int get_level_x(void);
            int get_y(void);
            int get_frame(void);
            int get_big_star_frame(void);
            bool exists(void);
            
            bool query_hit_ground(void);
            bool query_hit_chimney(void);
            int get_points(void);
        
        private:
            static const int frame_count = 15;
            static const int frame_speed = frame_count;
            
            static const int gravity_acceleration = 200;
            static const int speed_y_start = 50;
            
            static const int big_star_frame_count = 10;
            static const int big_star_vframe_count = 14;
            static const int big_star_vframe_speed = frame_count;
            
            static const int big_star1_x_offset = 10;
            static const int big_star1_y_offset = 10;
            static const int big_star2_x_offset = 25;
            static const int big_star2_y_offset = 15;
            static const int big_star3_x_offset = 15;
            static const int big_star3_y_offset = 25;
            static const int points_x_offset = 10;
            static const int points_y_offset = 10;
            static const int double_points_x_offset = 10;
            static const int double_points_y_offset = 10;
            
            static const int gift_points_easy = 10;
            static const int gift_points_medium = 15;
            static const int gift_points_hard = 20;
            
            SDL_Surface *m_surfaces[3];
            int m_widths[3];
            int m_heights[3];
            
            SDL_Surface *m_big_star_surface;
            int m_big_star_width;
            int m_big_star_height;
            
            SDL_Surface *m_points_surfaces[3];
            
            bool m_exists;
            int m_level_x;
            int m_y;
            int m_speed_x;
            int m_type;
            int m_frame;
            int m_time;
            
            bool m_hit_ground;
            bool m_hit_chimney;
            bool m_success;
            int m_points;
            bool m_double_points;
            
            int m_big_star_time;
    };
}

#endif
