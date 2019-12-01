/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include "SantaRacer/LevelObject/Finish.hpp"

#include <SDL/SDL.h>

#include "SantaRacer/Draw.hpp"
#include "SantaRacer/Globals.hpp"
#include "SantaRacer/LevelObject/LevelObject.hpp"

SantaRacer::LevelObject::Finish::Finish(void *parent) { m_parent = parent; }

SantaRacer::LevelObject::Finish::~Finish(void) { return; }

void SantaRacer::LevelObject::Finish::reinit(int tile_x, int tile_y) {
  LevelObject *object;
  SDL_Surface *surface;

  object = (LevelObject *)m_parent;
  surface = Setup::images["finish"];

  m_level_x = (tile_x + 0.5) * Setup::game->level->tile_width - surface->w / 2;
  m_y = (tile_y + 0.5) * Setup::game->level->tile_height - surface->h / 2;

  object->set_surface(surface);
  object->set_frame_count(1);
}

void SantaRacer::LevelObject::Finish::draw(void) {
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

void SantaRacer::LevelObject::Finish::move(void) { return; }

int SantaRacer::LevelObject::Finish::get_level_x(void) { return m_level_x; }

int SantaRacer::LevelObject::Finish::get_y(void) { return m_y; }

int SantaRacer::LevelObject::Finish::get_frame(void) { return 0; }

bool SantaRacer::LevelObject::Finish::reached(void) {
  return (Setup::game->level->get_offset() + Setup::game->sleigh->get_x() >=
          get_level_x());
}
