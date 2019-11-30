/*      
 *      Santa Racer
 *      balloon.hpp
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

#ifndef SANTA_BALLOON_H
#define SANTA_BALLOON_H

namespace Santa {
    class Balloon {
        public:
            enum BalloonType {
                CashBalloon,
                PointsBalloon,
                ChampagneBalloon,
                GiftBalloon,
                ShieldBalloon
            };
            
            Balloon(void *parent);
            
            void reinit(int tile_x, int tile_y, int gfx_index);
            void draw(void);
            void move(void);
            
            int get_level_x(void);
            int get_y(void);
            int get_frame(void);
            BalloonType get_type(void);
        
        private:
            static const int balloon_frame_count = 8;
            static const int balloon_frame_speed = balloon_frame_count;
            static const int cash_frame_count = 7;
            static const int cash_frame_speed = cash_frame_count;
            static const int speed = 50;
            
            void *m_parent;
            BalloonType m_ballon_type;
            int m_time;
            int m_frame_speed;
            
            int m_level_x;
            int m_y;
            int m_frame;
    };
}

#endif

