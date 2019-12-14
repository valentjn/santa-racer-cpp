/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

#include <vector>

#include "SantaRacer/Asset/Image.hpp"

namespace SantaRacer {

class Game;

class Gift {
 public:
  explicit Gift(Game* game);

  void draw();
  void drawBigStar(int x, int y);
  void drawPoints(int x, int y);
  void move();
  void collideWithGround();
  void collideWithChimney(int points);
  void activateDoublePoints();

  int getLevelX() const;
  int getY() const;
  size_t getFrame() const;
  size_t getBigStarFrame() const;
  int getGiftPoints() const;
  bool shouldBeDeleted() const;

  bool checkCollisionWithGround();
  bool checkCollisionWithChimney();

 protected:
  const size_t frameSpeed = 15;

  const int gravityAcceleration = 200;
  const int speedYStart = 50;

  const size_t bigStarVirtualFrameCount = 14;
  const size_t bigStarVirtualFrameSpeed = 15;

  const int bigStar1XOffset = 10;
  const int bigStar1YOffset = 10;
  const int bigStar2XOffset = 25;
  const int bigStar2YOffset = 15;
  const int bigStar3XOffset = 15;
  const int bigStar3YOffset = 25;
  const int pointsXOffset = 10;
  const int pointsYOffset = 10;
  const int doublePointsXOffset = 10;
  const int doublePointsYOffset = 10;

  static const std::vector<int> allGiftPoints;

  Game* game;
  const std::vector<Asset::Image*> imagesGift;
  Asset::Image* imageBigStar;
  const std::vector<Asset::Image*> imagesGiftPoints;

  int levelX;
  int y;
  int speedX;
  size_t type;
  size_t frame;
  size_t time;

  bool collidedWithGround;
  bool collidedWithChimney;
  bool succeeded;
  bool deleted;
  int giftPoints;
  bool doublePointsActivated;

  size_t bigStarTime;
};

}  // namespace SantaRacer
