/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include "SantaRacer/LevelObject/SnowmanStar.hpp"

#include "SantaRacer/Draw.hpp"
#include "SantaRacer/Globals.hpp"
#include "SantaRacer/Random.hpp"
#include "SantaRacer/LevelObject/Snowman.hpp"

namespace SantaRacer {
namespace LevelObject {

SnowmanStar::SnowmanStar(Snowman *snowman) {
  m_surface = Setup::images["star"];
  m_snowman = snowman;
  reinit(true);
  m_width = m_surface->w / frame_count;
  m_height = m_surface->h;
}

void SnowmanStar::reinit(bool first_init) {
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

void SnowmanStar::draw(void) {
  int frame;

  frame = get_frame();
  if ((frame >= frame_count) || (frame < 0)) {
    return;
  }

  Draw::blit(m_surface, frame * m_width, 0, m_width, m_height, Setup::screen,
             m_level_x - Setup::game->level->get_offset(), m_y);
}

void SnowmanStar::move(void) {
  if (!m_snowman->is_triggered()) {
    m_time = SDL_GetTicks();
  }

  if (get_frame() >= m_max_frame) {
    reinit();
  }
}

int SnowmanStar::get_frame(void) {
  return static_cast<int>((SDL_GetTicks() - m_time) / 1000.0 * frame_speed + m_frame);
}

}  // namespace LevelObject
}  // namespace SantaRacer
