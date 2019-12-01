/*
 *      Santa Racer
 *      setup.hpp
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

#ifndef SANTA_SETUP_H
#define SANTA_SETUP_H

namespace SantaRacer {
namespace Setup {

void santa_setup(void);
bool load_images(void);
bool load_text(void);
bool load_level(void);
bool load_level_objects(void);
bool load_chimneys(void);
bool load_sounds(void);
bool load_music(void);
void santa_cleanup(void);

}  // namespace Setup
}  // namespace SantaRacer

#endif
