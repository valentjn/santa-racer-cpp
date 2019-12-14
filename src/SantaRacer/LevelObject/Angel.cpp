/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include <SDL/SDL.h>

#include "SantaRacer/Game.hpp"
#include "SantaRacer/LevelObject/Angel.hpp"
#include "SantaRacer/LevelObject/LevelObject.hpp"

namespace SantaRacer {
namespace LevelObject {

Angel::Angel(Game* game, size_t tileX, size_t tileY) :
    LevelObject(game, tileX, tileY, &game->getImageLibrary().getAsset("angel")),
    levelX((tileX + 0.5) * game->getLevel().getTileWidth() -
      (image->getWidth() / image->getNumberOfFrames()) / 2),
    y((tileY + 0.5) * game->getLevel().getTileHeight() - image->getHeight() / 2),
    frame(0), time(SDL_GetTicks()) {
}

Angel::~Angel() {
}

int Angel::getLevelX() const {
  return levelX;
}

int Angel::getY() const {
  return y;
}

size_t Angel::getFrame() const {
  return static_cast<size_t>((SDL_GetTicks() - time) / 1000.0 * frameSpeed + frame) %
      image->getNumberOfFrames();
}

}  // namespace LevelObject
}  // namespace SantaRacer
