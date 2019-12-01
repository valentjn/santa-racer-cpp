/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include "SantaRacer/Level.hpp"

#include "SantaRacer/Draw.hpp"
#include "SantaRacer/Globals.hpp"

SantaRacer::Level::Level(int **map, int **level_object_map, int width, int height) {
  int i;

  m_surface = Setup::images["level"];
  m_mask = new Mask(m_surface, m_surface->w / tile_width);
  m_width = width;
  m_height = height;
  m_offset = 0.0;
  m_time = SDL_GetTicks();
  m_tiles_to_draw = Setup::screen_width / tile_width + 1;
  m_menu_mode = true;
  m_pause = false;

  m_map = map;
  m_level_object_map = level_object_map;

  m_level_objects = new LevelObject *[max_level_object_count];
  for (i = 0; i < max_level_object_count; i++) {
    m_level_objects[i] = new LevelObject();
  }
}

SantaRacer::Level::~Level(void) {
  int i;

  for (i = 0; i < max_level_object_count; i++) {
    delete m_level_objects[i];
  }
  delete[] m_level_objects;
}

void SantaRacer::Level::draw(void) {
  int start_x;
  int x;
  int y;
  int index;

  start_x = int(get_offset()) / tile_width;

  for (y = 0; y < m_height; y++) {
    for (x = start_x; x < start_x + m_tiles_to_draw; x++) {
      index = m_map[y][x];

      if (index != 0) {
        Draw::blit(m_surface, index * tile_width, 0, tile_width, tile_height,
                   Setup::screen, x * tile_width - m_offset, y * tile_height);
      }
    }
  }
}

void SantaRacer::Level::draw_ballons(void) {
  int i;
  LevelObject *object;

  for (i = 0; i < max_level_object_count; i++) {
    object = m_level_objects[i];
    if (object->exists() &&
        (object->get_type() == LevelObject::BalloonObject)) {
      object->draw();
    }
  }
}

void SantaRacer::Level::draw_objects(void) {
  int i;
  LevelObject *object;

  for (i = 0; i < max_level_object_count; i++) {
    object = m_level_objects[i];
    if (object->exists() &&
        (object->get_type() != LevelObject::BalloonObject)) {
      object->draw();
    }
  }
}

void SantaRacer::Level::move(void) {
  m_offset = get_offset();
  m_time = SDL_GetTicks();
}

void SantaRacer::Level::move_objects(void) {
  int start_x;
  int x;
  int y;
  int i;
  int index;
  LevelObject *object;

  start_x = int(get_offset()) / tile_width;

  for (y = 0; y < m_height; y++) {
    for (x = start_x; x < start_x + m_tiles_to_draw + 1; x++) {
      index = m_level_object_map[y][x];

      if (index != 0) {
        move_object(x, y);
      }
    }
  }

  for (i = 0; i < max_level_object_count; i++) {
    object = m_level_objects[i];

    if (object->exists()) {
      if ((object->get_tile_x() < start_x - 1) ||
          (object->get_y() > (2 * Setup::screen_height))) {
        object->reset();
      }
    }
  }
}

void SantaRacer::Level::move_object(int tile_x, int tile_y) {
  int i;
  int index;
  LevelObject *object;
  bool object_moved;

  object_moved = false;

  for (i = 0; i < max_level_object_count; i++) {
    object = m_level_objects[i];
    /*if ((tile_x == 7) && (tile_y == 2)) {
      Output::debug("move_goblin_object! %i\n", SDL_GetTicks());
      if (object->exists()) {
        Output::debug("object exists\n");
      } else {
        Output::debug("!object exists\n");
      }
      if (object->get_tile_x() == tile_x) {
        Output::debug("object tile_x\n");
      } else {
        Output::debug("!object tile_x %i, %i\n", object->get_tile_x(), tile_x);
      }
      if (object->get_tile_y() == tile_y) {
        Output::debug("object tile_y\n");
      } else {
        Output::debug("!object tile_y %i, %i\n", object->get_tile_y(), tile_y);
      }
    }*/

    if (object->exists() && (object->get_tile_x() == tile_x) &&
        (object->get_tile_y() == tile_y)) {
      /*if ((tile_x == 7) && (tile_y == 2)) {
    Output::debug("real_move_goblin_object! %i\n", SDL_GetTicks());
      }*/
      object->move();
      object_moved = true;
    }
  }

  if (object_moved) {
    return;
  }

  index = m_level_object_map[tile_y][tile_x];

  for (i = 0; i < max_level_object_count; i++) {
    object = m_level_objects[i];
    if (!object->exists()) {
      object->reinit(tile_x, tile_y, index);
      return;
    }
  }
}

void SantaRacer::Level::clear_objects(void) {
  int i;
  LevelObject *object;

  for (i = 0; i < max_level_object_count; i++) {
    object = m_level_objects[i];
    if (object->exists()) {
      object->reset();
    }
  }
}

float SantaRacer::Level::get_offset(void) {
  if (m_pause) {
    return m_offset;
  }

  return m_offset + (SDL_GetTicks() - m_time) / 1000.0 * get_speed();
}

void SantaRacer::Level::set_offset(float offset) {
  m_offset = offset;
  m_time = SDL_GetTicks();
}

float SantaRacer::Level::get_speed(void) {
  if (m_pause) {
    return 0.0;
  }

  if (m_menu_mode) {
    return menu_speed;
  } else {
    return Setup::game->sleigh->get_x() /
               float(Setup::screen_width - Setup::game->sleigh->get_width()) *
               (max_speed - min_speed) +
           min_speed;
  }
}

int SantaRacer::Level::get_tiles_to_draw(void) { return m_tiles_to_draw; }

int SantaRacer::Level::get_tile_width(void) { return tile_width; }

int SantaRacer::Level::get_tile_height(void) { return tile_height; }

int SantaRacer::Level::get_width(void) { return m_width; }

int SantaRacer::Level::get_height(void) { return m_height; }

SantaRacer::Mask *SantaRacer::Level::get_mask(void) { return m_mask; }

int **SantaRacer::Level::get_map(void) { return m_map; }

SantaRacer::LevelObject *SantaRacer::Level::get_level_object(int index) {
  return m_level_objects[index];
}

void SantaRacer::Level::set_menu_mode(bool menu_mode) { m_menu_mode = menu_mode; }

bool SantaRacer::Level::get_pause(void) { return m_pause; }

void SantaRacer::Level::set_pause(bool pause) {
  if ((pause && !m_pause) || (!pause && m_pause)) {
    m_offset = get_offset();
    m_time = SDL_GetTicks();
  }

  m_pause = pause;
}
