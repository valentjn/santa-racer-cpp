/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include <SDL/SDL.h>

#include "SantaRacer/Game.hpp"
#include "SantaRacer/LevelObject/GoblinSnowball.hpp"
#include "SantaRacer/LevelObject/LevelObject.hpp"

namespace SantaRacer {
namespace LevelObject {

GoblinSnowball::GoblinSnowball(Game* game, size_t tileX, size_t tileY) :
    LevelObject(game, tileX, tileY, &game->getImageLibrary().getAsset("snowball")),
    levelX(tileX * game->getLevel().getTileWidth() + offsetX),
    y(tileY * game->getLevel().getTileHeight() + offsetY), frame(0), time(SDL_GetTicks()) {
}

GoblinSnowball::~GoblinSnowball() {
}

int GoblinSnowball::getLevelX() const {
  return levelX + static_cast<int>((SDL_GetTicks() - time) / 1000.0 * speedX);
}

int GoblinSnowball::getY() const {
  const double duration = (SDL_GetTicks() - time) / 1000.0;

  return y + speedYStart * duration +
         0.5 * gravityAcceleration * duration * duration;
}

size_t GoblinSnowball::getFrame() const {
  return 0;
}

}  // namespace LevelObject
}  // namespace SantaRacer
