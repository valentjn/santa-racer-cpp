/*      
 *      Santa Racer
 *      score.hpp
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

#ifndef SANTA_SCORE_H
#define SANTA_SCORE_H

#include <SDL.h>

namespace Santa {
    class Score {
        public:
            Score(void);
            
            void reset(int total_time_secs);
            void draw(void);
            
            int get_points(void);
            void set_points(int points);
            void add_points(int points);
            
            int get_damage(void);
            void set_damage(int damage);
            void add_damage(int damage);
            
            int get_remaining_secs(void);
            void add_to_remaining_secs(int secs);
            void reset_clock(int total_time_secs);
            
            int get_score(void);
        
        private:
            static const int score_points_per_point = 1;
            static const int score_points_per_damage = -2;
            static const int score_points_per_remaining_sec = 10;
            
            int m_height;
            
            int m_points;
            int m_damage;
            int m_time_start;
            int m_total_time_secs;
            
            SDL_Surface *m_surface_points;
            SDL_Surface *m_surface_damage;
            SDL_Surface *m_surface_time;
    };
}

#endif
