/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#ifndef SANTA_CONFIG_H
#define SANTA_CONFIG_H

namespace SantaRacer {
namespace Config {

char *get_home_dir(void);
void set_config_dir(const char *dir);
bool load_highscores(void);
void save_highscores(void);
void init_highscores(void);
void free_highscores(void);
void check_mkdir(const char *dir);
bool check_dir(const char *dir);
bool check_file(const char *file);

}  // namespace Config
}  // namespace SantaRacer

#endif
