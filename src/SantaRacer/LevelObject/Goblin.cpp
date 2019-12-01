/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include "SantaRacer/LevelObject/Goblin.hpp"

#include "SantaRacer/Draw.hpp"
#include "SantaRacer/Globals.hpp"
#include "SantaRacer/LevelObject/LevelObject.hpp"

namespace SantaRacer {
namespace LevelObject {

Goblin::Goblin(void *parent) { m_parent = parent; }

Goblin::~Goblin(void) { return; }

void Goblin::reinit(int tile_x, int tile_y) {
  LevelObject *object;
  SDL_Surface *surface;

  object = (LevelObject *)m_parent;
  surface = Setup::images["goblin"];

  m_level_x = (tile_x + 0.5) * Setup::game->level->tile_width -
              (surface->w / frame_count) / 2;
  m_y = (tile_y + 0.5) * Setup::game->level->tile_height - surface->h / 2;

  object->set_surface(surface);
  object->set_frame_count(frame_count);

  m_time = SDL_GetTicks();
  m_frame = 0;
  m_snowball_thrown = false;
  m_snowball_thrown_query = false;
}

void Goblin::draw(void) {
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

void Goblin::move(void) {
  int frame;
  int i;
  LevelObject *parent;
  LevelObject *object;

  frame = get_frame();
  parent = (LevelObject *)m_parent;

  // Output::debug("frame %i\n", frame);

  if (frame == 13 && !m_snowball_thrown) {
    m_snowball_thrown = true;
    m_snowball_thrown_query = true;
    // Output::debug("new snowball %i\n", SDL_GetTicks());

    for (i = 0; i < Level::max_level_object_count; i++) {
      object = Setup::game->level->get_level_object(i);
      if (!object->exists()) {
        object->reinit(parent->get_tile_x(), parent->get_tile_y(), 200);
        return;
      }
    }

  } else if (frame != 13) {
    m_snowball_thrown = false;
  }
}

int Goblin::get_level_x(void) { return m_level_x; }

int Goblin::get_y(void) { return m_y; }

int Goblin::get_frame(void) {
  float time_diff;
  int frame;

  time_diff = (SDL_GetTicks() - m_time) / 1000.0;
  frame = int(time_diff * frame_speed + m_frame) % frame_count;

  return frame;
}

bool Goblin::query_snowball_thrown(void) {
  if (m_snowball_thrown_query) {
    m_snowball_thrown_query = false;
    return true;
  } else {
    return false;
  }
}

}  // namespace LevelObject
}  // namespace SantaRacer
