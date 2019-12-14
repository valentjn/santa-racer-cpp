/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include <SDL/SDL.h>

#include <algorithm>

#include "SantaRacer/Game.hpp"
#include "SantaRacer/Printer.hpp"
#include "SantaRacer/Score.hpp"

namespace SantaRacer {

Score::Score(Game *game) : game(game),
    scoreGiftImage(game->getImageLibrary().getAsset("score_gift")),
    scoreDamageImage(game->getImageLibrary().getAsset("score_damage")),
    scoreTimeImage(game->getImageLibrary().getAsset("score_time")),
    giftPoints(0), damagePoints(0), timeStart(0), totalTime(0) {
}

void Score::initialize(int totalTime) {
  giftPoints = 0;
  damagePoints = 0;
  resetClock(totalTime);
}

void Score::draw() const {
  const int y = static_cast<int>(scoreGiftImage.getHeight()) / 2;

  scoreGiftImage.copy(&game->getScreenSurface(), {0, 0});
  game->getText().draw(&game->getScreenSurface(), {40, y},
      Printer::printToString("%i", giftPoints), Text::Alignment::CenterLeft, true);

  scoreDamageImage.copy(&game->getScreenSurface(), {150, 0});
  game->getText().draw(&game->getScreenSurface(), {190, y},
      ((damagePoints == 0) ? "0" : Printer::printToString("%i", -damagePoints)),
      Text::Alignment::CenterLeft, true);

  size_t seconds = getRemainingTime();
  const size_t minutes = seconds / 60;
  seconds %= 60;

  scoreTimeImage.copy(&game->getScreenSurface(), {520, 0});
  game->getText().draw(&game->getScreenSurface(), {560, y},
      Printer::printToString("%i:%02i", minutes, seconds), Text::Alignment::CenterLeft, true);
}

int Score::getGiftPoints() const {
  return giftPoints;
}

void Score::setGiftPoints(int giftPoints) {
  this->giftPoints = giftPoints;
}

void Score::addGiftPoints(int giftPoints) {
  this->giftPoints += giftPoints;
}

int Score::getDamagePoints() const {
  return damagePoints;
}

void Score::setDamagePoints(int damagePoints) {
  this->damagePoints = damagePoints;
}

void Score::addDamagePoints(int damagePoints) {
  this->damagePoints = std::max(this->damagePoints + damagePoints, 0);
}

int Score::getRemainingTime() const {
  if (timeStart == 0) {
    return totalTime;
  } else {
    return totalTime - (SDL_GetTicks() - timeStart) / 1000;
  }
}

void Score::addToRemainingTime(int time) {
  timeStart += time * 1000;
}

void Score::resetClock(int totalTime) {
  timeStart = SDL_GetTicks();
  this->totalTime = totalTime;
}

int Score::getScore() const {
  return scorePointsPerGiftPoint * getGiftPoints() + scorePointsPerDamagePoint * getDamagePoints() +
      scorePointsPerRemainingTime * getRemainingTime();
}

}  // namespace SantaRacer
