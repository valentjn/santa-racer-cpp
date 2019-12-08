/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

#include "SantaRacer/LevelObject/LevelObject.hpp"

namespace SantaRacer {
namespace LevelObject {

class Finish : public LevelObject {
 public:
  Finish(Game* game, size_t tileX, size_t tileY);
  ~Finish() override;

  int getLevelX() const override;
  int getY() const override;
  size_t getFrame() const override;

  bool checkReached() const;

 protected:
  int levelX;
  int y;
};

}  // namespace LevelObject
}  // namespace SantaRacer
