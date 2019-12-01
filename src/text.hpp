/*
 *      Santa Racer
 *      text.hpp
 *
 *      Copyright (C) 2010 Julian Valentin.
 *
 *      This program is free software: you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation, either version 3 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#ifndef SANTA_TEXT_H
#define SANTA_TEXT_H

#include <SDL/SDL.h>

namespace Santa {

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

}  // namespace Santa

#endif
