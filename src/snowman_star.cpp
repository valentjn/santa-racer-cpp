/*
 *      Santa Racer
 *      snowman_star.cpp
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

#include "snowman_star.hpp"

#include "draw.hpp"
#include "globals.hpp"
#include "random.hpp"
#include "snowman.hpp"

Santa::SnowmanStar::SnowmanStar(Snowman *snowman) {
  m_surface = Setup::images["star"];
  m_snowman = snowman;
  reinit(true);
  m_width = m_surface->w / frame_count;
  m_height = m_surface->h;
}

void Santa::SnowmanStar::reinit(bool first_init) {
  if (!m_snowman->is_triggered()) {
    return;
  }

  m_level_x = m_snowman->get_level_x() + snowman_rocket_offset_x -
              Random::rnd(min_x_offset, max_x_offset);

  m_y = m_snowman->get_y() + snowman_rocket_offset_y -
        Random::rnd(min_y_offset, max_y_offset);

  m_time = SDL_GetTicks();

  if (first_init) {
    m_frame =
        m_max_frame - Random::rnd(wait_frame_count_min, wait_frame_count_max);
  } else {
    m_frame = 0;
  }

  m_max_frame = Random::rnd(frame_count, max_frame_count);
}

void Santa::SnowmanStar::draw(void) {
  int frame;

  frame = get_frame();
  if ((frame >= frame_count) || (frame < 0)) {
    return;
  }

  Draw::blit(m_surface, frame * m_width, 0, m_width, m_height, Setup::screen,
             m_level_x - Setup::game->level->get_offset(), m_y);
}

void Santa::SnowmanStar::move(void) {
  if (!m_snowman->is_triggered()) {
    m_time = SDL_GetTicks();
  }

  if (get_frame() >= m_max_frame) {
    reinit();
  }
}

int Santa::SnowmanStar::get_frame(void) {
  return int((SDL_GetTicks() - m_time) / 1000.0 * frame_speed + m_frame);
}
