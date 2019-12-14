/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include <SDL2/SDL.h>

#include <algorithm>
#include <vector>

#include "SantaRacer/Game.hpp"
#include "SantaRacer/RNG.hpp"
#include "SantaRacer/LevelObject/LevelObject.hpp"
#include "SantaRacer/LevelObject/Snowman.hpp"

namespace SantaRacer {
namespace LevelObject {

Snowman::Snowman(Game* game, size_t tileX, size_t tileY) :
    LevelObject(game, tileX, tileY, &game->getImageLibrary().getAsset("snowman")),
    levelX((tileX + 0.5) * game->getLevel().getTileWidth() -
      (image->getWidth() / image->getNumberOfFrames()) / 2),
    y((tileY + 0.5) * game->getLevel().getTileHeight() - image->getHeight() / 2),
    frame(0), time(SDL_GetTicks()),
    triggerOffset(game->getRNG().getInteger(minTriggerOffset, maxTriggerOffset)),
    triggered(false), triggeredCheck(false) {
  for (size_t i = 0; i < numberOfSnowmanStars; i++) {
    snowmanStars.emplace_back(game, this);
  }
}

Snowman::~Snowman() {
}

void Snowman::draw() {
  for (SnowmanStar& snowmanStar : snowmanStars) {
    snowmanStar.draw();
  }

  LevelObject::draw();
}

void Snowman::move() {
  if ((game->getSleigh().getX() + game->getLevel().getOffset() >= levelX - triggerOffset) &&
      !triggered) {
    time = SDL_GetTicks();
    triggered = true;
    triggeredCheck = true;
  }

  for (SnowmanStar& snowmanStar : snowmanStars) {
    snowmanStar.move();
  }
}

int Snowman::getLevelX() const {
  return (triggered ? (levelX + static_cast<int>((SDL_GetTicks() - time) / 1000.0 * speedX)) :
      levelX);
}

int Snowman::getY() const {
  return (triggered ? (y + static_cast<int>((SDL_GetTicks() - time) / 1000.0 * speedY)) : y);
}

size_t Snowman::getFrame() const {
  return (triggered ?
      std::min(static_cast<size_t>((SDL_GetTicks() - time) / 1000.0 * frameSpeed + frame),
      image->getNumberOfFrames() - 1) : 0);
}

bool Snowman::isTriggered() {
  return triggered;
}

bool Snowman::checkTriggered() {
  if (triggeredCheck) {
    triggeredCheck = false;
    return true;
  } else {
    return false;
  }
}

}  // namespace LevelObject
}  // namespace SantaRacer
