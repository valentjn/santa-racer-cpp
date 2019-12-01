/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

#include <SDL/SDL.h>

#include "SantaRacer/Angel.hpp"
#include "SantaRacer/Balloon.hpp"
#include "SantaRacer/Cloud.hpp"
#include "SantaRacer/Finish.hpp"
#include "SantaRacer/Goblin.hpp"
#include "SantaRacer/GoblinSnowball.hpp"
#include "SantaRacer/Mask.hpp"
#include "SantaRacer/Snowman.hpp"

namespace SantaRacer {

class LevelObject {
 public:
  enum ObjectType {
    EmptyObject,
    SnowmanObject,
    GoblinObject,
    GoblinSnowballObject,
    AngelObject,
    BalloonObject,
    CloudObject,
    FinishObject
  };

  LevelObject(void);
  ~LevelObject(void);

  void reinit(int tile_x, int tile_y, int gfx_index);
  void reset(void);
  void draw(void);
  void move(void);
  void hide(void);

  ObjectType get_type(void);
  int get_tile_x(void);
  int get_tile_y(void);
  int get_width(void);
  int get_height(void);
  Mask *get_mask(void);
  bool exists(void);
  bool is_hidden(void);

  int get_level_x(void);
  int get_y(void);
  int get_frame(void);

  Cloud *get_cloud(void);
  Balloon *get_balloon(void);
  Angel *get_angel(void);
  Goblin *get_goblin(void);
  GoblinSnowball *get_goblin_snowball(void);
  Snowman *get_snowman(void);
  Finish *get_finish(void);

  SDL_Surface *get_surface(void);
  void set_surface(SDL_Surface *surface);

  int get_frame_count(void);
  void set_frame_count(int frame_count);

 private:
  bool m_exists;
  ObjectType m_type;

  int m_width;
  int m_height;
  int m_frame_count;

  int m_tile_x;
  int m_tile_y;

  SDL_Surface *m_surface;
  Mask *m_mask;
  bool m_hidden;

  Cloud *m_cloud;
  Balloon *m_balloon;
  Angel *m_angel;
  Goblin *m_goblin;
  GoblinSnowball *m_goblin_snowball;
  Snowman *m_snowman;
  Finish *m_finish;
};

}  // namespace SantaRacer
