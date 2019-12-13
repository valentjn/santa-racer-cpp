/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include <memory>

#include "SantaRacer/Game.hpp"
#include "SantaRacer/LevelObject/Angel.hpp"
#include "SantaRacer/LevelObject/Balloon.hpp"
#include "SantaRacer/LevelObject/Cloud.hpp"
#include "SantaRacer/LevelObject/Finish.hpp"
#include "SantaRacer/LevelObject/Goblin.hpp"
#include "SantaRacer/LevelObject/GoblinSnowball.hpp"
#include "SantaRacer/LevelObject/LevelObject.hpp"
#include "SantaRacer/LevelObject/Snowman.hpp"

namespace SantaRacer {
namespace LevelObject {

LevelObject::LevelObject(Game* game, size_t tileX, size_t tileY, Asset::Image* image) :
    game(game), image(image), tileX(tileX), tileY(tileY), visible(true) {
}

LevelObject::~LevelObject() {
}

std::unique_ptr<LevelObject> LevelObject::create(Game* game, size_t tileX, size_t tileY,
    size_t mapValue) {
  if (mapValue == 70) {
    return std::unique_ptr<LevelObject>(new Angel(game, tileX, tileY));
  } else if (mapValue == 71) {
    return std::unique_ptr<LevelObject>(new Balloon(game, tileX, tileY, Balloon::Type::Cash));
  } else if (mapValue == 72) {
    return std::unique_ptr<LevelObject>(new Balloon(game, tileX, tileY, Balloon::Type::Normal));
  } else if (mapValue == 73) {
    return std::unique_ptr<LevelObject>(new Balloon(game, tileX, tileY, Balloon::Type::Champagne));
  } else if (mapValue == 74) {
    return std::unique_ptr<LevelObject>(new Balloon(game, tileX, tileY, Balloon::Type::Gift));
  } else if (mapValue == 76) {
    return std::unique_ptr<LevelObject>(new Balloon(game, tileX, tileY, Balloon::Type::Shield));
  } else if (mapValue == 75) {
    return std::unique_ptr<LevelObject>(new Cloud(game, tileX, tileY));
  } else if (mapValue == 77) {
    return std::unique_ptr<LevelObject>(new Finish(game, tileX, tileY));
  } else if (mapValue == 69) {
    return std::unique_ptr<LevelObject>(new Goblin(game, tileX, tileY));
  } else if (mapValue == 200) {
    return std::unique_ptr<LevelObject>(new GoblinSnowball(game, tileX, tileY));
  } else if (mapValue == 30) {
    return std::unique_ptr<LevelObject>(new Snowman(game, tileX, tileY));
  } else {
    return std::unique_ptr<LevelObject>();
  }
}

void LevelObject::draw() const {
  if (visible) {
    image->copy(&game->getScreenSurface(),
        {getLevelX() - static_cast<int>(game->getLevel().getOffset()), getY()}, getFrame());
  }
}

void LevelObject::move() {
}

size_t LevelObject::getTileX() const {
  return tileX;
}

size_t LevelObject::getTileY() const {
  return tileY;
}

Asset::Image& LevelObject::getImage() {
  return *image;
}

bool LevelObject::isVisible() const {
  return visible;
}

void LevelObject::setVisible(bool visible) {
  this->visible = visible;
}

}  // namespace LevelObject
}  // namespace SantaRacer
