/*
 *      Santa Racer
 *      goblin_snowball.cpp
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

#include "goblin_snowball.hpp"

#include "draw.hpp"
#include "globals.hpp"
#include "level_object.hpp"

SantaRacer::GoblinSnowball::GoblinSnowball(void *parent) { m_parent = parent; }

SantaRacer::GoblinSnowball::~GoblinSnowball(void) { return; }

void SantaRacer::GoblinSnowball::reinit(int tile_x, int tile_y) {
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

void SantaRacer::GoblinSnowball::draw(void) {
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

void SantaRacer::GoblinSnowball::move(void) { return; }

int SantaRacer::GoblinSnowball::get_level_x(void) {
  return m_level_x + int((SDL_GetTicks() - m_time) / 1000.0 * speed_x);
}

int SantaRacer::GoblinSnowball::get_y(void) {
  float time_diff;

  time_diff = (SDL_GetTicks() - m_time) / 1000.0;

  return m_y + speed_y_start * time_diff +
         0.5 * gravity_acceleration * time_diff * time_diff;
}

int SantaRacer::GoblinSnowball::get_frame(void) { return 0; }
