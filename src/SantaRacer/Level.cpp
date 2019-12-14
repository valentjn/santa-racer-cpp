/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include <SDL2/SDL.h>

#include <memory>
#include <vector>

#include "SantaRacer/Game.hpp"
#include "SantaRacer/Level.hpp"
#include "SantaRacer/LevelObject/Balloon.hpp"

namespace SantaRacer {

Level::Level(Game* game, const std::vector<double>& mapData,
    const std::vector<double>& levelObjectsMapData, size_t numberOfTilesY) :
    game(game), image(&game->getImageLibrary().getAsset("level")),
    tileWidth(image->getWidth()), tileHeight(image->getHeight()),
    numberOfTilesX(mapData.size() / numberOfTilesY), numberOfTilesY(numberOfTilesY),
    time(SDL_GetTicks()), numberOfTilesPerScreenWidth(game->getScreenWidth() / tileWidth + 1),
    offset(0.0), inMenuMode(true), paused(false) {
  for (size_t y = 0; y < numberOfTilesY; y++) {
    map.emplace_back(mapData.begin() + y * numberOfTilesX,
        mapData.begin() + (y + 1) * numberOfTilesX);
    levelObjectsMap.emplace_back(levelObjectsMapData.begin() + y * numberOfTilesX,
        levelObjectsMapData.begin() + (y + 1) * numberOfTilesX);
  }
}

void Level::draw() {
  const size_t x0 = getOffset() / tileWidth;

  for (size_t y = 0; y < numberOfTilesY; y++) {
    for (size_t x = x0; x < x0 + numberOfTilesPerScreenWidth; x++) {
      const size_t frame = map[y][x];

      if (frame != 0) {
        image->copy({static_cast<int>(x * tileWidth - offset), static_cast<int>(y * tileHeight)},
            frame);
      }
    }
  }
}

void Level::drawBallons() {
  for (const std::unique_ptr<LevelObject::LevelObject>& levelObject : levelObjects) {
    if (dynamic_cast<LevelObject::Balloon*>(levelObject.get()) != nullptr) {
      levelObject->draw();
    }
  }
}

void Level::drawObjects() {
  for (const std::unique_ptr<LevelObject::LevelObject>& levelObject : levelObjects) {
    if (dynamic_cast<LevelObject::Balloon*>(levelObject.get()) == nullptr) {
      levelObject->draw();
    }
  }
}

void Level::move() {
  offset = getOffset();
  time = SDL_GetTicks();
}

void Level::moveObjects() {
  const size_t x0 = static_cast<size_t>(getOffset() / tileWidth);

  for (size_t y = 0; y < numberOfTilesY; y++) {
    for (size_t x = x0; x < x0 + numberOfTilesPerScreenWidth + 1; x++) {
      if (levelObjectsMap[y][x] != 0) {
        moveObject(x, y);
      }
    }
  }

  auto it = levelObjects.begin();

  while (it != levelObjects.end()) {
    if ((static_cast<int>((*it)->getTileX()) < static_cast<int>(x0) - 1) ||
        ((*it)->getY() > static_cast<int>(2 * game->getScreenHeight()))) {
      it = levelObjects.erase(it);
    } else {
      ++it;
    }
  }
}

void Level::moveObject(size_t tileX, size_t tileY) {
  for (std::unique_ptr<LevelObject::LevelObject>& levelObject : levelObjects) {
    if ((levelObject->getTileX() == tileX) && (levelObject->getTileY() == tileY)) {
      levelObject->move();
      return;
    }
  }

  levelObjects.push_back(LevelObject::LevelObject::create(
      game, tileX, tileY, levelObjectsMap[tileY][tileX]));
}

void Level::clearObjects() {
  levelObjects.clear();
}

double Level::getOffset() const {
  return (paused ? offset : (offset + (SDL_GetTicks() - time) / 1000.0 * getSpeed()));
}

void Level::setOffset(double offset) {
  this->offset = offset;
  time = SDL_GetTicks();
}

double Level::getSpeed() const {
  if (paused) {
    return 0.0;
  } else if (inMenuMode) {
    return menuSpeed;
  } else {
    return game->getSleigh().getX() /
        static_cast<double>(game->getScreenWidth() - game->getSleigh().getWidth()) *
        (maxSpeed - minSpeed) + minSpeed;
  }
}

size_t Level::getNumberOfTilesPerScreenWidth() const {
  return numberOfTilesPerScreenWidth;
}

size_t Level::getTileWidth() const {
  return tileWidth;
}

size_t Level::getTileHeight() const {
  return tileHeight;
}

size_t Level::getNumberOfTilesX() const {
  return numberOfTilesX;
}

size_t Level::getNumberOfTilesY() const {
  return numberOfTilesY;
}

std::vector<std::vector<size_t>>& Level::getMap() {
  return map;
}

std::vector<std::vector<size_t>>& Level::getLevelObjectsMap() {
  return levelObjectsMap;
}

std::vector<std::unique_ptr<LevelObject::LevelObject>>& Level::getLevelObjects() {
  return levelObjects;
}

void Level::setInMenuMode(bool menu_mode) {
  inMenuMode = menu_mode;
}

bool Level::isPaused() const {
  return paused;
}

void Level::setPaused(bool paused) {
  if (paused != this->paused) {
    offset = getOffset();
    time = SDL_GetTicks();
  }

  this->paused = paused;
}

}  // namespace SantaRacer
