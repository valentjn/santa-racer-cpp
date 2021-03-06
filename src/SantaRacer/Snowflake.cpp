/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include <SDL2/SDL.h>

#include <algorithm>

#include "SantaRacer/Game.hpp"
#include "SantaRacer/RNG.hpp"
#include "SantaRacer/Snowflake.hpp"

namespace SantaRacer {

Snowflake::Snowflake(Game* game) : game(game) {
  initialize(false);
}

void Snowflake::initialize(bool putOnTop) {
  levelX = game->getRNG().getInteger(leftMargin, 2 * game->getScreenWidth()) +
      game->getLevel().getOffset();
  y = (putOnTop ? 0.0 : game->getRNG().getInteger(0, game->getScreenHeight()));
  brightness = game->getRNG().getInteger(0, 255);
  time = SDL_GetTicks();
  speedX = game->getRNG().getInteger(minSpeedX, maxSpeedX);
  speedY = game->getRNG().getInteger(minSpeedY, maxSpeedY);
  speedChangeTime = SDL_GetTicks() +
      game->getRNG().getInteger(minSpeedChangeTime, maxSpeedChangeTime);
}

void Snowflake::draw() {
  const int x = getLevelX() - game->getLevel().getOffset();
  const int y = getY();

  if ((x >= 0) && (x < static_cast<int>(game->getScreenWidth())) && (y >= 0) &&
      (y < static_cast<int>(game->getScreenHeight()))) {
    SDL_Renderer* renderer = game->getRenderer();
    SDL_SetRenderDrawColor(renderer, brightness, brightness, brightness, SDL_ALPHA_OPAQUE);
    SDL_RenderDrawPoint(renderer, x, y);
  }
}

void Snowflake::move() {
  const int currentLevelX = getLevelX();
  const int currentY = getY();

  if ((currentY >= static_cast<int>(game->getScreenHeight())) ||
      (currentLevelX - game->getLevel().getOffset() < leftMargin)) {
    initialize(true);
  } else if (SDL_GetTicks() > speedChangeTime) {
    levelX = currentLevelX;
    y = currentY;
    time = SDL_GetTicks();
    changeSpeed();
  }
}

void Snowflake::changeSpeed() {
  speedX = std::min(std::max(speedX + game->getRNG().getInteger(-10, 10), minSpeedX), maxSpeedX);
  speedY = std::min(std::max(speedY + game->getRNG().getInteger(-10, 10), minSpeedY), maxSpeedY);
  speedChangeTime = SDL_GetTicks() + game->getRNG().getInteger(minSpeedChangeTime,
      maxSpeedChangeTime);
}

double Snowflake::getLevelX() const {
  return levelX + speedX * ((SDL_GetTicks() - time) / 1000.0);
}

double Snowflake::getY() const {
  return y + speedY * (SDL_GetTicks() - time) / 1000.0;
}

}  // namespace SantaRacer
