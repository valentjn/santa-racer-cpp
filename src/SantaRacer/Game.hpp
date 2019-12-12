/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

#include <SDL/SDL.h>

#include <memory>
#include <vector>

#include "SantaRacer/Chimney.hpp"
#include "SantaRacer/Gift.hpp"
#include "SantaRacer/Landscape.hpp"
#include "SantaRacer/Level.hpp"
#include "SantaRacer/Options.hpp"
#include "SantaRacer/RNG.hpp"
#include "SantaRacer/Score.hpp"
#include "SantaRacer/Sleigh.hpp"
#include "SantaRacer/Snowflake.hpp"
#include "SantaRacer/Text.hpp"
#include "SantaRacer/Asset/DataLibrary.hpp"
#include "SantaRacer/Asset/ImageLibrary.hpp"
#include "SantaRacer/Asset/MusicLibrary.hpp"
#include "SantaRacer/Asset/Sound.hpp"
#include "SantaRacer/Asset/SoundLibrary.hpp"

namespace SantaRacer {

class Game {
 public:
  enum class Mode {
    Menu,
    HelpPage1,
    HelpPage2,
    Highscores,
    Running,
    Won,
    LostDueToTime,
    LostDueToDamage,
    NewHighscore,
  };

  explicit Game(Options&& options);
  Game(const Game& other) = delete;
  ~Game();

  void initialize();

  void loop();
  void processEvents();
  void check_keys();
  void logic();
  void draw();
  void frameTick();
  void fpsDelay();

  void startNewGame();
  void returnToMenu();

  void drawText();
  void drawHighscores();

  Asset::ImageLibrary& getImageLibrary();
  Asset::MusicLibrary& getMusicLibrary();
  Asset::SoundLibrary& getSoundLibrary();
  Text& getText() const;

  size_t getScreenWidth() const;
  size_t getScreenHeight() const;
  SDL_Surface& getScreenSurface() const;
  size_t getTargetFps() const;

  Options& getOptions();
  RNG& getRNG();
  Level& getLevel();
  Sleigh& getSleigh();
  const std::vector<Chimney>& getChimneys() const;

 protected:
  void loadText();
  void loadChimneys();
  void playSoundAtPosition(const Asset::Sound& sound, int x) const;

  Options options;
  RNG rng;
  SDL_Surface *screenSurface;

  Asset::DataLibrary dataLibrary;
  Asset::ImageLibrary imageLibrary;
  Asset::MusicLibrary musicLibrary;
  Asset::SoundLibrary soundLibrary;
  std::unique_ptr<Text> text;

  size_t screenWidth;
  size_t screenHeight;
  size_t targetFps;

  const size_t numberOfChannels = 64;
  const size_t defaultLevelHeight = 5;

  std::unique_ptr<Landscape> landscape;
  std::vector<Snowflake> snowflakes;
  std::unique_ptr<Level> level;
  std::unique_ptr<Sleigh> sleigh;
  std::vector<std::unique_ptr<Gift>> gifts;
  std::vector<Chimney> chimneys;
  std::unique_ptr<Score> score;

  Mode mode;
  size_t fps;

  bool countdownMode;
  size_t countdownStartTime;

  const size_t highscoreWidth = 400;
  const size_t highscoreHeight = 300;
  const size_t highscorePaddingX = 10;
  const size_t highscorePaddingY = 10;

  const size_t countdownStart = 3;

  const int sleighStartX = 50;
  const int sleighStartY = 100;

  const int hitDamage = 20;
  const int collisionDamage = 50;
  const int droppedGiftDamage = 15;
  const int maxDamage = 300;

  const size_t totalTimeSecs = 450;

  const int normalBalloonPoints = 20;
  const int cashBalloonPoints = 50;

  const size_t bonusDuration = 15000;

  const size_t numberOfSnowflakes = 1200;

  const size_t minBellTime = 10000;
  const size_t maxBellTime = 20000;
  const double bellVolume = 0.5;

  const size_t minDogTime = 10000;
  const size_t maxDogTime = 20000;
  const double dogVolume = 0.5;

  const size_t giftWaitDuration = 250;

  const size_t wonSplashDuration = 5000;
  const size_t lostSplashDuration = 5000;

  const size_t highscoreCaretBlinkDuration = 500;
  const size_t maxHighscoreNameLength = 16;

  Asset::Image highscoreBackground;
  bool initialized;

  Uint8 *keyState;
  bool firePressed;
  bool upPressed;
  bool downPressed;
  bool leftPressed;
  bool rightPressed;
  bool escapePressed;

  bool quitFlag;

  size_t lastFpsUpdateTime;
  size_t frameCounter;
  size_t lastTime;

  size_t bellTime;
  size_t dogTime;

  size_t bonusTimeStart;

  size_t lastGiftTime;

  size_t wonLostTime;

  Options::Highscore highscore;
  size_t highscorePlace;
  size_t highscoreCaretBlinkTime;
};

}  // namespace SantaRacer
