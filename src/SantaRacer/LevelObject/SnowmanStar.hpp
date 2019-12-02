/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

#include <SDL/SDL.h>

namespace SantaRacer {
namespace LevelObject {

class Snowman;

class SnowmanStar {
 public:
  explicit SnowmanStar(Snowman *snowman);
  void reinit(bool first_init = false);
  void draw(void);
  void move(void);
  int get_frame(void);

 private:
  static const int frame_count = 17;
  static const int max_frame_count = 30;
  static const int frame_speed = 2 * frame_count;
  static const int min_x_offset = -5;
  static const int max_x_offset = 5;
  static const int min_y_offset = -5;
  static const int max_y_offset = 5;

  static const int snowman_rocket_offset_x = 35;
  static const int snowman_rocket_offset_y = 35;

  static const int wait_frame_count_min = 50;
  static const int wait_frame_count_max = 100;

  int m_level_x;
  int m_y;
  int m_width;
  int m_height;
  int m_frame;
  int m_max_frame;
  int m_time;

  SDL_Surface *m_surface;
  SDL_Surface *m_surface_drunken;

  Snowman *m_snowman;
};

}  // namespace LevelObject
}  // namespace SantaRacer
