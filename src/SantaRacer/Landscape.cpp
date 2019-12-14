/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include <SDL/SDL.h>

#include <cmath>

#include "SantaRacer/Game.hpp"
#include "SantaRacer/Landscape.hpp"

namespace SantaRacer {

Landscape::Landscape(Game* game) : game(game),
    image(game->getImageLibrary().getAsset("landscape")) {
  initialize();
}

void Landscape::initialize() {
  offset = 0.0;
  time = SDL_GetTicks();
  speed = 5.0;
  paused = false;
}

void Landscape::draw() const {
  const size_t offset = getOffset();

  image.blit({static_cast<int>(offset), 0, image.getWidth() - offset, image.getHeight()},
      &game->getScreenSurface(), {0, 0});
  image.blit({0, 0, offset, image.getHeight()},
      &game->getScreenSurface(), {static_cast<int>(image.getWidth() - offset), 0});
}

void Landscape::move() {
  offset = getOffset();
  time = SDL_GetTicks();
}

double Landscape::getOffset() const {
  return (paused ? offset : std::fmod(offset + (SDL_GetTicks() - time) / 1000.0 * getSpeed(),
      image.getWidth()));
}

double Landscape::getSpeed() const {
  return (paused ? 0.0 : (game->getLevel().getSpeed() / 10.0));
}

bool Landscape::isPaused() const {
  return paused;
}

void Landscape::setPaused(bool paused) {
  if (paused != this->paused) {
    offset = getOffset();
    time = SDL_GetTicks();
  }

  this->paused = paused;
}

}  // namespace SantaRacer
