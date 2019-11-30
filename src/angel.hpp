/*      
 *      Santa Racer
 *      angel.hpp
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

#ifndef SANTA_ANGEL_H
#define SANTA_ANGEL_H

namespace Santa {
    class Angel {
        public:
            Angel(void *parent);
            ~Angel(void);
            
            void reinit(int tile_x, int tile_y);
            void draw(void);
            void move(void);
            
            int get_level_x(void);
            int get_y(void);
            int get_frame(void);
            
        private:
            static const int frame_count = 13;
            static const int frame_speed = frame_count;
            
            void *m_parent;
            
            int m_level_x;
            int m_y;
            int m_frame;
            int m_time;
    };
}

#endif
