/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include "Angel.hpp"

#include <SDL/SDL.h>

#include "Draw.hpp"
#include "Globals.hpp"
#include "LevelObject.hpp"

SantaRacer::Angel::Angel(void *parent) { m_parent = parent; }

SantaRacer::Angel::~Angel(void) { return; }

void SantaRacer::Angel::reinit(int tile_x, int tile_y) {
  LevelObject *object;
  SDL_Surface *surface;

  object = (LevelObject *)m_parent;
  surface = Setup::images["angel"];

  m_level_x = (tile_x + 0.5) * Setup::game->level->tile_width -
              (surface->w / frame_count) / 2;
  m_y = (tile_y + 0.5) * Setup::game->level->tile_height - surface->h / 2;

  object->set_surface(surface);
  object->set_frame_count(frame_count);

  m_time = SDL_GetTicks();
  m_frame = 0;
}

void SantaRacer::Angel::draw(void) {
  LevelObject *object;
  SDL_Surface *surface;
  int frame;
  int width;
  int height;

  int level_x;
  int y;

  object = (LevelObject *)m_parent;
  surface = object->get_surface();
  width = object->get_width();
  height = object->get_height();

  level_x = get_level_x();
  y = get_y();
  frame = get_frame();

  Draw::blit(surface, width * frame, 0, width, height, Setup::screen,
             level_x - Setup::game->level->get_offset(), y);
}

void SantaRacer::Angel::move(void) { return; }

int SantaRacer::Angel::get_level_x(void) { return m_level_x; }

int SantaRacer::Angel::get_y(void) { return m_y; }

int SantaRacer::Angel::get_frame(void) {
  float time_diff;
  int frame;

  time_diff = (SDL_GetTicks() - m_time) / 1000.0;
  frame = int(time_diff * frame_speed + m_frame) % frame_count;

  return frame;
}
