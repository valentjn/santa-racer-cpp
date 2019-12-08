/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include <string>
#include <unordered_map>

#include "SantaRacer/Game.hpp"
#include "SantaRacer/LevelObject/Balloon.hpp"
#include "SantaRacer/LevelObject/LevelObject.hpp"

namespace SantaRacer {
namespace LevelObject {

const std::unordered_map<Balloon::Type, std::string> Balloon::imageNameMap = {
      {Balloon::Type::Normal, "balloon1"},
      {Balloon::Type::Cash, "balloon2"},
      {Balloon::Type::Champagne, "balloon5"},
      {Balloon::Type::Gift, "balloon4"},
      {Balloon::Type::Shield, "balloon3"},
    };

Balloon::Balloon(Game* game, size_t tileX, size_t tileY, Type type) :
    LevelObject(game, tileX, tileY,
      game->getImageLibrary().getAsset(imageNameMap.find(type)->second)),
    type(type), levelX((tileX + 0.5) * game->getLevel().getTileWidth() -
      (image.getWidth() / image.getNumberOfFrames()) / 2),
    y((tileY + 1.5) * game->getLevel().getTileHeight() - image.getHeight() / 2),
    frame(0), time(SDL_GetTicks()) {
}

Balloon::~Balloon() {
}

int Balloon::getLevelX() const {
  return levelX;
}

int Balloon::getY() const {
  return y - speed * (SDL_GetTicks() - time) / 1000.0;
}

size_t Balloon::getFrame() const {
  /*if (frame >= image.getNumberOfFrames()) {
    frame = 2 * image.getNumberOfFrames() - frame - 2;
  }*/

  return static_cast<int>((SDL_GetTicks() - time) / 1000.0 * frameSpeed + frame) %
      (image.getNumberOfFrames() * 2 - 2);
}

Balloon::Type Balloon::getType() const {
  return type;
}

}  // namespace LevelObject
}  // namespace SantaRacer
