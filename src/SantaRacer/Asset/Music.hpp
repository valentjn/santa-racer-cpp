/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

#include <SDL2/SDL_mixer.h>

#include <filesystem>
#include <string>

namespace SantaRacer {
namespace Asset {

class Music {
 public:
  Music();
  explicit Music(Mix_Music* music);
  explicit Music(std::filesystem::path musicPath);
  Music(const Music& other) = delete;
  Music(Music&& other);
  ~Music();

  Music& operator=(const Music& other) = delete;
  Music& operator=(Music&& other);

  void play() const;

  Mix_Music& getMusic() const;

 protected:
  Mix_Music* music;
};

}  // namespace Asset
}  // namespace SantaRacer
