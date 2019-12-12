/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include <algorithm>
#include <cmath>
#include <memory>
#include <vector>

#include "SantaRacer/Game.hpp"
#include "SantaRacer/RNG.hpp"
#include "SantaRacer/Sleigh.hpp"
#include "SantaRacer/LevelObject/Balloon.hpp"

namespace SantaRacer {

Sleigh::Sleigh(Game* game) : game(game),
    sleighImage(game->getImageLibrary().getAsset("sleigh")),
    electrifiedSleighImage(game->getImageLibrary().getAsset("electrified_sleigh")),
    reindeerImage(game->getImageLibrary().getAsset("reindeer")),
    electrifiedReindeerImage(game->getImageLibrary().getAsset("electrified_reindeer")),
    shieldImage(game->getImageLibrary().getAsset("shield")),
    levelImage(game->getImageLibrary().getAsset("level")) {
  initialize();
}

void Sleigh::initialize() {
  x = 0;
  y = 0;
  speedX = 0;
  speedY = 0;
  width = reindeerImage.getWidth() + sleighImage.getWidth() + reindeerOffsetX;
  height = sleighImage.getHeight();
  frame = 0;
  time = SDL_GetTicks();
  timeX = 0;
  timeY = 0;
  alpha = 255;
  inMenuMode = true;
  menuOffsetAngleX = game->getRNG().getInteger(0, 2 * M_PI) / 100.0;
  menuOffsetAngleY = game->getRNG().getInteger(0, 2 * M_PI) / 100.0;
  electrifiedEndTime = 0;
  invincibleEndTime = 0;
  drunkEndTime = 0;
  shieldEndTime = 0;
  immobileEndTime = 0;
  paused = false;

  setAlpha(255);
}

void Sleigh::initializeSleighStars() {
  sleighStars.clear();

  for (size_t i = 0; i < numberOfStars; i++) {
    sleighStars.emplace_back(game);
  }
}

void Sleigh::draw() const {
  if (isInvincible() && ((invincibleEndTime - SDL_GetTicks()) % invincibleInvisiblePeriod >=
      invincibleInvisiblePeriod / 2)) {
    return;
  }

  const size_t sleighFrame = getFrame();
  const size_t reindeerFrame = getReindeerFrame();
  const int x = getX();
  const int y = getY();

  if (isElectrified()) {
    electrifiedSleighImage.copy(&game->getScreenSurface(), {
          x - static_cast<int>(electrifiedSleighImage.getWidth() - sleighImage.getWidth()) / 2 +
            electrifiedOffsetX,
          y - static_cast<int>(electrifiedSleighImage.getHeight() - sleighImage.getHeight()) / 2 +
            electrifiedOffsetY
        });
    electrifiedReindeerImage.copy(&game->getScreenSurface(), {
          x + static_cast<int>(sleighImage.getWidth()) + reindeerOffsetX -
            static_cast<int>(electrifiedReindeerImage.getWidth() - reindeerImage.getWidth()) / 2 +
            electrifiedOffsetX,
          y + reindeerOffsetY -
            static_cast<int>(electrifiedReindeerImage.getHeight() - reindeerImage.getHeight()) / 2 +
            electrifiedOffsetY
        });
    electrifiedReindeerImage.copy(&game->getScreenSurface(), {
          x + static_cast<int>(sleighImage.getWidth()) -
            static_cast<int>(electrifiedReindeerImage.getWidth() - reindeerImage.getWidth()) / 2 +
            electrifiedOffsetX,
          y + reindeerOffsetY -
            static_cast<int>(electrifiedReindeerImage.getHeight() - reindeerImage.getHeight()) / 2 +
            electrifiedOffsetY
        });
  }

  sleighImage.copy(&game->getScreenSurface(), {x, y}, sleighFrame);
  reindeerImage.copy(&game->getScreenSurface(),
      {x + static_cast<int>(sleighImage.getWidth()) + reindeerOffsetX, y + reindeerOffsetY},
      reindeerFrame);
  reindeerImage.copy(&game->getScreenSurface(),
      {x + static_cast<int>(sleighImage.getWidth()), y + reindeerOffsetY}, reindeerFrame);

  if (!paused) {
    for (const SleighStar& sleighStar : sleighStars) {
      sleighStar.draw();
    }
  }

  if (isShieldActivated()) {
    const size_t shieldFrame = static_cast<int>((SDL_GetTicks() - shieldEndTime) / 1000.0 *
        shieldFrameSpeed) % shieldImage.getNumberOfFrames();
    shieldImage.copy(&game->getScreenSurface(),
        {x + shieldOffsetY - static_cast<int>(shieldFrame), y + shieldOffsetY}, shieldFrame);
  }
}

void Sleigh::moveSleighStars() {
  for (SleighStar& sleighStar : sleighStars) {
    sleighStar.move();
  }
}

void Sleigh::electrify() {
  electrifiedEndTime = SDL_GetTicks() + electrifiedDuration;
  invincibleEndTime = SDL_GetTicks() + invincibleDuration;
}

void Sleigh::collideLevelObject() {
  invincibleEndTime = SDL_GetTicks() + invincibleDuration;
}

void Sleigh::collideLevel() {
  invincibleEndTime = SDL_GetTicks() + collisionInvincibleDuration;
  immobileEndTime = SDL_GetTicks() + collisionUnmovableDuration;
  speedX = 0;
  speedY = -maxMoveSpeed;
}

void Sleigh::becomeDrunk() {
  drunkEndTime = SDL_GetTicks() + drunkDuration;
}

void Sleigh::activateShield() {
  shieldEndTime = SDL_GetTicks() + shieldDuration;
}

bool Sleigh::isInvincible() const {
  return ((invincibleEndTime != 0) && (SDL_GetTicks() < invincibleEndTime));
}

bool Sleigh::isElectrified() const {
  return ((electrifiedEndTime != 0) && (SDL_GetTicks() < electrifiedEndTime));
}

bool Sleigh::isDrunk() const {
  return ((drunkEndTime != 0) && (SDL_GetTicks() < drunkEndTime));
}

bool Sleigh::isShieldActivated() const {
  return ((shieldEndTime != 0) && (SDL_GetTicks() < shieldEndTime));
}

bool Sleigh::isImmobile() const {
  return ((immobileEndTime != 0) && (SDL_GetTicks() < immobileEndTime));
}

bool Sleigh::checkCollisionLevel() {
  const int tileWidth = static_cast<int>(game->getLevel().getTileWidth());
  const int tileHeight = static_cast<int>(game->getLevel().getTileHeight());
  const int levelOffset = game->getLevel().getOffset();
  const std::vector<std::vector<size_t>>& levelMap = game->getLevel().getMap();
  const size_t offsetTileX = levelOffset / tileWidth;
  const size_t sleighFrame = getFrame();
  const size_t reindeerFrame = (sleighFrame + sleighImage.getNumberOfFrames() / 2) %
      sleighImage.getNumberOfFrames();

  for (int tileY = 0; tileY < static_cast<int>(game->getLevel().getNumberOfTilesY()); tileY++) {
    for (int tileX = static_cast<int>(offsetTileX);
        tileX < static_cast<int>(offsetTileX + game->getLevel().getNumberOfTilesPerScreenWidth());
        tileX++) {
      const size_t tileFrame = levelMap[tileY][tileX];

      if (tileFrame == 0) {
        continue;
      }

      if (sleighImage.checkCollision({x, y}, sleighFrame, &levelImage,
            {tileX * tileWidth - levelOffset, tileY * tileHeight}, tileFrame) ||
          reindeerImage.checkCollision(
            {x + static_cast<int>(sleighImage.getWidth()) + reindeerOffsetX, y},
            reindeerFrame, &levelImage,
            {tileX * tileWidth - levelOffset, tileY * tileHeight}, tileFrame)) {
        return true;
      }
    }
  }

  return false;
}

SantaRacer::LevelObject::LevelObject* Sleigh::checkCollisionLevelObject() {
  if (isInvincible()) {
    return nullptr;
  }

  const size_t sleighFrame = getFrame();
  const size_t reindeerFrame = getReindeerFrame();
  const bool shieldActivated = isShieldActivated();
  const int level_offset = game->getLevel().getOffset();

  for (std::unique_ptr<LevelObject::LevelObject>& levelObject :
      game->getLevel().getLevelObjects()) {
    if (shieldActivated && (dynamic_cast<LevelObject::Balloon*>(levelObject.get()) != nullptr)) {
      continue;
    }

    if (sleighImage.checkCollision({x, y}, sleighFrame, &levelObject->getImage(),
          {levelObject->getLevelX() - level_offset, levelObject->getY()},
          levelObject->getFrame()) ||
        sleighImage.checkCollision(
          {x + static_cast<int>(sleighImage.getWidth()) + reindeerOffsetX, y}, reindeerFrame,
          &levelObject->getImage(),
          {levelObject->getLevelX() - level_offset, levelObject->getY()},
          levelObject->getFrame())) {
      return levelObject.get();
    }
  }

  return nullptr;
}

int Sleigh::getX() const {
  if (inMenuMode) {
    return (sin(static_cast<double>(SDL_GetTicks() - time) / menuXPeriod * 2.0 * M_PI +
        menuOffsetAngleX) + 1.0) * ((maxMenuX - minMenuX) / 2.0) + minMenuX;
  } else {
    if (speedX == 0) {
      return x;
    } else {
      return std::min(std::max(x + static_cast<int>((SDL_GetTicks() - timeX) / 1000.0 * speedX), 0),
          static_cast<int>(game->getScreenWidth() - getWidth()));
    }
  }
}

int Sleigh::getY() const {
  if (inMenuMode) {
    return (sin(static_cast<float>(SDL_GetTicks() - time) / menuYPeriod * 2 * M_PI +
        menuOffsetAngleY) + 1.0) * ((maxMenuY - minMenuY) / 2.0) + minMenuY;
  } else {
    if (speedY == 0) {
      return y;
    } else {
      return std::min(std::max(y + static_cast<int>((SDL_GetTicks() - timeY) / 1000.0 * speedY), 0),
          static_cast<int>(game->getScreenHeight() - getHeight()));
    }
  }
}

int Sleigh::getSpeedX() const {
  return speedX;
}

int Sleigh::getSpeedY() const {
  return speedY;
}

size_t Sleigh::getWidth() const {
  return width;
}

size_t Sleigh::getHeight() const {
  return height;
}

size_t Sleigh::getFrame() const {
  return (paused ? frame : static_cast<int>((SDL_GetTicks() - time) / 1000.0 * frameSpeed + frame));
}

size_t Sleigh::getReindeerFrame() const {
  return getFrame() + reindeerImage.getNumberOfFrames() / 2;
}

void Sleigh::setInMenuMode(bool inMenuMode) {
  this->inMenuMode = inMenuMode;
}

void Sleigh::setX(int x) {
  this->x = x;
  speedX = 0;
}

void Sleigh::setY(int y) {
  this->y = y;
  speedY = 0;
}

void Sleigh::setSpeedX(int direction) {
  if (isImmobile()) {
    return;
  }

  if (direction == 0) {
    direction = ((speedX > 0) ? -1 : ((speedX < 0) ? 1 : 0));
  }

  x = getX();
  speedX = std::min(std::max(speedX + acceleration * direction, -maxMoveSpeed), maxMoveSpeed);
  timeX = SDL_GetTicks();
}

void Sleigh::setSpeedY(int direction) {
  if (isImmobile()) {
    return;
  }

  if (direction == 0) {
    direction = ((speedY > 0) ? -1 : ((speedY < 0) ? 1 : 0));
  }

  y = getY();
  speedY = std::min(std::max(speedY + acceleration * direction, -maxMoveSpeed), maxMoveSpeed);
  timeY = SDL_GetTicks();
}

bool Sleigh::isPaused() const {
  return paused;
}

void Sleigh::setPaused(bool paused) {
  if (paused != this->paused) {
    frame = getFrame();
    time = SDL_GetTicks();
  }

  this->paused = paused;
}

void Sleigh::setAlpha(Uint8 alpha) {
  sleighImage.setAlpha(alpha);
  reindeerImage.setAlpha(alpha);
}

}  // namespace SantaRacer
