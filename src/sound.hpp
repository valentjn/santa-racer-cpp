/*
 *      Santa Racer
 *      sound.hpp
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

#ifndef SANTA_SOUND_H
#define SANTA_SOUND_H

namespace Santa {
namespace Sound {

void play(std::string name);
void play_volume(std::string name, float volume);
void play_channel(std::string name, int channel);
void play_panned_volume(std::string name, float pan, float volume);
void play_panned_x(std::string name, int x);
void play_music(void);

int get_channel(void);

}  // namespace Sound
}  // namespace Santa

#endif
