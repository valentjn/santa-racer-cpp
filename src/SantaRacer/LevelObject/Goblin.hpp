/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

#include <SDL/SDL.h>

namespace SantaRacer {
namespace LevelObject {

class Goblin {
 public:
  explicit Goblin(void *parent);
  ~Goblin(void);

  void reinit(int tile_x, int tile_y);
  void draw(void);
  void move(void);

  int get_level_x(void);
  int get_y(void);
  int get_frame(void);
  bool query_snowball_thrown(void);

 private:
  static const int frame_count = 19;
  static const int frame_speed = frame_count / 1.5;

  void *m_parent;

  int m_level_x;
  int m_y;
  int m_frame;
  int m_time;
  bool m_snowball_thrown;
  bool m_snowball_thrown_query;
};

}  // namespace LevelObject
}  // namespace SantaRacer
