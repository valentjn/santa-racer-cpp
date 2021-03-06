/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

#include "SantaRacer/LevelObject/LevelObject.hpp"

namespace SantaRacer {
namespace LevelObject {

class Goblin : public LevelObject {
 public:
  Goblin(Game* game, size_t tileX, size_t tileY);
  ~Goblin() override;

  void move() override;

  int getLevelX() const override;
  int getY() const override;
  size_t getFrame() const override;

  bool checkSpawnSnowball();

 protected:
  const size_t frameSpeed = 12;
  const size_t spawnSnowballFrame = 13;

  int levelX;
  int y;
  size_t frame;
  size_t time;
  bool snowballThrown;
  bool spawnSnowball;
};

}  // namespace LevelObject
}  // namespace SantaRacer
