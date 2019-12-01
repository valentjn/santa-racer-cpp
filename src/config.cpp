/*
 *      Santa Racer
 *      config.cpp
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

#include "config.hpp"

#include <sys/stat.h>

#include <fstream>
#include <iostream>
#include <string>

#include "globals.hpp"

namespace SantaRacer {
namespace Config {

Highscore *highscores;
std::string config_dir;

}  // namespace Config
}  // namespace SantaRacer

char *SantaRacer::Config::get_home_dir(void) { return getenv("HOME"); }

void SantaRacer::Config::set_config_dir(const char *dir) {
  Output::debug("setting config directory %s\n", dir);
  config_dir = dir;
  check_mkdir(dir);
}

bool SantaRacer::Config::load_highscores(void) {
  std::string highscores_file;
  std::ifstream f;
  int i;

  init_highscores();
  highscores_file = config_dir + "highscores.txt";

  if (!check_file(highscores_file.c_str())) {
    save_highscores();

  } else {
    Output::debug("loading highscores\n");
    f.open(highscores_file.c_str(), std::ios_base::in);

    for (i = 0; i < 10; i++) {
      f >> highscores[i].name;
      f >> highscores[i].score;
    }

    f.close();
  }

  return true;
}

void SantaRacer::Config::save_highscores(void) {
  std::string highscores_file;
  std::ofstream f;
  int i;

  Output::debug("saving highscores\n");
  highscores_file = config_dir + "highscores.txt";
  f.open(highscores_file.c_str(), std::ios_base::out);

  for (i = 0; i < 10; i++) {
    if (i > 0) {
      f << " ";
    }
    f << highscores[i].name << " " << highscores[i].score;
  }

  f.close();
}

void SantaRacer::Config::init_highscores(void) {
  int i;

  highscores = new Highscore[10];
  for (i = 0; i < 10; i++) {
    highscores[i].name = "nobody";
    highscores[i].score = 0;
  }
}

void SantaRacer::Config::free_highscores(void) { delete[] highscores; }

void SantaRacer::Config::check_mkdir(const char *dir) {
  if (!check_dir(dir)) {
    Output::debug("creating directory %s\n", dir);
    if (mkdir(dir, 0755) == -1) {
      Output::fatal_error("couldn't create directory %s\n", dir);
    }
  }
}

bool SantaRacer::Config::check_dir(const char *dir) {
  struct stat attributes;
  int result;

  result = stat(dir, &attributes);
  if (result == -1) {
    return false;
  } else {
    return bool(attributes.st_mode & S_IFDIR);
  }
}

bool SantaRacer::Config::check_file(const char *file) {
  struct stat attributes;
  int result;

  result = stat(file, &attributes);
  if (result == -1) {
    return false;
  } else {
    return bool(attributes.st_mode & S_IFREG);
  }
}
