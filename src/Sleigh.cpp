/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include "Sleigh.hpp"

#include "Draw.hpp"
#include "Globals.hpp"
#include "Random.hpp"

SantaRacer::Sleigh::Sleigh(void) {
  m_sleigh_surface = Setup::images["sleigh"];
  m_sleigh_width = m_sleigh_surface->w / frame_count;
  m_sleigh_height = m_sleigh_surface->h;
  m_sleigh_mask = new Mask(m_sleigh_surface, frame_count);

  m_sleigh_electrified_surface = Setup::images["electrified_sleigh"];
  m_sleigh_electrified_width = m_sleigh_electrified_surface->w;
  m_sleigh_electrified_height = m_sleigh_electrified_surface->h;

  m_reindeer_surface = Setup::images["reindeer"];
  m_reindeer_width = m_reindeer_surface->w / frame_count;
  m_reindeer_height = m_reindeer_surface->h;
  m_reindeer_mask = new Mask(m_reindeer_surface, frame_count);

  m_reindeer_electrified_surface = Setup::images["electrified_reindeer"];
  m_reindeer_electrified_width = m_reindeer_electrified_surface->w;
  m_reindeer_electrified_height = m_reindeer_electrified_surface->h;

  m_shield_surface = Setup::images["shield"];
  m_shield_width = m_shield_surface->w / shield_frame_count;
  m_shield_height = m_shield_surface->h;

  m_stars = NULL;
  reset();
}

SantaRacer::Sleigh::~Sleigh(void) {
  int i;

  for (i = 0; i < star_count; i++) {
    delete m_stars[i];
  }
  delete[] m_stars;

  delete m_sleigh_mask;
}

void SantaRacer::Sleigh::reset(void) {
  m_x = 0;
  m_y = 0;
  m_speed_x = 0;
  m_speed_y = 0;
  m_width = m_reindeer_width + m_sleigh_width + reindeer_offset_x;
  m_height = m_sleigh_height;
  m_frame = 0;
  m_time = SDL_GetTicks();
  m_time_x = 0;
  m_time_y = 0;
  m_alpha = 255;
  m_menu_mode = true;
  m_rand_offset_x = Random::rnd(0, 200 * M_PI) / 100.0;
  m_rand_offset_y = Random::rnd(0, 200 * M_PI) / 100.0;
  m_electrified_end = 0;
  m_invincible_end = 0;
  m_drunken_end = 0;
  m_shield_end = 0;
  m_unmovable_end = 0;
  m_pause = false;

  set_alpha(255);
}

void SantaRacer::Sleigh::reset_stars(void) {
  int i;

  if (m_stars == NULL) {
    m_stars = new SleighStar *[star_count];
    for (i = 0; i < star_count; i++) {
      m_stars[i] = new SleighStar();
    }
  } else {
    for (i = 0; i < star_count; i++) {
      m_stars[i]->reinit(true);
    }
  }
}

void SantaRacer::Sleigh::draw(void) {
  int frame;
  int shield_frame;
  int reindeer_frame_number;
  int x;
  int y;
  int i;
  int time;

  if (is_invincible()) {
    time = (m_invincible_end - SDL_GetTicks()) % invincible_invisible_period;
    if (time >= invincible_invisible_period / 2) {
      return;
    }
  }

  frame = get_frame();
  reindeer_frame_number = (frame + frame_count / 2) % frame_count;
  x = get_x();
  y = get_y();

  if (is_electrified()) {
    Draw::copy(m_sleigh_electrified_surface, Setup::screen,
               x - (m_sleigh_electrified_width - m_sleigh_width) / 2 +
                   electrified_offset_x,
               y - (m_sleigh_electrified_height - m_sleigh_height) / 2 +
                   electrified_offset_y);

    Draw::copy(m_reindeer_electrified_surface, Setup::screen,
               x + m_sleigh_width + reindeer_offset_x -
                   (m_reindeer_electrified_width - m_reindeer_width) / 2 +
                   electrified_offset_x,
               y + reindeer_offset_y -
                   (m_reindeer_electrified_height - m_reindeer_height) / 2 +
                   electrified_offset_y);

    Draw::copy(m_reindeer_electrified_surface, Setup::screen,
               x + m_sleigh_width -
                   (m_reindeer_electrified_width - m_reindeer_width) / 2 +
                   electrified_offset_x,
               y + reindeer_offset_y -
                   (m_reindeer_electrified_height - m_reindeer_height) / 2 +
                   electrified_offset_y);
  }

  Draw::blit(m_sleigh_surface, frame * m_sleigh_width, 0, m_sleigh_width,
             m_sleigh_height, Setup::screen, x, y);

  Draw::blit(m_reindeer_surface, reindeer_frame_number * m_reindeer_width, 0,
             m_reindeer_width, m_reindeer_height, Setup::screen,
             x + m_sleigh_width + reindeer_offset_x, y + reindeer_offset_y);

  Draw::blit(m_reindeer_surface, frame * m_reindeer_width, 0, m_reindeer_width,
             m_reindeer_height, Setup::screen, x + m_sleigh_width,
             y + reindeer_offset_y);

  if (!m_pause) {
    for (i = 0; i < star_count; i++) {
      m_stars[i]->draw();
    }
  }

  if (has_shield()) {
    shield_frame =
        int((m_shield_end - SDL_GetTicks()) / 1000.0 * shield_frame_speed) %
        shield_frame_count;
    Draw::blit(m_shield_surface, shield_frame * m_shield_width, 0,
               m_shield_width, m_shield_height, Setup::screen,
               x + shield_offset_y - shield_frame, y + shield_offset_y);
  }
}

void SantaRacer::Sleigh::stars_move(void) {
  int i;

  for (i = 0; i < star_count; i++) {
    m_stars[i]->move();
  }
}

void SantaRacer::Sleigh::electrified(void) {
  m_electrified_end = SDL_GetTicks() + electrified_duration;
  m_invincible_end = SDL_GetTicks() + invincible_duration;
}

void SantaRacer::Sleigh::hit(void) {
  m_invincible_end = SDL_GetTicks() + invincible_duration;
}

void SantaRacer::Sleigh::collided(void) {
  m_invincible_end = SDL_GetTicks() + collision_invincible_duration;
  m_unmovable_end = SDL_GetTicks() + collision_unmovable_duration;
  m_speed_x = 0;
  m_speed_y = -max_move_speed;
}

void SantaRacer::Sleigh::drunken(void) {
  m_drunken_end = SDL_GetTicks() + drunken_duration;
}

void SantaRacer::Sleigh::shield(void) {
  m_shield_end = SDL_GetTicks() + shield_duration;
}

bool SantaRacer::Sleigh::is_invincible(void) {
  if (m_invincible_end == 0) {
    return false;
  } else if (m_invincible_end > SDL_GetTicks()) {
    return true;
  }

  return false;
}

bool SantaRacer::Sleigh::is_electrified(void) {
  if (m_electrified_end == 0) {
    return false;
  } else if (m_electrified_end > SDL_GetTicks()) {
    return true;
  }

  return false;
}

bool SantaRacer::Sleigh::is_drunken(void) {
  if (m_drunken_end == 0) {
    return false;
  } else if (m_drunken_end > SDL_GetTicks()) {
    return true;
  }

  return false;
}

bool SantaRacer::Sleigh::has_shield(void) {
  if (m_shield_end == 0) {
    return false;
  } else if (m_shield_end > SDL_GetTicks()) {
    return true;
  }

  return false;
}

bool SantaRacer::Sleigh::is_unmovable(void) {
  if (m_unmovable_end == 0) {
    return false;
  } else if (m_unmovable_end > SDL_GetTicks()) {
    return true;
  }

  return false;
}

bool SantaRacer::Sleigh::is_colliding(void) {
  int x;
  int y;
  int start_x;
  int tile_x;
  int tile_y;
  int sleigh_frame;
  int reindeer_frame;
  int level_height;
  int level_frame;
  int tile_width;
  int tile_height;
  int tiles_to_draw;
  int level_offset;

  Mask *level_mask;
  int **level_map;

  if (m_menu_mode) {
    return false;
  }

  if (is_unmovable()) {
    return false;
  }

  x = get_x();
  y = get_y();
  sleigh_frame = get_frame();
  reindeer_frame = (sleigh_frame + frame_count / 2) % frame_count;
  level_mask = Setup::game->level->get_mask();
  level_map = Setup::game->level->get_map();
  level_height = Setup::game->level->get_height();
  tile_width = Setup::game->level->get_tile_width();
  tile_height = Setup::game->level->get_tile_height();
  tiles_to_draw = Setup::game->level->get_tiles_to_draw();
  level_offset = Setup::game->level->get_offset();
  start_x = level_offset / tile_width;

  for (tile_y = 0; tile_y < level_height; tile_y++) {
    for (tile_x = start_x; tile_x < start_x + tiles_to_draw; tile_x++) {
      level_frame = level_map[tile_y][tile_x];

      if (level_frame == 0) {
        continue;
      }

      if (m_sleigh_mask->is_colliding(x, y, sleigh_frame, level_mask,
                                      tile_x * tile_width - level_offset,
                                      tile_y * tile_height, level_frame)) {
        return true;
      }

      if (m_reindeer_mask->is_colliding(x + m_sleigh_width + reindeer_offset_x,
                                        y, reindeer_frame, level_mask,
                                        tile_x * tile_width - level_offset,
                                        tile_y * tile_height, level_frame)) {
        return true;
      }
    }
  }

  return false;
}

SantaRacer::LevelObject *SantaRacer::Sleigh::touched_level_object(void) {
  int x;
  int y;
  int sleigh_frame;
  int reindeer_frame;
  int i;
  int level_offset;

  LevelObject *object;
  Mask *object_mask;
  int object_level_x;
  int object_y;
  int object_frame;

  bool shield;

  if (is_invincible()) {
    return NULL;
  }

  x = get_x();
  y = get_y();
  sleigh_frame = get_frame();
  reindeer_frame = (sleigh_frame + frame_count / 2) % frame_count;
  level_offset = Setup::game->level->get_offset();
  shield = has_shield();

  for (i = 0; i < Level::max_level_object_count; i++) {
    object = Setup::game->level->get_level_object(i);

    if (object->exists() && !object->is_hidden()) {
      object_mask = object->get_mask();
      object_level_x = object->get_level_x();
      object_y = object->get_y();
      object_frame = object->get_frame();
      // Output::debug("touching, type %i, level_x %i, y %i\n",
      // object->get_type(), object_level_x, object_y);

      if (m_sleigh_mask->is_colliding(x, y, sleigh_frame, object_mask,
                                      object_level_x - level_offset, object_y,
                                      object_frame)) {
        if (!shield || (object->get_type() == LevelObject::BalloonObject)) {
          return object;
        }
      }

      if (m_reindeer_mask->is_colliding(x + m_sleigh_width + reindeer_offset_x,
                                        y, reindeer_frame, object_mask,
                                        object_level_x - level_offset, object_y,
                                        object_frame)) {
        if (!shield || (object->get_type() == LevelObject::BalloonObject)) {
          return object;
        }
      }
    }
  }

  return NULL;
}

int SantaRacer::Sleigh::get_x(void) {
  int x;

  if (m_menu_mode) {
    return (sin(float(SDL_GetTicks() - m_time) / menu_x_period_length * 2 *
                    M_PI +
                m_rand_offset_x) +
            1) *
               ((menu_max_x - menu_min_x) / 2.0) +
           menu_min_x;
  } else {
    if (m_speed_x == 0) {
      return m_x;
    } else {
      x = m_x + int((SDL_GetTicks() - m_time_x) / 1000.0 * m_speed_x);
      if (x < 0) {
        m_x = 0;
        m_speed_x = 0;
        x = m_x;
      } else if (x > Setup::screen_width - get_width()) {
        m_x = Setup::screen_width - get_width();
        m_speed_x = 0;
        x = m_x;
      }

      return x;
    }
  }
}

int SantaRacer::Sleigh::get_y(void) {
  int y;

  if (m_menu_mode) {
    return (sin(float(SDL_GetTicks() - m_time) / menu_y_period_length * 2 *
                    M_PI +
                m_rand_offset_y) +
            1) *
               ((menu_max_y - menu_min_y) / 2.0) +
           menu_min_y;
  } else {
    if (m_speed_y == 0) {
      return m_y;

    } else {
      y = m_y + int((SDL_GetTicks() - m_time_y) / 1000.0 * m_speed_y);
      if (y < 0) {
        m_y = 0;
        m_speed_y = 0;
        y = m_y;
      } else if (y > Setup::screen_height - get_height()) {
        m_y = Setup::screen_height - get_height();
        m_speed_y = 0;
        y = m_y;
      }

      return y;
    }
  }
}

int SantaRacer::Sleigh::get_speed_x(void) { return m_speed_x; }

int SantaRacer::Sleigh::get_speed_y(void) { return m_speed_y; }

int SantaRacer::Sleigh::get_width(void) { return m_width; }

int SantaRacer::Sleigh::get_height(void) { return m_height; }

int SantaRacer::Sleigh::get_frame(void) {
  if (m_pause) {
    return m_frame;
  }

  return int((SDL_GetTicks() - m_time) / 1000.0 * frame_speed + m_frame) %
         frame_count;
}

void SantaRacer::Sleigh::set_menu_mode(bool menu_mode) { m_menu_mode = menu_mode; }

void SantaRacer::Sleigh::set_x(int x) {
  m_x = x;
  m_speed_x = 0;
}

void SantaRacer::Sleigh::set_y(int y) {
  m_y = y;
  m_speed_y = 0;
}

void SantaRacer::Sleigh::set_speed_x(int direction) {
  if (is_unmovable()) {
    return;
  }

  if (direction == 0) {
    if (m_speed_x > 0) {
      direction = -1;
    } else if (m_speed_x < 0) {
      direction = 1;
    }
  }

  m_x = get_x();
  m_speed_x += acceleration * direction;

  if (m_speed_x > max_move_speed) {
    m_speed_x = max_move_speed;
  } else if (m_speed_x < -max_move_speed) {
    m_speed_x = -max_move_speed;
  }

  m_time_x = SDL_GetTicks();
}

void SantaRacer::Sleigh::set_speed_y(int direction) {
  if (is_unmovable()) {
    return;
  }

  if (direction == 0) {
    if (m_speed_y > 0) {
      direction = -1;
    } else if (m_speed_y < 0) {
      direction = 1;
    }
  }

  m_y = get_y();
  m_speed_y += acceleration * direction;

  if (m_speed_y > max_move_speed) {
    m_speed_y = max_move_speed;
  } else if (m_speed_y < -max_move_speed) {
    m_speed_y = -max_move_speed;
  }

  m_time_y = SDL_GetTicks();
}

bool SantaRacer::Sleigh::get_pause(void) { return m_pause; }

void SantaRacer::Sleigh::set_pause(bool pause) {
  if ((pause && !m_pause) || (!pause && m_pause)) {
    m_frame = get_frame();
    m_time = SDL_GetTicks();
  }

  m_pause = pause;
}

void SantaRacer::Sleigh::set_alpha(Uint8 alpha) {
  Draw::set_alpha(m_sleigh_surface, alpha);
  Draw::set_alpha(m_reindeer_surface, alpha);
}
