/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

#include "SantaRacer/Asset/Image.hpp"

namespace SantaRacer {

class Game;

class SleighStar {
 public:
  SleighStar(Game* game);

  void initialize(bool useRandomFrame = false);
  void draw() const;
  void move();
  size_t getFrame() const;

 protected:
  int levelX;
  int y;
  size_t frame;
  size_t maxFrame;
  size_t time;

  Game* game;
  const Asset::Image& imageNormal;
  const Asset::Image& imageDrunk;

  const size_t maxNumberOfFrames = 30;
  const size_t frameSpeed = 34;
  const int minXOffset = -10;
  const int maxXOffset = 140;
  const int minYOffset = 0;
  const int maxYOffset = 10;
};

}  // namespace SantaRacer
