/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

#include <string>
#include <unordered_map>

#include "SantaRacer/LevelObject/LevelObject.hpp"

namespace SantaRacer {
namespace LevelObject {

class Balloon : public LevelObject {
 public:
  enum class Type {
    Normal,
    Cash,
    Champagne,
    Gift,
    Shield,
  };

  Balloon(Game* game, size_t tileX, size_t tileY, Type type);
  ~Balloon() override;

  int getLevelX() const override;
  int getY() const override;
  size_t getFrame() const override;
  Type getType() const;

 protected:
  static const std::unordered_map<Type, std::string> imageNameMap;

  const size_t frameSpeed = 8;
  const int speed = 50;

  Type type;
  int levelX;
  int y;
  size_t frame;
  size_t time;
};

}  // namespace LevelObject
}  // namespace SantaRacer
