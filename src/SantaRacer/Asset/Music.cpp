/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include <SDL/SDL_mixer.h>

#include <filesystem>
#include <string>

#include "SantaRacer/Printer.hpp"
#include "SantaRacer/Asset/Music.hpp"

namespace SantaRacer {
namespace Asset {

Music::Music() : music(nullptr) {
}

Music::Music(Mix_Music* music) : music(music) {
}

Music::Music(std::filesystem::path musicPath) : music(Mix_LoadMUS(musicPath.c_str())) {
  if (music == nullptr) {
    Printer::fatalError("couldn't load music: %s\n", Mix_GetError());
  }
}

Music::Music(Music&& other) : music(other.music) {
  other.music = nullptr;
}

Music::~Music() {
  if (music != nullptr) {
    Mix_FreeMusic(music);
  }
}

Music& Music::operator=(Music&& other) {
  if (&other != this) {
    music = other.music;
    other.music = nullptr;
  }

  return *this;
}

void Music::play() const {
#ifdef NDEBUG
  if ((music != nullptr) && (Mix_PlayMusic(music, -1) == -1)) {
    Printer::fatalError("couldn't play music: %s\n", Mix_GetError());
  }
#endif  // NDEBUG
}

Mix_Music& Music::getMusic() const {
  return *music;
}

}  // namespace Asset
}  // namespace SantaRacer
