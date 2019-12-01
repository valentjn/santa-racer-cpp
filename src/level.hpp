/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#ifndef SANTA_LEVEL_H
#define SANTA_LEVEL_H

#include <SDL/SDL.h>

#include "level_object.hpp"
#include "mask.hpp"

namespace SantaRacer {

class Level {
 public:
  static const int tile_width = 128;
  static const int tile_height = 128;
  static const int max_level_object_count = 50;

  Level(int **array, int **level_objects, int width, int height);
  ~Level(void);

  void draw(void);
  void draw_ballons(void);
  void draw_objects(void);
  void move(void);
  void move_objects(void);
  void move_object(int tile_x, int tile_y);
  void clear_objects(void);

  float get_offset(void);
  void set_offset(float offset);

  float get_speed(void);
  int get_tiles_to_draw(void);
  int get_tile_width(void);
  int get_tile_height(void);
  int get_width(void);
  int get_height(void);
  SantaRacer::Mask *get_mask(void);
  int **get_map(void);
  LevelObject *get_level_object(int index);

  void set_menu_mode(bool menu_mode);

  bool get_pause(void);
  void set_pause(bool pause);

 private:
  static const int min_speed = 40;
  static const int max_speed = 160;
  static const int menu_speed = 40;

  SDL_Surface *m_surface;
  Mask *m_mask;

  int m_width;
  int m_height;
  int m_time;
  int m_tiles_to_draw;
  float m_offset;
  bool m_menu_mode;
  bool m_pause;

  int **m_map;
  int **m_level_object_map;
  LevelObject **m_level_objects;
};

}  // namespace SantaRacer

#endif
