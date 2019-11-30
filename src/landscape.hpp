/*      
 *      Santa Racer
 *      landscape.hpp
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

#ifndef SANTA_LANDSCAPE_H
#define SANTA_LANDSCAPE_H

#include <SDL.h>

namespace Santa {
    class Landscape {
        public:
            Landscape(void);
            void reset(void);
            
            void draw(void);
            void move(void);
            
            float get_offset(void);
            float get_speed(void);
            
            bool get_pause(void);
            void set_pause(bool pause);
        
        private:
            SDL_Surface *m_surface;
            int m_time;
            float m_offset;
            float m_speed;
            
            bool m_pause;
    };
}

#endif
