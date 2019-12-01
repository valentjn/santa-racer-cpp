/*
 *      Santa Racer
 *      text.cpp
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

#include "text.hpp"

#include "globals.hpp"

Santa::Text::Text(SDL_Surface *surface) {
  int i;
  int char_width;

  m_surface = surface;
  m_char_width = m_surface->w / 16;
  m_char_height = m_surface->h / 6;

  m_max_char_width = 0;
  for (i = 0; i < 97; i++) {
    char_width = Setup::text_char_widths[i];
    if (char_width > m_max_char_width) {
      m_max_char_width = char_width;
    }
  }
}

void Santa::Text::draw(const char *text, int x, int y, TextAlign align,
                       bool monospace) {
  int width;
  int char_width;
  int i;
  SDL_Rect src_rect;
  SDL_Rect dest_rect;

  if (monospace) {
    width = strlen(text) * m_max_char_width;
  } else {
    width = 0;
    for (i = 0; i < strlen(text); i++) {
      width += Setup::text_char_widths[text[i] - 32];
    }
  }

  x -= (align % 3) * (width / 2);
  y -= (align / 3) * (m_char_height / 2);

  for (i = 0; i < strlen(text); i++) {
    char_width = Setup::text_char_widths[text[i] - 32];

    src_rect.x = (text[i] % 16) * m_char_width;
    src_rect.y = (text[i] / 16 - 2) * m_char_height;
    src_rect.w = m_char_width;
    src_rect.h = m_char_height;
    dest_rect.x = x;
    dest_rect.y = y;

    if (monospace) {
      dest_rect.x += m_max_char_width / 2 - char_width / 2;
    }

    SDL_BlitSurface(m_surface, &src_rect, Setup::screen, &dest_rect);

    if (monospace) {
      x += m_max_char_width;
    } else {
      x += char_width;
    }
  }
}

int Santa::Text::get_line_height(void) { return m_char_height; }
