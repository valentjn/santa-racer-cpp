/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include "SantaRacer/LevelObject/SleighStar.hpp"

#include "SantaRacer/Draw.hpp"
#include "SantaRacer/Globals.hpp"
#include "SantaRacer/Random.hpp"

namespace SantaRacer {
namespace LevelObject {

SleighStar::SleighStar() {
  m_surface = Setup::images["star"];
  m_surface_drunken = Setup::images["star_drunken"];
  m_width = m_surface->w / frame_count;
  m_height = m_surface->h;
  reinit(true);
}

void SleighStar::reinit(bool first_init) {
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

void SleighStar::draw(void) {
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

void SleighStar::move(void) {
  if (get_frame() >= m_max_frame) {
    reinit();
  }
}

int SleighStar::get_frame(void) {
  return int((SDL_GetTicks() - m_time) / 1000.0 * frame_speed + m_frame);
}

}  // namespace LevelObject
}  // namespace SantaRacer
