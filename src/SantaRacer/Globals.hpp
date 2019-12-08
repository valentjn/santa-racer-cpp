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

#include "SantaRacer/Chimney.hpp"
#include "SantaRacer/Game.hpp"
#include "SantaRacer/Printer.hpp"
#include "SantaRacer/Text.hpp"

namespace SantaRacer {

struct highscore_entry {
  std::string name;
  int score;
};

namespace Config {

typedef struct highscore_entry Highscore;

}  // namespace Config
/*typedef int** HighscoreList;*/

namespace Config {

extern Highscore *highscores;
extern std::string config_dir;

}  // namespace Config
}  // namespace SantaRacer
