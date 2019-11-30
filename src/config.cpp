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

#include <sys/stat.h>
#include <iostream>
#include <fstream>

#include "globals.hpp"
#include "config.hpp"

namespace Santa {
    namespace Config {
        Highscore *highscores;
        std::string config_dir;
    }
}

char *Santa::Config::get_home_dir(void) {
    return getenv("HOME");
}

void Santa::Config::set_config_dir(const char *dir) {
    Output::debug("setting config directory %s\n", dir);
    config_dir = dir;
    check_mkdir(dir);
}

bool Santa::Config::load_highscores(void) {
    const char *highscores_file;
    std::ifstream f;
    int i;
    
    init_highscores();
    highscores_file = (config_dir + "highscores.txt").c_str();
    
    if (!check_file(highscores_file)) {
        save_highscores();
        
    } else {
        Output::debug("loading highscores\n");
        f.open(highscores_file, std::ios_base::in);
        
        for (i = 0; i < 10; i++) {
            f >> highscores[i].name;
            f >> highscores[i].score;
        }
        
        f.close();
    }
    
    return true;
}

void Santa::Config::save_highscores(void) {
    const char *highscores_file;
    std::ofstream f;
    int i;
    
    Output::debug("saving highscores\n");
    highscores_file = (config_dir + "highscores.txt").c_str();
    f.open(highscores_file, std::ios_base::out);
    
    for (i = 0; i < 10; i++) {
        if (i > 0) {
            f << " ";
        }
        f << highscores[i].name << " " << highscores[i].score;
    }
    
    f.close();
}

void Santa::Config::init_highscores(void) {
    int i;
    
    highscores = new Highscore[10];
    for (i = 0; i < 10; i++) {
        highscores[i].name = "nobody";
        highscores[i].score = 0;
    }
}

void Santa::Config::free_highscores(void) {
    delete[] highscores;
}

void Santa::Config::check_mkdir(const char *dir) {
    if (!check_dir(dir)) {
        Output::debug("creating directory %s\n", dir);
        if (mkdir(dir, 0755) == -1) {
            Output::fatal_error("couldn't create directory %s\n", dir);
        }
    }
}

bool Santa::Config::check_dir(const char *dir) {
    struct stat attributes;
    int result;
    
    result = stat(dir, &attributes);
    if (result == -1) {
        return false;
    } else {
        return bool(attributes.st_mode & S_IFDIR);
    }
}

bool Santa::Config::check_file(const char *file) {
    struct stat attributes;
    int result;
    
    result = stat(file, &attributes);
    if (result == -1) {
        return false;
    } else {
        return bool(attributes.st_mode & S_IFREG);
    }
}
