/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

namespace SantaRacer {

class Game;

class Snowflake {
 public:
  Snowflake(Game* game);

  void initialize(bool putOnTop = false);
  void draw() const;
  void move();
  void changeSpeed();
  double getLevelX() const;
  double getY() const;

 protected:
  Game* game;
  double levelX;
  double y;
  size_t z;
  Uint32 color;
  int speedX;
  int speedY;
  size_t speedChangeTime;
  size_t time;

  const int minSpeedX = -40;
  const int maxSpeedX = 40;
  const int minSpeedY = 40;
  const int maxSpeedY = 160;
  const int minSpeedChangeTime = 25;
  const int maxSpeedChangeTime = 250;
  const int leftMargin = -50;
};

}  // namespace SantaRacer
