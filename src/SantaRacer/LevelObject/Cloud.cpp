/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include "SantaRacer/LevelObject/Cloud.hpp"

#include <SDL/SDL.h>

#include "SantaRacer/Draw.hpp"
#include "SantaRacer/Globals.hpp"
#include "SantaRacer/LevelObject/LevelObject.hpp"

namespace SantaRacer {
namespace LevelObject {

Cloud::Cloud(void *parent) { m_parent = parent; }

void Cloud::reinit(int tile_x, int tile_y) {
  LevelObject *object;
  SDL_Surface *surface;

  object = (LevelObject *)m_parent;

  surface = Setup::images["cloud"];
  m_level_x = (tile_x + 0.5) * Setup::game->level->tile_width - surface->w / 2;
  m_y = (tile_y + 0.5) * Setup::game->level->tile_height - surface->h / 2;

  object->set_surface(surface);
  object->set_frame_count(1);
}

void Cloud::draw(void) {
  LevelObject *object;
  SDL_Surface *surface;

  object = (LevelObject *)m_parent;
  surface = object->get_surface();

  Draw::copy(surface, Setup::screen,
             m_level_x - Setup::game->level->get_offset(), m_y);
}

void Cloud::move(void) { return; }

int Cloud::get_level_x(void) { return m_level_x; }

int Cloud::get_y(void) { return m_y; }

int Cloud::get_frame(void) { return 0; }

}  // namespace LevelObject
}  // namespace SantaRacer
