/*      
 *      Santa Racer
 *      sleigh_star.hpp
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

#ifndef SANTA_SLEIGH_STAR_H
#define SANTA_SLEIGH_STAR_H

#include <SDL.h>

namespace Santa {
    class SleighStar {
        public:
            SleighStar(void);
            void reinit(bool first_init = false);
            void draw(void);
            void move(void);
            int get_frame(void);
        
        private:
            int m_level_x;
            int m_y;
            int m_width;
            int m_height;
            int m_frame;
            int m_max_frame;
            int m_time;
            
            SDL_Surface *m_surface;
            SDL_Surface *m_surface_drunken;

            static const int frame_count = 17;
            static const int max_frame_count = 30;
            static const int frame_speed = 2 * frame_count;
            static const int min_x_offset = -10;
            static const int max_x_offset = 140;
            static const int min_y_offset = 0;
            static const int max_y_offset = 10;
    };
}

#endif
