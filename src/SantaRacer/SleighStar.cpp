/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include "SantaRacer/Game.hpp"
#include "SantaRacer/RNG.hpp"
#include "SantaRacer/SleighStar.hpp"

namespace SantaRacer {

SleighStar::SleighStar(Game* game) : game(game),
    imageNormal(game->getImageLibrary().getAsset("star")),
    imageDrunk(game->getImageLibrary().getAsset("star_drunk")) {
  initialize();
}

void SleighStar::initialize(bool useRandomFrame) {
  levelX = game->getLevel().getOffset() + game->getSleigh().getX() +
      game->getSleigh().getWidth() - game->getRNG().getInteger(minXOffset, maxXOffset);
  y = game->getSleigh().getY() + game->getSleigh().getHeight() -
      game->getRNG().getInteger(minYOffset, maxYOffset);
  time = SDL_GetTicks();
  frame = (useRandomFrame ? game->getRNG().getInteger(0, imageNormal.getNumberOfFrames() - 1) : 0);
  maxFrame = game->getRNG().getInteger(imageNormal.getNumberOfFrames(), maxNumberOfFrames);
}

void SleighStar::draw() const {
  const Asset::Image& image = (game->getSleigh().isDrunk() ? imageDrunk : imageNormal);
  const size_t frame = getFrame();

  if (frame < image.getNumberOfFrames()) {
    image.copy(&game->getScreenSurface(),
        {levelX - static_cast<int>(game->getLevel().getOffset()), y}, frame);
  }
}

void SleighStar::move() {
  if (getFrame() >= maxFrame) {
    initialize(false);
  }
}

size_t SleighStar::getFrame() const {
  return static_cast<int>((SDL_GetTicks() - time) / 1000.0 * frameSpeed + frame);
}

}  // namespace SantaRacer
