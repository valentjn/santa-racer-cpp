/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

#include <filesystem>
#include <string>

#include <SDL/SDL_mixer.h>

namespace SantaRacer {
namespace Asset {

class Sound {
 public:
  explicit Sound(std::filesystem::path soundPath);
  Sound(const Sound& other) = delete;
  Sound(Sound&& other);
  ~Sound();

  Sound& operator=(const Sound& other) = delete;
  Sound& operator=(Sound&& other);

  static int getFreeChannel();

  void play() const;
  void playPanned(double pan) const;
  void playWithVolume(double volume) const;
  void playPannedWithVolume(double pan, double volume) const;
  void playOnChannel(int channel) const;

  Mix_Chunk& getChunk() const;

protected:
  Mix_Chunk* chunk;
};

}  // namespace Asset
}  // namespace SantaRacer
