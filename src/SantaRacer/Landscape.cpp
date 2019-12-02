/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include <math.h>

#include "SantaRacer/Draw.hpp"
#include "SantaRacer/Globals.hpp"
#include "SantaRacer/Landscape.hpp"

namespace SantaRacer {

Landscape::Landscape(void) {
  m_surface = Setup::images["landscape"];
  reset();
}

void Landscape::reset(void) {
  m_offset = 0.0;
  m_time = SDL_GetTicks();
  m_speed = 5.0;
  m_pause = false;
}

void Landscape::draw(void) {
  int offset;

  offset = get_offset();

  Draw::blit(m_surface, offset, 0, m_surface->w - offset, m_surface->h,
             Setup::screen, 0, 0);
  Draw::blit(m_surface, 0, 0, offset, m_surface->h, Setup::screen,
             m_surface->w - offset, 0);
}

void Landscape::move(void) {
  m_offset = get_offset();
  m_time = SDL_GetTicks();
}

float Landscape::get_offset(void) {
  if (m_pause) {
    return m_offset;
  }

  return fmod(m_offset + (SDL_GetTicks() - m_time) / 1000.0 * get_speed(),
              m_surface->w);
}

float Landscape::get_speed(void) {
  if (m_pause) {
    return 0.0;
  }

  return Setup::game->level->get_speed() / 10.0;
}

bool Landscape::get_pause(void) { return m_pause; }

void Landscape::set_pause(bool pause) {
  if ((pause && !m_pause) || (!pause && m_pause)) {
    m_offset = get_offset();
    m_time = SDL_GetTicks();
  }

  m_pause = pause;
}

}  // namespace SantaRacer
