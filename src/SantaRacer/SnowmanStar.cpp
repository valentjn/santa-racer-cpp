/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include <SDL/SDL.h>

#include "SantaRacer/Game.hpp"
#include "SantaRacer/RNG.hpp"
#include "SantaRacer/SnowmanStar.hpp"
#include "SantaRacer/LevelObject/Snowman.hpp"

namespace SantaRacer {

SnowmanStar::SnowmanStar(Game* game, LevelObject::Snowman *snowman) :
    game(game), snowman(snowman), image(game->getImageLibrary().getAsset("star")) {
  initialize();
}

void SnowmanStar::initialize(bool useRandomFrame) {
  levelX = snowman->getLevelX() + snowmanRocketOffsetX -
      game->getRNG().getInteger(minXOffset, maxXOffset);
  y = snowman->getY() + snowmanRocketOffsetY - game->getRNG().getInteger(minYOffset, maxYOffset);
  time = SDL_GetTicks();
  frame = (useRandomFrame ? (-game->getRNG().getInteger(minNumberOfFramesToWait,
      maxNumberOfFramesToWait)) : 0);
}

void SnowmanStar::draw() const {
  const int frame = getFrame();

  if ((frame >= 0) && (frame < static_cast<int>(image.getNumberOfFrames()))) {
    image.copy(&game->getScreenSurface(),
        {static_cast<int>(levelX - game->getLevel().getOffset()), y}, frame);
  }
}

void SnowmanStar::move() {
  if (!snowman->isTriggered()) {
    time = SDL_GetTicks();
  } else if (getFrame() >= static_cast<int>(image.getNumberOfFrames())) {
    initialize(false);
  }
}

int SnowmanStar::getFrame() const {
  return static_cast<int>((SDL_GetTicks() - time) / 1000.0 * frameSpeed + frame);
}

}  // namespace SantaRacer
