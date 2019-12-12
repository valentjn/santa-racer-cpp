/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

#include <SDL/SDL.h>

namespace SantaRacer {

class Game;

class Score {
 public:
  explicit Score(Game *game);

  void initialize(int totalTime);
  void draw() const;

  int getGiftPoints() const;
  void setGiftPoints(int giftPoints);
  void addGiftPoints(int giftPoints);

  int getDamagePoints() const;
  void setDamagePoints(int damagePoints);
  void addDamagePoints(int damagePoints);

  int getRemainingTime() const;
  void addToRemainingTime(int time);
  void resetClock(int totalTime);

  int getScore() const;

 protected:
  const int scorePointsPerGiftPoint = 1;
  const int scorePointsPerDamagePoint = -2;
  const int scorePointsPerRemainingTime = 10;

  Game *game;

  const Asset::Image& scoreGiftImage;
  const Asset::Image& scoreDamageImage;
  const Asset::Image& scoreTimeImage;

  int giftPoints;
  int damagePoints;
  int timeStart;
  int totalTime;
};

}  // namespace SantaRacer
