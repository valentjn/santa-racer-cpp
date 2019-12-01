/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#ifndef SANTA_SCORE_H
#define SANTA_SCORE_H

#include <SDL/SDL.h>

namespace SantaRacer {

class Score {
 public:
  Score(void);

  void reset(int total_time_secs);
  void draw(void);

  int get_points(void);
  void set_points(int points);
  void add_points(int points);

  int get_damage(void);
  void set_damage(int damage);
  void add_damage(int damage);

  int get_remaining_secs(void);
  void add_to_remaining_secs(int secs);
  void reset_clock(int total_time_secs);

  int get_score(void);

 private:
  static const int score_points_per_point = 1;
  static const int score_points_per_damage = -2;
  static const int score_points_per_remaining_sec = 10;

  int m_height;

  int m_points;
  int m_damage;
  int m_time_start;
  int m_total_time_secs;

  SDL_Surface *m_surface_points;
  SDL_Surface *m_surface_damage;
  SDL_Surface *m_surface_time;
};

}  // namespace SantaRacer

#endif
