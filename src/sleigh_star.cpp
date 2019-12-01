/*
 *      Santa Racer
 *      sleigh_star.cpp
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

#include "sleigh_star.hpp"

#include "draw.hpp"
#include "globals.hpp"
#include "random.hpp"

Santa::SleighStar::SleighStar() {
  m_surface = Setup::images["star"];
  m_surface_drunken = Setup::images["star_drunken"];
  m_width = m_surface->w / frame_count;
  m_height = m_surface->h;
  reinit(true);
}

void Santa::SleighStar::reinit(bool first_init) {
  m_level_x = Setup::game->level->get_offset() + Setup::game->sleigh->get_x() +
              Setup::game->sleigh->get_width() -
              Random::rnd(min_x_offset, max_x_offset);

  m_y = Setup::game->sleigh->get_y() + Setup::game->sleigh->get_height() -
        Random::rnd(min_y_offset, max_y_offset);

  m_time = SDL_GetTicks();

  if (first_init) {
    m_frame = Random::rnd(0, frame_count - 1);
  } else {
    m_frame = 0;
  }

  m_max_frame = Random::rnd(frame_count, max_frame_count);
}

void Santa::SleighStar::draw(void) {
  int frame;
  SDL_Surface *cur_surface;

  if (Setup::game->sleigh->is_drunken()) {
    cur_surface = m_surface_drunken;
  } else {
    cur_surface = m_surface;
  }

  frame = get_frame();
  if (frame >= frame_count) {
    return;
  }

  Draw::blit(cur_surface, frame * m_width, 0, m_width, m_height, Setup::screen,
             m_level_x - Setup::game->level->get_offset(), m_y);
}

void Santa::SleighStar::move(void) {
  if (get_frame() >= m_max_frame) {
    reinit();
  }
}

int Santa::SleighStar::get_frame(void) {
  return int((SDL_GetTicks() - m_time) / 1000.0 * frame_speed + m_frame);
}
