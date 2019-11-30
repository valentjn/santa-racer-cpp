/*      
 *      Santa Racer
 *      game.hpp
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

#ifndef SANTA_GAME_H
#define SANTA_GAME_H

#include "landscape.hpp"
#include "snowflake.hpp"
#include "sleigh.hpp"
#include "level.hpp"
#include "gift.hpp"
#include "score.hpp"

namespace Santa {
    class Game {
        public:
            enum GameMode {
                menu_mode,
                help1_mode,
                help2_mode,
                highscore_mode,
                running_game,
                won_mode,
                lost_time_mode,
                lost_damage_mode,
                new_highscore_mode
            };
            
            Game(void);
            ~Game(void);
            void init(void);
            
            void loop(void);
            void process_events(void);
            void check_keys(void);
            void logic(void);
            void draw(void);
            void frame_tick(void);
            void fps_delay(void);
            
            void start_new_game(void);
            void return_to_menu(void);
            
            void draw_text(void);
            void draw_highscores(void);
            
            Landscape *landscape;
            Snowflake **snowflakes;
            Level *level;
            Sleigh *sleigh;
            Gift **gifts;
            Score *score;
            
            GameMode mode;
            int fps;
            
            bool countdown_mode;
            int countdown_start_time;
        
        private:
            static const int highscore_width = 400;
            static const int highscore_height = 300;
            static const int highscore_padding_x = 10;
            static const int highscore_padding_y = 10;
            
            static const int countdown_start = 3;
            
            static const int sleigh_start_x = 50;
            static const int sleigh_start_y = 100;
            
            static const int hit_damage = 20;
            static const int collision_damage = 50;
            static const int gift_ground_damage = 15;
            static const int max_damage = 300;
            
            static const int total_time_secs = 450;
            
            static const int points_balloon_pts = 20;
            static const int cash_balloon_pts = 50;
            
            static const int bonus_duration = 15000;
            
            static const int snowflake_count = 1200;
            static const int max_gift_count = 20;
            
            static const int bell_time_min = 10000;
            static const int bell_time_max = 20000;
            static const float bell_volume = 0.5;
            
            static const int dog_time_min = 10000;
            static const int dog_time_max = 20000;
            static const float dog_volume = 0.5;
            
            static const int gift_wait_duration = 250;
            
            static const int won_splash_duration = 5000;
            static const int lost_splash_duration = 5000;
            
            static const int highscore_caret_blink_duration = 500;
            static const int highscore_name_max_length = 16;
            
            SDL_Surface *m_highscore_bg;
            bool m_initialized;
            
            Uint8 *m_key_state;
            bool m_fire_pressed;
            bool m_up_pressed;
            bool m_down_pressed;
            bool m_left_pressed;
            bool m_right_pressed;
            bool m_escape_pressed;
            
            bool m_quit;
            
            int m_last_fps_update_time;
            int m_frame_counter;
            int m_last_time;
            
            int m_bell_time;
            int m_dog_time;
            
            int m_bonus_time_start;
            
            int m_last_gift_time;
            
            int m_won_lost_time;
            
            int m_highscore_score;
            int m_highscore_place;
            std::string m_highscore_name;
            int m_highscore_caret_blink_time;
    };
}

#endif
