/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

#include <memory>
#include <vector>

#include "SantaRacer/LevelObject/LevelObject.hpp"

namespace SantaRacer {

class Game;

class Level {
 public:
  Level(Game* game, const std::vector<double>& mapData,
      const std::vector<double>& levelObjectsMapData, size_t numberOfTilesY);

  void draw() const;
  void drawBallons() const;
  void drawObjects() const;
  void move();
  void moveObjects();
  void moveObject(size_t tileX, size_t tileY);
  void clearObjects();

  double getOffset() const;
  void setOffset(double offset);

  double getSpeed() const;
  size_t getNumberOfTilesPerScreenWidth() const;
  size_t getTileWidth() const;
  size_t getTileHeight() const;
  size_t getNumberOfTilesX() const;
  size_t getNumberOfTilesY() const;
  std::vector<std::vector<size_t>>& getMap();
  std::vector<std::vector<size_t>>& getLevelObjectsMap();
  std::vector<std::unique_ptr<LevelObject::LevelObject>>& getLevelObjects();

  void setInMenuMode(bool menu_mode);

  bool isPaused() const;
  void setPaused(bool paused);

 protected:
  const int minSpeed = 40;
  const int maxSpeed = 160;
  const int menuSpeed = 40;

  Game* game;
  const Asset::Image& image;

  const size_t tileWidth;
  const size_t tileHeight;

  size_t numberOfTilesX;
  size_t numberOfTilesY;
  size_t time;
  size_t numberOfTilesPerScreenWidth;
  double offset;
  bool inMenuMode;
  bool paused;

  std::vector<std::vector<size_t>> map;
  std::vector<std::vector<size_t>> levelObjectsMap;
  std::vector<std::unique_ptr<LevelObject::LevelObject>> levelObjects;
};

}  // namespace SantaRacer
