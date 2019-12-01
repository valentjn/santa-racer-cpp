/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include "SantaRacer/LevelObject/GoblinSnowball.hpp"

#include "SantaRacer/Draw.hpp"
#include "SantaRacer/Globals.hpp"
#include "SantaRacer/LevelObject/LevelObject.hpp"

SantaRacer::LevelObject::GoblinSnowball::GoblinSnowball(void *parent) { m_parent = parent; }

SantaRacer::LevelObject::GoblinSnowball::~GoblinSnowball(void) { return; }

void SantaRacer::LevelObject::GoblinSnowball::reinit(int tile_x, int tile_y) {
  LevelObject *object;
  SDL_Surface *surface;

  object = (LevelObject *)m_parent;
  surface = Setup::images["snowball"];

  m_level_x = tile_x * Setup::game->level->tile_width + offset_x;
  m_y = tile_y * Setup::game->level->tile_height + offset_y;

  object->set_surface(surface);
  object->set_frame_count(frame_count);

  m_time = SDL_GetTicks();
  m_frame = 0;
}

void SantaRacer::LevelObject::GoblinSnowball::draw(void) {
  LevelObject *object;
  SDL_Surface *surface;

  int level_x;
  int y;

  object = (LevelObject *)m_parent;
  surface = object->get_surface();

  level_x = get_level_x();
  y = get_y();

  Draw::copy(surface, Setup::screen, level_x - Setup::game->level->get_offset(),
             y);
}

void SantaRacer::LevelObject::GoblinSnowball::move(void) { return; }

int SantaRacer::LevelObject::GoblinSnowball::get_level_x(void) {
  return m_level_x + int((SDL_GetTicks() - m_time) / 1000.0 * speed_x);
}

int SantaRacer::LevelObject::GoblinSnowball::get_y(void) {
  float time_diff;

  time_diff = (SDL_GetTicks() - m_time) / 1000.0;

  return m_y + speed_y_start * time_diff +
         0.5 * gravity_acceleration * time_diff * time_diff;
}

int SantaRacer::LevelObject::GoblinSnowball::get_frame(void) { return 0; }
