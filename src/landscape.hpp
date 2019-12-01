/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#ifndef SANTA_LANDSCAPE_H
#define SANTA_LANDSCAPE_H

#include <SDL/SDL.h>

namespace SantaRacer {

class Landscape {
 public:
  Landscape(void);
  void reset(void);

  void draw(void);
  void move(void);

  float get_offset(void);
  float get_speed(void);

  bool get_pause(void);
  void set_pause(bool pause);

 private:
  SDL_Surface *m_surface;
  int m_time;
  float m_offset;
  float m_speed;

  bool m_pause;
};

}  // namespace SantaRacer

#endif
