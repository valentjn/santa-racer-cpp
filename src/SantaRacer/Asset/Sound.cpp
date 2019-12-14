/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include <SDL2/SDL_mixer.h>

#include <filesystem>
#include <string>

#include "SantaRacer/Printer.hpp"
#include "SantaRacer/Asset/Sound.hpp"

namespace SantaRacer {
namespace Asset {

Sound::Sound() : chunk(nullptr) {
}

Sound::Sound(Mix_Chunk* chunk) : chunk(chunk) {
}

Sound::Sound(std::filesystem::path soundPath) : chunk(Mix_LoadWAV(soundPath.c_str())) {
  if (chunk == nullptr) {
    Printer::fatalError("couldn't load sound: %s\n", Mix_GetError());
  }
}

Sound::Sound(Sound&& other) : chunk(other.chunk) {
  other.chunk = nullptr;
}

Sound::~Sound() {
  if (chunk != nullptr) {
    Mix_FreeChunk(chunk);
  }
}

Sound& Sound::operator=(Sound&& other) {
  if (&other != this) {
    chunk = other.chunk;
    other.chunk = nullptr;
  }

  return *this;
}

int Sound::getFreeChannel() {
  int channel = 0;

  while (Mix_Playing(channel) == 1) {
    channel++;
  }

  return channel;
}

void Sound::play() const {
  playPannedWithVolume(0.5, 1.0);
}

void Sound::playPanned(double pan) const {
  playPannedWithVolume(pan, 1.0);
}

void Sound::playWithVolume(double volume) const {
  playPannedWithVolume(0.5, volume);
}

void Sound::playPannedWithVolume(double pan, double volume) const {
  if (chunk != nullptr) {
    int channel = getFreeChannel();
    Uint8 left = ((pan > 0.5) ? static_cast<Uint8>((1 - pan) * 2 * 255) : 255);
    Uint8 right = ((pan < 0.5) ? static_cast<Uint8>(pan * 2 * 255) : 255);

    // Printer::debug("pan %f, left %i, right %i\n", pan, left, right);
    if (Mix_SetPanning(channel, left, right) == 0) {
      Printer::fatalError("couldn't set panning: %s\n", Mix_GetError());
    }

    Mix_Volume(channel, static_cast<int>(volume * MIX_MAX_VOLUME));
    playOnChannel(channel);
  }
}

void Sound::playOnChannel(int channel) const {
#ifdef NDEBUG
  if ((chunk != nullptr) && (Mix_PlayChannel(channel, chunk, 0) == -1)) {
    Printer::fatalError("couldn't play sound: %s\n", Mix_GetError());
  }
#else
  (void)channel;
#endif  // NDEBUG
}

Mix_Chunk& Sound::getChunk() const {
  return *chunk;
}

}  // namespace Asset
}  // namespace SantaRacer
