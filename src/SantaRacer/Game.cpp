/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include <algorithm>
#include <fstream>
#include <iterator>
#include <memory>
#include <string>
#include <utility>
#include <vector>

#include "SantaRacer/Game.hpp"
#include "SantaRacer/Printer.hpp"
#include "SantaRacer/LevelObject/Angel.hpp"
#include "SantaRacer/LevelObject/Balloon.hpp"
#include "SantaRacer/LevelObject/Cloud.hpp"
#include "SantaRacer/LevelObject/Finish.hpp"
#include "SantaRacer/LevelObject/Goblin.hpp"
#include "SantaRacer/LevelObject/GoblinSnowball.hpp"
#include "SantaRacer/LevelObject/LevelObject.hpp"
#include "SantaRacer/LevelObject/Snowman.hpp"

namespace SantaRacer {

Game::Game(Options&& options) : options(std::move(options)),
      screenWidth(640), screenHeight(480), targetFps(30) {
#ifdef NDEBUG
  Printer::setVerbose(options.isVerbose());
#endif

  if (SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO) < 0) {
    Printer::fatalError("unable to initalize SDL: %s\n", SDL_GetError());
  }

  SDL_WM_SetCaption("Santa Racer", "Santa Racer");
  SDL_ShowCursor(SDL_DISABLE);
  SDL_EnableUNICODE(1);

  Uint32 flags = SDL_DOUBLEBUF | SDL_RESIZABLE;

  if (options.isFullScreen()) {
    flags |= SDL_FULLSCREEN;
  }

  screenSurface = SDL_SetVideoMode(screenWidth, screenHeight, 16, flags);

  if (options.isSoundEnabled()) {
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 1024) == -1) {
      Printer::fatalError("unable to initialize SDL_Mixer: %s\n", Mix_GetError());
    }
    Mix_AllocateChannels(numberOfChannels);
  }

  dataLibrary.loadAssets();
  imageLibrary.loadAssets();

  if (options.isSoundEnabled()) {
    soundLibrary.loadAssets();
    musicLibrary.loadAssets();
  } else {
    soundLibrary.setEnabled(false);
    musicLibrary.setEnabled(false);
  }

  loadText();
  loadChimneys();

  SDL_WM_SetIcon(&imageLibrary.getAsset("icon").getSurface(), nullptr);

  SDL_Surface* highscoreBackgroundSurface =
      SDL_CreateRGBSurface(SDL_SWSURFACE, 400, 300, 32, 0, 0, 0, 0);

  if (highscoreBackgroundSurface == nullptr) {
    Printer::fatalError("could not create RGB surface: %s\n", SDL_GetError());
  }

  SDL_SetAlpha(highscoreBackgroundSurface, SDL_SRCALPHA, 128);
  highscoreBackground = Asset::Image(highscoreBackgroundSurface);

  rng.seed();
  Printer::debug("initializing game\n");
  initialize();

  musicLibrary.getAsset("bgmusic").play();
}

Game::~Game() {
  if (options.isSoundEnabled()) {
    Printer::debug("closing audio\n");
    Mix_CloseAudio();
  }

  Printer::debug("quitting sdl\n");
  SDL_Quit();
}

void Game::loadText() {
  const std::vector<double> data = dataLibrary.getAsset("char_widths");
  const std::vector<size_t> textCharWidths(data.begin(), data.end());

  if (textCharWidths.size() != 96) {
    Printer::fatalError("invalid format of char_widths.txt, expected 96 values\n");
  }

  text.reset(new Text(imageLibrary.getAsset("font"), textCharWidths));
}

void Game::loadChimneys() {
  const std::vector<double> data = dataLibrary.getAsset("chimneys");

  if (data.size() % 4 != 0) {
    Printer::fatalError("invalid format of chimneys.txt, expected size divisible by 4\n");
  }

  for (size_t i = 0; i < data.size() / 4; i++) {
    const int mapIndex = data[4 * i];
    const int x = data[4 * i + 1];
    const int width = data[4 * i + 2];
    const int y = data[4 * i + 3];
    chimneys.emplace_back(mapIndex, x, width, y);
  }
}

void Game::playSoundAtPosition(const Asset::Sound& sound, int x) const {
  const double pan = std::min(std::max(
      static_cast<double>(x) / static_cast<double>(screenWidth), 0.0), 1.0);
  sound.playPannedWithVolume(pan, 1.0);
}

void Game::initialize() {
  lastTime = 0;

  landscape.reset(new Landscape(this));
  level.reset(new Level(this, dataLibrary.getAsset("level"), dataLibrary.getAsset("level_objects"),
      defaultLevelHeight));
  sleigh.reset(new Sleigh(this));
  score.reset(new Score(this));

  sleigh->initializeSleighStars();
  snowflakes.clear();

  for (size_t i = 0; i < numberOfSnowflakes; i++) {
    snowflakes.emplace_back(this);
  }

  quitFlag = false;
  firePressed = false;
  upPressed = false;
  downPressed = false;
  leftPressed = false;
  rightPressed = false;
  escapePressed = false;

  mode = Mode::Menu;
  fps = 0;
  lastFpsUpdateTime = 0;
  frameCounter = 0;

  keyState = SDL_GetKeyState(nullptr);

  countdownMode = false;
  countdownStartTime = 0;

  bellTime = SDL_GetTicks() + rng.getInteger(minBellTime, maxBellTime);
  dogTime = SDL_GetTicks() + rng.getInteger(minDogTime, maxDogTime);

  bonusTimeStart = 0;

  lastGiftTime = 0;

  highscore = {"", 0};
  highscorePlace = 0;
  highscoreCaretBlinkTime = 0;

  initialized = true;
}

void Game::loop() {
  while (!quitFlag) {
    processEvents();
    check_keys();
    logic();
    draw();
    frameTick();
  }
}

void Game::processEvents() {
  SDL_Event event;
  char ch;

  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      quitFlag = true;
      break;
    } else if (event.key.type == SDL_KEYDOWN) {
      if (mode == Mode::NewHighscore) {
        if ((event.key.keysym.sym == SDLK_BACKSPACE) ||
            (event.key.keysym.sym == SDLK_DELETE)) {
          if (highscore.name.length() > 0) {
            highscore.name =
                highscore.name.erase(highscore.name.length() - 1);
            highscoreCaretBlinkTime = SDL_GetTicks();
          }
        } else if (event.key.keysym.sym == SDLK_RETURN) {
          options.getHighscores()[highscorePlace].name = highscore.name;
          returnToMenu();
          mode = Mode::Highscores;

        } else if ((event.key.keysym.unicode & 0xff80) == 0) {
          ch = event.key.keysym.unicode & 0x7f;

          if (((ch >= 65) && (ch <= 90)) || ((ch >= 97) && (ch <= 120)) ||
              ((ch >= 48) && (ch <= 57)) || (ch == 64) || (ch == 95) ||
              (ch == 45) || (ch == 46) || (ch == 47) || (ch == 58)) {
            if (highscore.name.length() < maxHighscoreNameLength) {
              highscore.name += event.key.keysym.unicode;
              highscoreCaretBlinkTime = SDL_GetTicks();
            }
          }
        }
      }
    }
  }
}

void Game::check_keys() {
  const SDLMod modState = SDL_GetModState();

  if (keyState[SDLK_c] && (modState & KMOD_CTRL)) {
    quitFlag = true;
  } else if (modState & KMOD_CTRL && modState & KMOD_ALT && keyState[SDLK_RETURN]) {
    if (!SDL_WM_ToggleFullScreen(screenSurface)) {
      Printer::fatalError("could not toggle fullscreen mode: %s\n", SDL_GetError());
    }
  }

  if (mode == Mode::Menu) {
    if (keyState[SDLK_F1]) {
      mode = Mode::HelpPage1;
    } else if (keyState[SDLK_F2]) {
      mode = Mode::HelpPage2;
    } else if (keyState[SDLK_F3]) {
      mode = Mode::Highscores;
    } else if (keyState[SDLK_F5]) {
      startNewGame();
    } else if (keyState[SDLK_ESCAPE] && !escapePressed) {
      quitFlag = true;
    }

  } else if (mode == Mode::HelpPage1 || mode == Mode::HelpPage2) {
    if (keyState[SDLK_F1]) {
      mode = Mode::HelpPage1;
    } else if (keyState[SDLK_F2]) {
      mode = Mode::HelpPage2;
    } else if (keyState[SDLK_SPACE] || (keyState[SDLK_ESCAPE] && !escapePressed)) {
      mode = Mode::Menu;
    }

  } else if (mode == Mode::Highscores) {
    if (keyState[SDLK_F1]) {
      mode = Mode::HelpPage1;
    } else if (keyState[SDLK_F2]) {
      mode = Mode::HelpPage2;
    } else if (keyState[SDLK_SPACE] || (keyState[SDLK_ESCAPE] && !escapePressed)) {
      mode = Mode::Menu;
    }

  } else if ((mode == Mode::Running) && !countdownMode) {
    const int drunkFactor = (sleigh->isDrunk() ? -1 : 1);

    if (keyState[SDLK_UP]) {
      sleigh->setSpeedY(drunkFactor * -1);
    } else if (keyState[SDLK_DOWN]) {
      sleigh->setSpeedY(drunkFactor * 1);
    } else {
      sleigh->setSpeedY(0);
    }
    if (keyState[SDLK_LEFT]) {
      sleigh->setSpeedX(drunkFactor * -1);
    } else if (keyState[SDLK_RIGHT]) {
      sleigh->setSpeedX(drunkFactor * 1);
    } else {
      sleigh->setSpeedX(0);
    }
    if (keyState[SDLK_SPACE] && !firePressed &&
        (lastGiftTime + giftWaitDuration < SDL_GetTicks()) &&
        !sleigh->isImmobile()) {
      gifts.emplace_back(new Gift(this));
      lastGiftTime = SDL_GetTicks();
    }

    if (keyState[SDLK_ESCAPE] && !escapePressed) {
      returnToMenu();
    }
  }

  leftPressed = keyState[SDLK_LEFT];
  rightPressed = keyState[SDLK_RIGHT];
  upPressed = keyState[SDLK_UP];
  downPressed = keyState[SDLK_DOWN];
  firePressed = keyState[SDLK_SPACE];
  escapePressed = keyState[SDLK_ESCAPE];
}

void Game::logic() {
  if (mode == Mode::Running) {
    if (sleigh->checkCollisionLevel()) {
      Printer::debug("collision detected: %i\n", SDL_GetTicks());
      sleigh->collideLevel();
      score->addDamagePoints(collisionDamage);
      landscape->setPaused(true);
      level->setPaused(true);
      sleigh->setPaused(true);
      playSoundAtPosition(soundLibrary.getAsset((rng.getInteger(0, 1) == 0) ?
          "damaged1" : "damaged2"), sleigh->getX());
    }

    LevelObject::LevelObject* levelObject = sleigh->checkCollisionLevelObject();

    if (levelObject != nullptr) {
      const int x = levelObject->getLevelX() - level->getOffset();

      if (dynamic_cast<LevelObject::Cloud*>(levelObject) != nullptr) {
        Printer::debug("touched cloud: %i\n", SDL_GetTicks());
        score->addDamagePoints(collisionDamage);
        playSoundAtPosition(soundLibrary.getAsset("electrified"), x);
        sleigh->electrify();

      } else if (dynamic_cast<LevelObject::Balloon*>(levelObject) != nullptr) {
        const LevelObject::Balloon::Type Type =
            dynamic_cast<LevelObject::Balloon*>(levelObject)->getType();

        if (Type == LevelObject::Balloon::Type::Normal) {
          score->addGiftPoints(normalBalloonPoints);
          playSoundAtPosition(soundLibrary.getAsset("success"), x);

        } else if (Type == LevelObject::Balloon::Type::Cash) {
          score->addDamagePoints(-cashBalloonPoints);
          playSoundAtPosition(soundLibrary.getAsset("cash"), x);

        } else if (Type == LevelObject::Balloon::Type::Gift) {
          bonusTimeStart = SDL_GetTicks();
          playSoundAtPosition(soundLibrary.getAsset("bonus"), x);

        } else if (Type == LevelObject::Balloon::Type::Shield) {
          sleigh->activateShield();
          playSoundAtPosition(soundLibrary.getAsset("shield"), x);

        } else if (Type == LevelObject::Balloon::Type::Champagne) {
          sleigh->becomeDrunk();
          playSoundAtPosition(soundLibrary.getAsset("drunk"), x);
        }

        levelObject->setVisible(false);

      } else if ((dynamic_cast<LevelObject::Angel*>(levelObject) != nullptr) ||
                 (dynamic_cast<LevelObject::Goblin*>(levelObject) != nullptr) ||
                 (dynamic_cast<LevelObject::GoblinSnowball*>(levelObject) != nullptr) ||
                 (dynamic_cast<LevelObject::Snowman*>(levelObject) != nullptr)) {
        score->addDamagePoints(collisionDamage);
        playSoundAtPosition(soundLibrary.getAsset("hit"), x);
        sleigh->collideLevelObject();
      }
    }

    if (score->getRemainingTime() <= 0) {
      mode = Mode::LostDueToTime;
      wonLostTime = SDL_GetTicks();
      soundLibrary.getAsset("lost").play();
      return;
    }

    if (score->getDamagePoints() > maxDamage) {
      mode = Mode::LostDueToDamage;
      wonLostTime = SDL_GetTicks();
      soundLibrary.getAsset("lost").play();
      return;
    }
  } else if (mode == Mode::Won) {
    std::vector<Options::Highscore>& highscores = options.getHighscores();

    if (wonLostTime + wonSplashDuration <= SDL_GetTicks()) {
      for (size_t i = 0; i < 10; i++) {
        if (highscore.score > highscores[i].score) {
          mode = Mode::NewHighscore;
          highscorePlace = i;
          highscoreCaretBlinkTime = SDL_GetTicks();
          break;
        }
      }

      if (mode == Mode::NewHighscore) {
        for (int i = 9; i > static_cast<int>(highscorePlace); i--) {
          highscores[i] = highscores[i - 1];
        }

        highscores[highscorePlace].name = "";
        highscores[highscorePlace].score = highscore.score;
      } else {
        returnToMenu();
        mode = Mode::Highscores;
      }
    }

    return;
  } else if ((mode == Mode::LostDueToTime) || (mode == Mode::LostDueToDamage)) {
    if (wonLostTime + lostSplashDuration <= SDL_GetTicks()) {
      returnToMenu();
    }

    return;
  }

  for (Snowflake& snowflake : snowflakes) {
    snowflake.move();
  }

  for (std::unique_ptr<Gift>& gift : gifts) {
    gift->move();
    const int x = gift->getLevelX() - level->getOffset();

    if (gift->checkCollisionWithGround()) {
      score->addDamagePoints(droppedGiftDamage);
      playSoundAtPosition(soundLibrary.getAsset("gift_missed"), x);

    } else if (gift->checkCollisionWithChimney()) {
      int points = gift->getGiftPoints();

      if ((bonusTimeStart != 0) &&
          (bonusTimeStart + bonusDuration > SDL_GetTicks())) {
        points *= 2;
        gift->activateDoublePoints();
      }

      score->addGiftPoints(points);
      playSoundAtPosition(soundLibrary.getAsset("success"), x);
    }
  }

  {
    auto it = gifts.begin();

    while (it != gifts.end()) {
      if ((*it)->shouldBeDeleted()) {
        it = gifts.erase(it);
      } else {
        ++it;
      }
    }
  }

  landscape->move();
  level->move();
  level->moveObjects();
  sleigh->moveSleighStars();

  if (countdownMode) {
    const int countdownNumber = countdownStart -
        (static_cast<int>(SDL_GetTicks()) - countdownStartTime) / 1000;

    if (countdownNumber <= 0) {
      countdownMode = false;
      landscape->setPaused(false);
      level->setPaused(false);
      sleigh->setPaused(false);
      sleigh->setAlpha(255);
    }

    score->initialize(totalTimeSecs);
  }

  if (sleigh->isPaused() && !sleigh->isImmobile()) {
    landscape->setPaused(false);
    level->setPaused(false);
    sleigh->setPaused(false);
  }

  for (std::unique_ptr<LevelObject::LevelObject>& levelObject : level->getLevelObjects()) {
    if ((dynamic_cast<LevelObject::Goblin*>(levelObject.get()) != nullptr) &&
        dynamic_cast<LevelObject::Goblin*>(levelObject.get())->checkSpawnSnowball()) {
      level->getLevelObjects().emplace_back(new LevelObject::GoblinSnowball(
          this, levelObject->getTileX(), levelObject->getTileY()));
      playSoundAtPosition(soundLibrary.getAsset("snowball"),
          levelObject->getLevelX() - level->getOffset());
    } else if ((dynamic_cast<LevelObject::Snowman*>(levelObject.get()) != nullptr) &&
        dynamic_cast<LevelObject::Snowman*>(levelObject.get())->checkTriggered()) {
      playSoundAtPosition(soundLibrary.getAsset("snowman"),
          levelObject->getLevelX() - level->getOffset());
    } else if ((dynamic_cast<LevelObject::Finish*>(levelObject.get()) != nullptr) &&
               dynamic_cast<LevelObject::Finish*>(levelObject.get())->checkReached() &&
               ((mode == Mode::Running) || (mode == Mode::Menu))) {
      if (mode == Mode::Running) {
        mode = Mode::Won;
        wonLostTime = SDL_GetTicks();
        highscore.score = score->getScore();
        soundLibrary.getAsset("won").play();

        return;
      } else {
        returnToMenu();
      }
    }
  }

  if (SDL_GetTicks() >= bellTime) {
    soundLibrary.getAsset("bell").playWithVolume(bellVolume);
    bellTime = SDL_GetTicks() + rng.getInteger(minBellTime, maxBellTime);
  }

  if (SDL_GetTicks() >= dogTime) {
    soundLibrary.getAsset("dog").playWithVolume(dogVolume);
    dogTime = SDL_GetTicks() + rng.getInteger(minDogTime, maxDogTime);
  }
}

void Game::draw() {
  if (mode == Mode::HelpPage1) {
    imageLibrary.getAsset("help1").copy(screenSurface, {0, 0});

  } else if (mode == Mode::HelpPage2) {
    imageLibrary.getAsset("help2").copy(screenSurface, {0, 0});

  } else if (mode == Mode::Won) {
    imageLibrary.getAsset("finished").copy(screenSurface, {0, 0});

  } else if (mode == Mode::NewHighscore) {
    imageLibrary.getAsset("finished").copy(screenSurface, {0, 0});
    drawHighscores();

  } else if (mode == Mode::LostDueToTime) {
    imageLibrary.getAsset("lost_time").copy(screenSurface, {0, 0});

  } else if (mode == Mode::LostDueToDamage) {
    imageLibrary.getAsset("lost_damage").copy(screenSurface, {0, 0});

  } else {
    imageLibrary.getAsset("bg").copy(screenSurface, {0, 0});
    landscape->draw();
    level->drawBallons();
    level->draw();
    sleigh->draw();
    level->drawObjects();

    for (const std::unique_ptr<Gift>& gift : gifts) {
      gift->draw();
    }

    SDL_LockSurface(screenSurface);

    for (const Snowflake& snowflake : snowflakes) {
      snowflake.draw();
    }

    SDL_UnlockSurface(screenSurface);

    drawText();

    if (mode == Mode::Highscores) {
      drawHighscores();
    }
  }

#ifndef NDEBUG
  text->draw(screenSurface, {static_cast<int>(screenWidth), static_cast<int>(screenHeight)},
      Printer::printToString("%u FPS", fps), Text::Alignment::BottomRight);
#endif

  if ((mode == Mode::Menu) || (mode == Mode::Highscores)) {
    const Asset::Image& logo = imageLibrary.getAsset("logo");
    logo.copy(screenSurface, {0, static_cast<int>(screenHeight - logo.getHeight())});
  }

  SDL_Flip(screenSurface);
}

void Game::frameTick() {
  const size_t currentTime = SDL_GetTicks();

  if (lastFpsUpdateTime + 1000 < currentTime) {
    fps = (frameCounter * 1000) / (currentTime - lastFpsUpdateTime);
    // debug("%i", frame_counter);
    lastFpsUpdateTime = currentTime;
    frameCounter = 0;
  }

  fpsDelay();
  frameCounter++;
}

void Game::fpsDelay() {
  const int currentTime = SDL_GetTicks();

  if (lastTime != 0) {
    const int currentFrameTime = currentTime - lastTime;
    // cur_fps = 1000.0 / cur_delay;
    const double targetFrameTime = 1000.0 / targetFps;

    if (currentFrameTime < targetFrameTime) {
      SDL_Delay(static_cast<int>((targetFrameTime - currentFrameTime)));
    }
  }

  lastTime = currentTime;
}

void Game::startNewGame() {
  mode = Mode::Running;

  countdownMode = true;
  countdownStartTime = SDL_GetTicks();

  sleigh->initialize();
  sleigh->initializeSleighStars();
  sleigh->setInMenuMode(false);
  sleigh->setAlpha(128);
  sleigh->setX(sleighStartX);
  sleigh->setY(sleighStartY);
  sleigh->setPaused(true);

  level->setInMenuMode(false);
  level->setOffset(0);
  level->setPaused(true);
  level->clearObjects();

  landscape->initialize();
  landscape->setPaused(true);

  sleigh->initializeSleighStars();

  for (Snowflake& snowflake : snowflakes) {
    snowflake.initialize();
  }

  gifts.clear();
  score->initialize(totalTimeSecs);
}

void Game::returnToMenu() {
  mode = Mode::Menu;

  countdownMode = false;

  sleigh->initialize();
  sleigh->initializeSleighStars();
  sleigh->setInMenuMode(true);

  level->setInMenuMode(true);
  level->setOffset(0);
  level->setPaused(false);
  level->clearObjects();

  landscape->initialize();
  landscape->setPaused(false);

  sleigh->initializeSleighStars();

  for (Snowflake& snowflake : snowflakes) {
    snowflake.initialize();
  }

  gifts.clear();
}

void Game::drawText() {
  if (mode == Mode::Menu || mode == Mode::Highscores) {
    text->draw(screenSurface, {0, 0}, "F1/F2 - Hilfe", Text::Alignment::TopLeft);
    text->draw(screenSurface, {static_cast<int>(screenWidth / 2), 0}, "F3 - Highscores",
        Text::Alignment::TopCenter);
    text->draw(screenSurface, {static_cast<int>(screenWidth), 0}, "F5 - Spielen",
        Text::Alignment::TopRight);
  } else {
    score->draw();

    if (countdownMode) {
      const int countdownNumber = std::max(static_cast<size_t>(1),
          countdownStart - (SDL_GetTicks() - countdownStartTime) / 1000);
      text->draw(screenSurface,
          {sleigh->getX() - 10, sleigh->getY() + static_cast<int>(sleigh->getHeight() / 2)},
          Printer::printToString("%i", countdownNumber), Text::Alignment::CenterRight);
    }
  }
}

void Game::drawHighscores() {
  int x = screenWidth / 2 - highscoreWidth / 2;
  int y = screenHeight / 2 - highscoreHeight / 2;
  const size_t lineSpacing =
      (highscoreHeight - text->getLineHeight() - 2 * highscorePaddingY) / 9;

  highscoreBackground.blit({0, 0, highscoreWidth, highscoreHeight}, screenSurface, {x, y});

  x += highscorePaddingX;
  y += highscorePaddingY;

  for (size_t i = 0; i < 10; i++) {
    std::string name;

    if ((mode == Mode::NewHighscore) && (i == highscorePlace)) {
      if ((SDL_GetTicks() - highscoreCaretBlinkTime) % (2 * highscoreCaretBlinkDuration) <
          highscoreCaretBlinkDuration) {
        name = highscore.name + "_";
      } else {
        name = highscore.name;
      }
    } else {
      name = options.getHighscores()[i].name;
    }

    text->draw(screenSurface, {x, y}, name, Text::Alignment::TopLeft);
    text->draw(screenSurface,
        {x + static_cast<int>(highscoreWidth) - static_cast<int>(2 * highscorePaddingX), y},
        Printer::printToString("%i", options.getHighscores()[i].score), Text::Alignment::TopRight);

    y += lineSpacing;
  }
}

Asset::ImageLibrary& Game::getImageLibrary() {
  return imageLibrary;
}

Asset::MusicLibrary& Game::getMusicLibrary() {
  return musicLibrary;
}

Asset::SoundLibrary& Game::getSoundLibrary() {
  return soundLibrary;
}

Text& Game::getText() const {
  return *text;
}

size_t Game::getScreenWidth() const {
  return screenWidth;
}

size_t Game::getScreenHeight() const {
  return screenHeight;
}

SDL_Surface& Game::getScreenSurface() const {
  return *screenSurface;
}

size_t Game::getTargetFps() const {
  return targetFps;
}

Options& Game::getOptions() {
  return options;
}

RNG& Game::getRNG() {
  return rng;
}

Level& Game::getLevel() {
  return *level;
}

Sleigh& Game::getSleigh() {
  return *sleigh;
}

const std::vector<Chimney>& Game::getChimneys() const {
  return chimneys;
}

}  // namespace SantaRacer
