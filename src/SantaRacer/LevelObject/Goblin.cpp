/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include "SantaRacer/Game.hpp"
#include "SantaRacer/LevelObject/Goblin.hpp"
#include "SantaRacer/LevelObject/GoblinSnowball.hpp"
#include "SantaRacer/LevelObject/LevelObject.hpp"

namespace SantaRacer {
namespace LevelObject {

Goblin::Goblin(Game* game, size_t tileX, size_t tileY) :
    LevelObject(game, tileX, tileY, game->getImageLibrary().getAsset("goblin")),
    levelX((tileX + 0.5) * game->getLevel().getTileWidth() -
      (image.getWidth() / image.getNumberOfFrames()) / 2),
    y((tileY + 0.5) * game->getLevel().getTileHeight() - image.getHeight() / 2),
    frame(0), time(SDL_GetTicks()), snowballThrown(false), snowballThrownCheck(false) {
}

Goblin::~Goblin() {
}

void Goblin::move() {
  if (frame != 13) {
    snowballThrown = false;
  } else if (!snowballThrown) {
    snowballThrown = true;
    snowballThrownCheck = true;
    game->getLevel().getLevelObjects().emplace_back(new GoblinSnowball(game, tileX, tileY));
  }
}

int Goblin::getLevelX() const {
  return levelX;
}

int Goblin::getY() const {
  return y;
}

size_t Goblin::getFrame() const {
  return static_cast<int>((SDL_GetTicks() - time) / 1000.0 * frameSpeed + frame) %
      image.getNumberOfFrames();
}

bool Goblin::checkSnowballThrown() {
  if (snowballThrownCheck) {
    snowballThrownCheck = false;
    return true;
  } else {
    return false;
  }
}

}  // namespace LevelObject
}  // namespace SantaRacer
