/*
 *      Santa Racer
 *      balloon.cpp
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

#include "balloon.hpp"

#include <SDL/SDL.h>

#include "draw.hpp"
#include "globals.hpp"
#include "level_object.hpp"

SantaRacer::Balloon::Balloon(void *parent) { m_parent = parent; }

void SantaRacer::Balloon::reinit(int tile_x, int tile_y, int gfx_index) {
  LevelObject *object;
  SDL_Surface *surface;
  int frame_count;

  object = (LevelObject *)m_parent;

  frame_count = balloon_frame_count;
  m_frame_speed = balloon_frame_speed;

  if (gfx_index == 71) {
    m_ballon_type = CashBalloon;
    surface = Setup::images["balloon2"];
    frame_count = cash_frame_count;
    m_frame_speed = cash_frame_speed;
  } else if (gfx_index == 72) {
    m_ballon_type = PointsBalloon;
    surface = Setup::images["balloon1"];
  } else if (gfx_index == 73) {
    m_ballon_type = ChampagneBalloon;
    surface = Setup::images["balloon5"];
  } else if (gfx_index == 74) {
    m_ballon_type = GiftBalloon;
    surface = Setup::images["balloon4"];
  } else if (gfx_index == 76) {
    m_ballon_type = ShieldBalloon;
    surface = Setup::images["balloon3"];
  }

  m_level_x = (tile_x + 0.5) * Setup::game->level->tile_width -
              (surface->w / frame_count) / 2;
  m_y = (tile_y + 1.5) * Setup::game->level->tile_height - surface->h / 2;

  object->set_surface(surface);
  object->set_frame_count(frame_count);

  m_time = SDL_GetTicks();
  m_frame = 0;
}

void SantaRacer::Balloon::draw(void) {
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

void SantaRacer::Balloon::move(void) { return; }

int SantaRacer::Balloon::get_level_x(void) { return m_level_x; }

int SantaRacer::Balloon::get_y(void) {
  LevelObject *object;
  float time_diff;
  int y;

  object = (LevelObject *)m_parent;
  time_diff = (SDL_GetTicks() - m_time) / 1000.0;
  y = m_y - speed * time_diff;

  return y;
}

int SantaRacer::Balloon::get_frame(void) {
  float time_diff;
  int frame;
  int frame_count;
  LevelObject *object;

  object = (LevelObject *)m_parent;
  frame_count = object->get_frame_count();
  time_diff = (SDL_GetTicks() - m_time) / 1000.0;
  frame = int(time_diff * m_frame_speed + m_frame) % (frame_count * 2 - 2);

  if (frame >= frame_count) {
    frame = 2 * frame_count - frame - 2;
  }

  return frame;
}

SantaRacer::Balloon::BalloonType SantaRacer::Balloon::get_type(void) {
  return m_ballon_type;
}
