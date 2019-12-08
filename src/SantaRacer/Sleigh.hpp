/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

#include <vector>

#include "SantaRacer/SleighStar.hpp"
#include "SantaRacer/LevelObject/LevelObject.hpp"

namespace SantaRacer {

class Game;

class Sleigh {
 public:
  Sleigh(Game* game);

  void initialize();
  void initializeSleighStars();
  void draw() const;
  void moveSleighStars();
  void electrify();
  void collideLevelObject();
  void collideLevel();
  void becomeDrunk();
  void activateShield();

  bool isInvincible() const;
  bool isElectrified() const;
  bool isDrunk() const;
  bool isShieldActivated() const;
  bool isImmobile() const;

  bool checkCollisionLevel();
  LevelObject::LevelObject *checkCollisionLevelObject();

  int getX() const;
  void setX(int x);

  int getY() const;
  void setY(int y);

  int getSpeedX() const;
  void setSpeedX(int direction);

  int getSpeedY() const;
  void setSpeedY(int direction);

  bool isPaused() const;
  void setPaused(bool paused);

  size_t getWidth() const;
  size_t getHeight() const;
  size_t getFrame() const;
  size_t getReindeerFrame() const;

  void setInMenuMode(bool inMenuMode);
  void setAlpha(Uint8 alpha);

 protected:
  const size_t frameSpeed = 14;
  const size_t shieldFrameSpeed = 8;

  const size_t menuXPeriod = 30000;
  const int minMenuX = 50;
  const int maxMenuX = 450;
  const size_t menuYPeriod = 20000;
  const int minMenuY = 50;
  const int maxMenuY = 200;

  const size_t numberOfStars = 50;
  const size_t acceleration = 25;
  const size_t maxMoveSpeed = 200;

  const int electrifiedOffsetX = -3;
  const int electrifiedOffsetY = -2;
  const int reindeerOffsetX = 10;
  const int reindeerOffsetY = 3;
  const int shieldOffsetX = -12;
  const int shieldOffsetY = -17;

  const size_t invincibleInvisiblePeriod = 200;

  const size_t invincibleDuration = 3000;
  const size_t electrifiedDuration = 1000;
  const size_t drunkDuration = 15000;
  const size_t shieldDuration = 15000;
  const size_t collisionInvincibleDuration = 8000;
  const size_t collisionUnmovableDuration = 5000;

  Game *game;

  Asset::Image& sleighImage;
  Asset::Image& electrifiedSleighImage;
  Asset::Image& reindeerImage;
  Asset::Image& electrifiedReindeerImage;
  Asset::Image& shieldImage;
  Asset::Image& levelImage;

  int x;
  int y;
  int speedX;
  int speedY;
  size_t width;
  size_t height;
  size_t frame;
  size_t time;
  size_t timeX;
  size_t timeY;

  Uint8 alpha;
  bool inMenuMode;
  double menuOffsetAngleX;
  double menuOffsetAngleY;
  std::vector<SleighStar> sleighStars;

  size_t electrifiedEndTime;
  size_t invincibleEndTime;
  size_t drunkEndTime;
  size_t shieldEndTime;
  size_t immobileEndTime;

  bool paused;
};

}  // namespace SantaRacer
