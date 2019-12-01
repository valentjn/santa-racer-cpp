/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#ifndef SANTA_SOUND_H
#define SANTA_SOUND_H

namespace SantaRacer {
namespace Sound {

void play(std::string name);
void play_volume(std::string name, float volume);
void play_channel(std::string name, int channel);
void play_panned_volume(std::string name, float pan, float volume);
void play_panned_x(std::string name, int x);
void play_music(void);

int get_channel(void);

}  // namespace Sound
}  // namespace SantaRacer

#endif
