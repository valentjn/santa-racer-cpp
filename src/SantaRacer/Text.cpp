/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include <SDL/SDL.h>

#include <algorithm>
#include <string>
#include <vector>

#include "SantaRacer/Text.hpp"

namespace SantaRacer {

Text::Text(const Asset::Image& image, const std::vector<size_t>& actualCharWidths) :
    image(image), actualCharWidths(actualCharWidths),
    maxActualCharWidth(*std::max_element(actualCharWidths.begin(), actualCharWidths.end())),
    charWidth(image.getWidth() / 16),
    charHeight(image.getHeight() / 6) {
}

void Text::draw(SDL_Surface* targetSurface, Asset::Image::Point targetPoint,
    const std::string& text, Alignment alignment, bool isMonospace) const {
  size_t width;

  if (isMonospace) {
    width = text.size() * maxActualCharWidth;
  } else {
    width = 0;

    for (const char ch : text) {
      width += actualCharWidths[ch - 32];
    }
  }

  targetPoint.x -= (static_cast<size_t>(alignment) % 3) * (width / 2);
  targetPoint.y -= (static_cast<size_t>(alignment) / 3) * (charHeight / 2);

  for (const char ch : text) {
    const size_t actualCharWidth = actualCharWidths[ch - 32];

    Asset::Image::Rectangle sourceRectangle;
    sourceRectangle.x = (ch % 16) * charWidth;
    sourceRectangle.y = (ch / 16 - 2) * charHeight;
    sourceRectangle.w = charWidth;
    sourceRectangle.h = charHeight;

    if (isMonospace) {
      targetPoint.x += maxActualCharWidth / 2 - actualCharWidth / 2;
    }

    image.blit(sourceRectangle, targetSurface, targetPoint);

    if (isMonospace) {
      targetPoint.x += maxActualCharWidth;
    } else {
      targetPoint.x += actualCharWidth;
    }
  }
}

size_t Text::getLineHeight() const {
  return charHeight;
}

}  // namespace SantaRacer
