/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

#include <SDL/SDL.h>

#include "level_object.hpp"
#include "mask.hpp"
#include "sleigh_star.hpp"

namespace SantaRacer {

class Sleigh {
 public:
  Sleigh(void);
  ~Sleigh(void);

  void reset(void);
  void reset_stars(void);
  void draw(void);
  void stars_move(void);
  void electrified(void);
  void hit(void);
  void collided(void);
  void drunken(void);
  void shield(void);

  bool is_invincible(void);
  bool is_electrified(void);
  bool is_drunken(void);
  bool has_shield(void);
  bool is_unmovable(void);

  bool is_colliding(void);
  LevelObject *touched_level_object(void);

  int get_x(void);
  void set_x(int x);

  int get_y(void);
  void set_y(int y);

  int get_speed_x(void);
  void set_speed_x(int direction);

  int get_speed_y(void);
  void set_speed_y(int direction);

  bool get_pause(void);
  void set_pause(bool pause);

  int get_width(void);
  int get_height(void);
  int get_frame(void);

  void set_menu_mode(bool menu_mode);
  void set_alpha(Uint8 alpha);

 private:
  static const int frame_count = 14;
  static const int frame_speed = frame_count;
  static const int shield_frame_count = 8;
  static const int shield_frame_speed = shield_frame_count;

  static const int menu_x_period_length = 30000;
  static const int menu_min_x = 50;
  static const int menu_max_x = 450;
  static const int menu_y_period_length = 20000;
  static const int menu_min_y = 50;
  static const int menu_max_y = 200;

  static const int star_count = 50;
  static const int acceleration = 25;
  static const int max_move_speed = 200;

  static const int electrified_offset_x = -3;
  static const int electrified_offset_y = -2;
  static const int reindeer_offset_x = 10;
  static const int reindeer_offset_y = 3;
  static const int shield_offset_x = -12;
  static const int shield_offset_y = -17;

  static const int invincible_invisible_period = 200;

  static const int invincible_duration = 3000;
  static const int electrified_duration = 1000;
  static const int drunken_duration = 15000;
  static const int shield_duration = 15000;
  static const int collision_invincible_duration = 8000;
  static const int collision_unmovable_duration = 5000;

  int m_x;
  int m_y;
  int m_speed_x;
  int m_speed_y;
  int m_width;
  int m_height;
  int m_frame;
  int m_time;
  int m_time_x;
  int m_time_y;

  Uint8 m_alpha;
  bool m_menu_mode;
  float m_rand_offset_x;
  float m_rand_offset_y;
  SleighStar **m_stars;

  SDL_Surface *m_sleigh_surface;
  int m_sleigh_width;
  int m_sleigh_height;
  Mask *m_sleigh_mask;

  SDL_Surface *m_sleigh_electrified_surface;
  int m_sleigh_electrified_width;
  int m_sleigh_electrified_height;

  SDL_Surface *m_reindeer_surface;
  int m_reindeer_width;
  int m_reindeer_height;
  Mask *m_reindeer_mask;

  SDL_Surface *m_reindeer_electrified_surface;
  int m_reindeer_electrified_width;
  int m_reindeer_electrified_height;

  SDL_Surface *m_shield_surface;
  int m_shield_width;
  int m_shield_height;

  int m_electrified_end;
  int m_invincible_end;
  int m_drunken_end;
  int m_shield_end;
  int m_unmovable_end;

  bool m_pause;
};

}  // namespace SantaRacer
