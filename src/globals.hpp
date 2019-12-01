/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

#include <SDL/SDL.h>
#include <SDL/SDL_image.h>
#include <SDL/SDL_mixer.h>
#include <math.h>
#include <stdlib.h>

#include <map>
#include <string>
#include <vector>

#include "chimney.hpp"
#include "game.hpp"
#include "output.hpp"
#include "text.hpp"

namespace SantaRacer {

struct highscore_entry {
  std::string name;
  int score;
};

typedef std::map<std::string, SDL_Surface *> SurfaceMap;
typedef std::map<std::string, Mix_Chunk *> ChunkMap;

namespace Config {

typedef struct highscore_entry Highscore;

}  // namespace Config
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

}  // namespace Setup

namespace Config {

extern Highscore *highscores;
extern std::string config_dir;

}  // namespace Config
}  // namespace SantaRacer
