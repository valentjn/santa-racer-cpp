/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include "SantaRacer/Game.hpp"
#include "SantaRacer/LevelObject/Finish.hpp"
#include "SantaRacer/LevelObject/LevelObject.hpp"

namespace SantaRacer {
namespace LevelObject {

Finish::Finish(Game* game, size_t tileX, size_t tileY) :
    LevelObject(game, tileX, tileY, game->getImageLibrary().getAsset("finish")),
    levelX((tileX + 0.5) * game->getLevel().getTileWidth() - image.getWidth() / 2),
    y((tileY + 0.5) * game->getLevel().getTileHeight() - image.getHeight() / 2) {
}

Finish::~Finish() {
}

int Finish::getLevelX() const {
  return levelX;
}

int Finish::getY() const {
  return y;
}

size_t Finish::getFrame() const {
  return 0;
}

bool Finish::checkReached() const {
  return (game->getLevel().getOffset() + game->getSleigh().getX() >= getLevelX());
}

}  // namespace LevelObject
}  // namespace SantaRacer
