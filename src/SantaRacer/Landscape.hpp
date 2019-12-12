/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

#include "SantaRacer/Asset/Image.hpp"

namespace SantaRacer {

class Game;

class Landscape {
 public:
  explicit Landscape(Game* game);

  void initialize();

  void draw() const;
  void move();

  double getOffset() const;
  double getSpeed() const;

  bool isPaused() const;
  void setPaused(bool paused);

 protected:
  Game* game;
  const Asset::Image& image;

  size_t time;
  double offset;
  double speed;
  bool paused;
};

}  // namespace SantaRacer
