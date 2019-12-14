/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

#include <vector>

#include "SantaRacer/SnowmanStar.hpp"
#include "SantaRacer/LevelObject/LevelObject.hpp"

namespace SantaRacer {
namespace LevelObject {

class Snowman : public LevelObject {
 public:
  Snowman(Game* game, size_t tileX, size_t tileY);
  ~Snowman() override;

  void draw() override;
  void move() override;

  int getLevelX() const override;
  int getY() const override;
  size_t getFrame() const override;

  bool isTriggered();
  bool checkTriggered();

 protected:
  const size_t frameSpeed = 8;

  const int speedX = -100;
  const int speedY = -150;

  const int minTriggerOffset = 200;
  const int maxTriggerOffset = 400;

  const size_t numberOfSnowmanStars = 20;

  int levelX;
  int y;
  size_t frame;
  size_t time;
  int triggerOffset;
  bool triggered;
  bool triggeredCheck;

  std::vector<SnowmanStar> snowmanStars;
};

}  // namespace LevelObject
}  // namespace SantaRacer
