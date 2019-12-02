/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include <sys/stat.h>

#include <fstream>
#include <iostream>
#include <string>

#include "SantaRacer/Config.hpp"
#include "SantaRacer/Globals.hpp"

namespace SantaRacer {
namespace Config {

Highscore *highscores;
std::string config_dir;

char *get_home_dir(void) { return getenv("HOME"); }

void set_config_dir(const char *dir) {
  Output::debug("setting config directory %s\n", dir);
  config_dir = dir;
  check_mkdir(dir);
}

bool load_highscores(void) {
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

void save_highscores(void) {
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

void init_highscores(void) {
  int i;

  highscores = new Highscore[10];
  for (i = 0; i < 10; i++) {
    highscores[i].name = "nobody";
    highscores[i].score = 0;
  }
}

void free_highscores(void) { delete[] highscores; }

void check_mkdir(const char *dir) {
  if (!check_dir(dir)) {
    Output::debug("creating directory %s\n", dir);
    if (mkdir(dir, 0755) == -1) {
      Output::fatal_error("couldn't create directory %s\n", dir);
    }
  }
}

bool check_dir(const char *dir) {
  struct stat attributes;
  int result;

  result = stat(dir, &attributes);
  if (result == -1) {
    return false;
  } else {
    return static_cast<bool>(attributes.st_mode & S_IFDIR);
  }
}

bool check_file(const char *file) {
  struct stat attributes;
  int result;

  result = stat(file, &attributes);
  if (result == -1) {
    return false;
  } else {
    return static_cast<bool>(attributes.st_mode & S_IFREG);
  }
}

}  // namespace Config
}  // namespace SantaRacer
