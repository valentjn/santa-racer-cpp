/*      
 *      Santa Racer
 *      globals.hpp
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

#ifndef SANTA_GLOBALS_H
#define SANTA_GLOBALS_H

#include <stdlib.h>
#include <math.h>
#include <map>
#include <string>
#include <vector>
#include <SDL.h>
#include <SDL_image.h>
#include <SDL_mixer.h>

#include "game.hpp"
#include "text.hpp"
#include "output.hpp"
#include "chimney.hpp"

namespace Santa {
    struct highscore_entry {
        std::string name;
        int score;
    };
    
    typedef std::map<std::string, SDL_Surface *> SurfaceMap;
    typedef std::map<std::string, Mix_Chunk *> ChunkMap;
    namespace Config {
        typedef struct highscore_entry Highscore;
    }
    /*typedef int** HighscoreList;*/
    
    //#define DEBUG_MODE
    
    namespace Setup {
        #ifdef DEBUG_MODE
        const bool debug_mode = true;
        #else
        const bool debug_mode = false;
        #endif
        
        extern SDL_Surface *screen;
        extern bool fullscreen;
        
        extern bool verbose;
        
        extern Game *game;
    
        extern SurfaceMap images;
        extern Text *text;
        extern int text_char_widths[96];
        
        extern ChunkMap sounds;
        extern Mix_Music *music;
    
        extern int **std_level_map;
        extern int std_level_width;
        extern int **std_level_objects_map;
        
        extern Chimney **chimneys;
        extern int chimney_count;
        
        const int screen_width = 640;
        const int screen_height = 480;
        const int target_fps = 30;
        const int channel_count = 64;
        
        const int std_level_height = 5;
    }
    
    namespace Config {
        extern Highscore *highscores;
        extern std::string config_dir;
    }
}

#endif
