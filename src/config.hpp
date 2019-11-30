/*      
 *      Santa Racer
 *      config.hpp
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

#ifndef SANTA_CONFIG_H
#define SANTA_CONFIG_H

namespace Santa {
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
    }
}

#endif
