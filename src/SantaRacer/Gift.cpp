/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include <algorithm>
#include <vector>

#include "SantaRacer/Game.hpp"
#include "SantaRacer/Gift.hpp"
#include "SantaRacer/Printer.hpp"
#include "SantaRacer/RNG.hpp"
#include "SantaRacer/Chimney.hpp"

namespace SantaRacer {

const std::vector<int> Gift::allGiftPoints = {10, 15, 20};

Gift::Gift(Game* game) : game(game),
    imagesGift({&game->getImageLibrary().getAsset("gift1"),
        &game->getImageLibrary().getAsset("gift2"), &game->getImageLibrary().getAsset("gift3")}),
    imageBigStar(game->getImageLibrary().getAsset("big_star")),
    imagesGiftPoints({&game->getImageLibrary().getAsset("10"),
        &game->getImageLibrary().getAsset("15"), &game->getImageLibrary().getAsset("20")}),
    levelX(game->getSleigh().getX() + game->getLevel().getOffset()),
    y(game->getSleigh().getY() + game->getSleigh().getHeight()),
    speedX(game->getLevel().getSpeed()), type(game->getRNG().getInteger(0, 2)),
    frame(game->getRNG().getInteger(0, imagesGift[0]->getNumberOfFrames() - 1)),
    time(SDL_GetTicks()), collidedWithGround(false), collidedWithChimney(false), succeeded(false),
    deleted(false), giftPoints(0), doublePointsActivated(false), bigStarTime(0) {
}

void Gift::draw() const {
  if (succeeded) {
    const int x = getLevelX() - game->getLevel().getOffset() - imageBigStar.getWidth() / 2;
    const int y = getY() - imageBigStar.getHeight() / 2;

    if (doublePointsActivated) {
      drawBigStar(x, y);
      drawBigStar(x + doublePointsXOffset, y + doublePointsXOffset);
      drawPoints(x, y);
      drawPoints(x + doublePointsXOffset, y + doublePointsYOffset);
    } else {
      drawBigStar(x, y);
      drawPoints(x, y);
    }
  } else {
    imagesGift[type]->copy(&game->getScreenSurface(),
        {getLevelX() - static_cast<int>(game->getLevel().getOffset()), getY()}, getFrame());
  }
}

void Gift::drawBigStar(int x, int y) const {
  const size_t bigStarVirtualFrame = std::min(getBigStarFrame(), bigStarVirtualFrameCount - 1);

  if (bigStarVirtualFrame < 10) {
    imageBigStar.copy(&game->getScreenSurface(), {x + bigStar1XOffset, y + bigStar1YOffset},
        bigStarVirtualFrame);
  }

  if ((bigStarVirtualFrame >= 2) && (bigStarVirtualFrame < 12)) {
    imageBigStar.copy(&game->getScreenSurface(), {x + bigStar2XOffset, y + bigStar2YOffset},
        bigStarVirtualFrame - 2);
  }

  if (bigStarVirtualFrame >= 4) {
    imageBigStar.copy(&game->getScreenSurface(), {x + bigStar3XOffset, y + bigStar3YOffset},
        bigStarVirtualFrame - 4);
  }
}

void Gift::drawPoints(int x, int y) const {
  const size_t frame = std::find(allGiftPoints.begin(), allGiftPoints.end(), giftPoints) -
      allGiftPoints.begin();
  imagesGiftPoints[frame]->copy(&game->getScreenSurface(),
      {x + pointsXOffset + static_cast<int>(imageBigStar.getWidth() / 2),
      y + pointsYOffset + static_cast<int>(imageBigStar.getHeight() / 2)});
}

void Gift::move() {
  if (deleted) {
    return;
  } else if (succeeded) {
    if (getBigStarFrame() >= bigStarVirtualFrameCount) {
      deleted = true;
    }

    return;
  }

  const int y = getY();

  if (y >= static_cast<int>(game->getScreenHeight())) {
    collideWithGround();
    return;
  }

  const int levelX = getLevelX();
  const size_t tileX0 = static_cast<size_t>(game->getLevel().getOffset() /
      game->getLevel().getTileWidth());

  for (size_t tileY = 0; tileY < game->getLevel().getNumberOfTilesY(); tileY++) {
    for (size_t tileX = tileX0; tileX < tileX0 + game->getLevel().getNumberOfTilesPerScreenWidth();
        tileX++) {
      const size_t mapValue = game->getLevel().getMap()[tileY][tileX];

      if (mapValue == 0) {
        continue;
      }

      const int chimneyX = static_cast<int>(tileX * game->getLevel().getTileWidth());
      const int chimneyY = static_cast<int>(tileY * game->getLevel().getTileHeight());

      for (const Chimney& chimney : game->getChimneys()) {
        if (chimney.getMapValue() != mapValue) {
          continue;
        }

        if ((levelX >= chimneyX + chimney.getX()) &&
            (y + static_cast<int>(imagesGift[type]->getHeight()) / 2 >=
              chimneyY + chimney.getY()) &&
            (levelX <= chimneyX + chimney.getX() + static_cast<int>(chimney.getWidth())) &&
            (y <= chimneyY + chimney.getY() + static_cast<int>(chimney.getHeight()))) {
          collideWithChimney(*std::find(allGiftPoints.begin(), allGiftPoints.end(),
              allGiftPoints[tileY - 1]));
          return;
        }
      }
    }
  }
}

void Gift::collideWithGround() {
  collidedWithGround = true;
}

void Gift::collideWithChimney(int points) {
  giftPoints = points;
  bigStarTime = SDL_GetTicks();

  levelX = getLevelX();
  y = getY();

  succeeded = true;
  collidedWithChimney = true;
}

void Gift::activateDoublePoints() {
  doublePointsActivated = true;
}

int Gift::getLevelX() const {
  return (succeeded ? levelX :
      (levelX + static_cast<int>((SDL_GetTicks() - time) / 1000.0 * speedX)));
}

int Gift::getY() const {
  if (succeeded) {
    return y;
  } else {
    const double duration = (SDL_GetTicks() - time) / 1000.0;
    return y + speedYStart * duration + 0.5 * gravityAcceleration * duration * duration;
  }
}

size_t Gift::getFrame() const {
  return static_cast<size_t>((SDL_GetTicks() - time) / 1000.0 * frameSpeed) + frame;
}

size_t Gift::getBigStarFrame() const {
  return static_cast<size_t>((SDL_GetTicks() - bigStarTime) / 1000.0 * bigStarVirtualFrameSpeed);
}

bool Gift::checkCollisionWithGround() {
  if (collidedWithGround) {
    deleted = true;
    return true;
  } else {
    return false;
  }
}

bool Gift::checkCollisionWithChimney() {
  if (collidedWithChimney) {
    collidedWithChimney = false;
    return true;
  } else {
    return false;
  }
}

int Gift::getGiftPoints() const {
  return giftPoints;
}

bool Gift::shouldBeDeleted() const {
  return deleted;
}

}  // namespace SantaRacer
