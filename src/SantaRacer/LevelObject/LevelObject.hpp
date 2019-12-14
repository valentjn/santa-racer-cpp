/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

#include <memory>

#include "SantaRacer/Asset/Image.hpp"

namespace SantaRacer {

class Game;

namespace LevelObject {

class LevelObject {
 public:
  LevelObject(Game* game, size_t tileX, size_t tileY, Asset::Image* image);
  virtual ~LevelObject();

  static std::unique_ptr<LevelObject> create(Game* game, size_t tileX, size_t tileY,
      size_t mapValue);

  virtual void draw();
  virtual void move();

  size_t getTileX() const;
  size_t getTileY() const;
  virtual int getLevelX() const = 0;
  virtual int getY() const = 0;
  virtual size_t getFrame() const = 0;

  bool isVisible() const;
  void setVisible(bool visible);

  Asset::Image* getImage();

 protected:
  Game *game;
  Asset::Image* image;

  int tileX;
  int tileY;
  bool visible;
};

}  // namespace LevelObject
}  // namespace SantaRacer
