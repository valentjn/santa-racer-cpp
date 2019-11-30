/*      
 *      Santa Racer
 *      sound.cpp
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

#include "globals.hpp"
#include "sound.hpp"

void Santa::Sound::play(std::string name) {
    play_panned_volume(name, 0.5, 1.0);
}

void Santa::Sound::play_volume(std::string name, float volume) {
    play_panned_volume(name, 0.5, volume);
}

void Santa::Sound::play_channel(std::string name, int channel) {
    if (!Setup::debug_mode) {
        if (Mix_PlayChannel(channel, Setup::sounds[name], 0) == -1) {
            Output::fatal_error("couldn't play sound: %s\n", Mix_GetError());
        }
    }
}

void Santa::Sound::play_panned_volume(std::string name, float pan,
                                      float volume) {
    
    int channel;
    int left;
    int right;
    
    channel = get_channel();
    left = (1 - pan) * 2 * 255;
    right = pan * 2 * 255;
    
    if (left > 255) {
        left = 255;
    }
    if (right > 255) {
        right = 255;
    }
    
    //Output::debug("pan %f, left %i, right %i\n", pan, left, right);
    if (Mix_SetPanning(channel, left, right) == 0) {
        Output::fatal_error("couldn't set panning: %s\n", Mix_GetError());
    }
    
    Mix_Volume(channel, (int)(volume * MIX_MAX_VOLUME));
    
    play_channel(name, channel);
}

void Santa::Sound::play_panned_x(std::string name, int x) {
    float pan;
    
    pan = (float)x / Setup::screen_width;
    if (pan < 0) {
        pan = 0;
    } else if (pan > 1) {
        pan = 1;
    }
    
    play_panned_volume(name, pan, 1.0);
}

void Santa::Sound::play_music(void) {
    if (!Setup::debug_mode) {
        if (Mix_PlayMusic(Setup::music, -1) == -1) {
            Output::fatal_error("couldn't play music: %s\n", Mix_GetError());
        }
    }
}

int Santa::Sound::get_channel(void) {
    int channel;
    
    channel = 0;
    while (Mix_Playing(channel) == 1) {
        channel++;
    }
    
    return channel;
}
