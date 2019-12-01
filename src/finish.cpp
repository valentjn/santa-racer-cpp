/*
 *      Santa Racer
 *      finish.cpp
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

#include "finish.hpp"

#include <SDL/SDL.h>

#include "draw.hpp"
#include "globals.hpp"
#include "level_object.hpp"

SantaRacer::Finish::Finish(void *parent) { m_parent = parent; }

SantaRacer::Finish::~Finish(void) { return; }

void SantaRacer::Finish::reinit(int tile_x, int tile_y) {
  LevelObject *object;
  SDL_Surface *surface;

  object = (LevelObject *)m_parent;
  surface = Setup::images["finish"];

  m_level_x = (tile_x + 0.5) * Setup::game->level->tile_width - surface->w / 2;
  m_y = (tile_y + 0.5) * Setup::game->level->tile_height - surface->h / 2;

  object->set_surface(surface);
  object->set_frame_count(1);
}

void SantaRacer::Finish::draw(void) {
  LevelObject *object;
  SDL_Surface *surface;
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

  Draw::blit(surface, 0, 0, width, height, Setup::screen,
             level_x - Setup::game->level->get_offset(), y);
}

void SantaRacer::Finish::move(void) { return; }

int SantaRacer::Finish::get_level_x(void) { return m_level_x; }

int SantaRacer::Finish::get_y(void) { return m_y; }

int SantaRacer::Finish::get_frame(void) { return 0; }

bool SantaRacer::Finish::reached(void) {
  return (Setup::game->level->get_offset() + Setup::game->sleigh->get_x() >=
          get_level_x());
}
