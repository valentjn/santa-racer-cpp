/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

#include "SantaRacer/LevelObject/LevelObject.hpp"

namespace SantaRacer {

namespace LevelObject {

class Snowman;

}  // namespace LevelObject

class SnowmanStar {
 public:
  SnowmanStar(Game* game, LevelObject::Snowman* snowman);

  void initialize(bool useRandomFrame = false);
  void draw() const;
  void move();

  int getFrame() const;

 protected:
  const int maxNumberOfFrames = 30;
  const int frameSpeed = 34;
  const int minXOffset = -5;
  const int maxXOffset = 5;
  const int minYOffset = -5;
  const int maxYOffset = 5;

  const int snowmanRocketOffsetX = 35;
  const int snowmanRocketOffsetY = 35;

  const int minNumberOfFramesToWait = 50;
  const int maxNumberOfFramesToWait = 100;

  Game* game;
  LevelObject::Snowman *snowman;
  const Asset::Image& image;

  int levelX;
  int y;
  int frame;
  int maxFrame;
  size_t time;
};

}  // namespace SantaRacer
