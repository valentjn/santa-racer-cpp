/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

#include <SDL/SDL.h>

#include <string>
#include <vector>

#include "SantaRacer/Asset/Image.hpp"

namespace SantaRacer {

class Text {
 public:
  enum class Alignment {
    TopLeft = 0,
    TopCenter = 1,
    TopRight = 2,
    CenterLeft = 3,
    Center = 4,
    CenterRight = 5,
    BottomLeft = 6,
    BottomCenter = 7,
    BottomRight = 8
  };

  Text(const Asset::Image& image, const std::vector<size_t>& actualCharWidths);

  void draw(SDL_Surface* targetSurface, Asset::Image::Point point, const std::string& text,
      Alignment align = Alignment::TopLeft, bool isMonospace = false) const;

  size_t getLineHeight() const;

 protected:
  const Asset::Image& image;
  const std::vector<size_t> actualCharWidths;
  const size_t maxActualCharWidth;
  const size_t charWidth;
  const size_t charHeight;
};

}  // namespace SantaRacer
