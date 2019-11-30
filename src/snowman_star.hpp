/*      
 *      Santa Racer
 *      snowman_star.hpp
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

#ifndef SANTA_SNOWMAN_STAR_H
#define SANTA_SNOWMAN_STAR_H

#include <SDL.h>

namespace Santa {
    class Snowman;
}

namespace Santa {
    class SnowmanStar {
        public:
            SnowmanStar(Snowman *snowman);
            void reinit(bool first_init = false);
            void draw(void);
            void move(void);
            int get_frame(void);
            
        private:
            static const int frame_count = 17;
            static const int max_frame_count = 30;
            static const int frame_speed = 2 * frame_count;
            static const int min_x_offset = -5;
            static const int max_x_offset = 5;
            static const int min_y_offset = -5;
            static const int max_y_offset = 5;
            
            static const int snowman_rocket_offset_x = 35;
            static const int snowman_rocket_offset_y = 35;
            
            static const int wait_frame_count_min = 50;
            static const int wait_frame_count_max = 100;
            
            int m_level_x;
            int m_y;
            int m_width;
            int m_height;
            int m_frame;
            int m_max_frame;
            int m_time;
            
            SDL_Surface *m_surface;
            SDL_Surface *m_surface_drunken;
            
            Snowman *m_snowman;
    };
}

#endif