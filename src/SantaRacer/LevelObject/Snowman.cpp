/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include "SantaRacer/LevelObject/Snowman.hpp"

#include <SDL/SDL.h>

#include "SantaRacer/Draw.hpp"
#include "SantaRacer/Globals.hpp"
#include "SantaRacer/LevelObject/LevelObject.hpp"
#include "SantaRacer/Random.hpp"

namespace SantaRacer {
namespace LevelObject {

Snowman::Snowman(void *parent) {
  m_parent = parent;
  m_stars = nullptr;
}

Snowman::~Snowman(void) {
  int i;

  if (m_stars != nullptr) {
    for (i = 0; i < star_count; i++) {
      delete m_stars[i];
    }
    delete[] m_stars;
  }
}

void Snowman::reinit(int tile_x, int tile_y) {
  LevelObject *object;
  SDL_Surface *surface;
  int i;

  object = (LevelObject *)m_parent;
  surface = Setup::images["snowman"];

  m_level_x = (tile_x + 0.5) * Setup::game->level->tile_width -
              (surface->w / frame_count) / 2;
  m_y = (tile_y + 0.5) * Setup::game->level->tile_height - surface->h / 2;

  object->set_surface(surface);
  object->set_frame_count(frame_count);

  m_trigger_offset = Random::rnd(trigger_offset_min, trigger_offset_max);

  m_time = SDL_GetTicks();
  m_frame = 0;
  m_triggered = false;
  m_triggered_query = false;

  m_stars = new SnowmanStar *[star_count];
  for (i = 0; i < star_count; i++) {
    m_stars[i] = new SnowmanStar(this);
  }
}

void Snowman::draw(void) {
  LevelObject *object;
  SDL_Surface *surface;
  int frame;
  int width;
  int height;

  int level_x;
  int y;

  int i;

  for (i = 0; i < star_count; i++) {
    m_stars[i]->draw();
  }

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

void Snowman::move(void) {
  int i;

  if (Setup::game->sleigh->get_x() + Setup::game->level->get_offset() >=
      m_level_x - m_trigger_offset) {
    if (!m_triggered) {
      m_time = SDL_GetTicks();
      m_triggered = true;
      m_triggered_query = true;
    }
  }

  for (i = 0; i < star_count; i++) {
    m_stars[i]->move();
  }
}

int Snowman::get_level_x(void) {
  if (m_triggered) {
    return m_level_x + int((SDL_GetTicks() - m_time) / 1000.0 * speed_x);
  } else {
    return m_level_x;
  }
}

int Snowman::get_y(void) {
  if (m_triggered) {
    return m_y + int((SDL_GetTicks() - m_time) / 1000.0 * speed_y);
  } else {
    return m_y;
  }
}

int Snowman::get_frame(void) {
  float time_diff;
  int frame;

  if (m_triggered) {
    time_diff = (SDL_GetTicks() - m_time) / 1000.0;
    frame = int(time_diff * frame_speed + m_frame);

    if (frame >= frame_count) {
      return frame_count - 1;
    } else {
      return frame;
    }
  } else {
    return 0;
  }
}

bool Snowman::is_triggered(void) { return m_triggered; }

bool Snowman::query_triggered(void) {
  if (m_triggered_query) {
    m_triggered_query = false;
    return true;
  } else {
    return false;
  }
}

}  // namespace LevelObject
}  // namespace SantaRacer
