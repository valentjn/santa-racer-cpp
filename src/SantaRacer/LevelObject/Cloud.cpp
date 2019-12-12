/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include "SantaRacer/Game.hpp"
#include "SantaRacer/LevelObject/Cloud.hpp"
#include "SantaRacer/LevelObject/LevelObject.hpp"

namespace SantaRacer {
namespace LevelObject {

Cloud::Cloud(Game* game, size_t tileX, size_t tileY) :
    LevelObject(game, tileX, tileY, &game->getImageLibrary().getAsset("cloud")),
    levelX((tileX + 0.5) * game->getLevel().getTileWidth() - image->getWidth() / 2),
    y((tileY + 0.5) * game->getLevel().getTileHeight() - image->getHeight() / 2) {
}

Cloud::~Cloud() {
}

int Cloud::getLevelX() const {
  return levelX;
}

int Cloud::getY() const {
  return y;
}

size_t Cloud::getFrame() const {
  return 0;
}

}  // namespace LevelObject
}  // namespace SantaRacer
