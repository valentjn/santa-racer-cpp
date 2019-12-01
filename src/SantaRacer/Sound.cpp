/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include "SantaRacer/Globals.hpp"
#include "SantaRacer/Sound.hpp"

#include <string>

namespace SantaRacer {

void Sound::play(std::string name) {
  play_panned_volume(name, 0.5, 1.0);
}

void Sound::play_volume(std::string name, float volume) {
  play_panned_volume(name, 0.5, volume);
}

void Sound::play_channel(std::string name, int channel) {
  if (!Setup::debug_mode) {
    if (Mix_PlayChannel(channel, Setup::sounds[name], 0) == -1) {
      Output::fatal_error("couldn't play sound: %s\n", Mix_GetError());
    }
  }
}

void Sound::play_panned_volume(std::string name, float pan,
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

  // Output::debug("pan %f, left %i, right %i\n", pan, left, right);
  if (Mix_SetPanning(channel, left, right) == 0) {
    Output::fatal_error("couldn't set panning: %s\n", Mix_GetError());
  }

  Mix_Volume(channel, (int)(volume * MIX_MAX_VOLUME));

  play_channel(name, channel);
}

void Sound::play_panned_x(std::string name, int x) {
  float pan;

  pan = (float)x / Setup::screen_width;
  if (pan < 0) {
    pan = 0;
  } else if (pan > 1) {
    pan = 1;
  }

  play_panned_volume(name, pan, 1.0);
}

void Sound::play_music(void) {
  if (!Setup::debug_mode) {
    if (Mix_PlayMusic(Setup::music, -1) == -1) {
      Output::fatal_error("couldn't play music: %s\n", Mix_GetError());
    }
  }
}

int Sound::get_channel(void) {
  int channel;

  channel = 0;
  while (Mix_Playing(channel) == 1) {
    channel++;
  }

  return channel;
}

}  // namespace SantaRacer
