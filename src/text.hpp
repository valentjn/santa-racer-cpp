/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

#include <SDL/SDL.h>

namespace SantaRacer {

class Text {
 public:
  enum TextAlign {
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

  Text(SDL_Surface *surface);
  void draw(const char *text, int x, int y, TextAlign align = TopLeft,
            bool monospace = false);
  int get_line_height(void);

 private:
  SDL_Surface *m_surface;

  int m_char_width;
  int m_char_height;
  int m_max_char_width;
};

}  // namespace SantaRacer
