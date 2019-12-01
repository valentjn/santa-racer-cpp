/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include "SantaRacer/Score.hpp"

#include "SantaRacer/Draw.hpp"
#include "SantaRacer/Globals.hpp"

SantaRacer::Score::Score(void) {
  m_surface_points = Setup::images["score_gift"];
  m_surface_damage = Setup::images["score_damage"];
  m_surface_time = Setup::images["score_time"];
  m_height = m_surface_points->h;

  m_points = 0;
  m_damage = 0;
  m_time_start = 0;
  m_total_time_secs = 0;
}

void SantaRacer::Score::reset(int total_time_secs) {
  m_points = 0;
  m_damage = 0;
  reset_clock(total_time_secs);
}

void SantaRacer::Score::draw(void) {
  char points[11];
  char damage[11];
  char time[11];
  int mins;
  int secs;

  Draw::copy(m_surface_points, Setup::screen, 0, 0);
  snprintf(points, 10, "%i", m_points);
  Setup::text->draw(points, 40, m_height / 2, Text::CenterLeft, true);

  Draw::copy(m_surface_damage, Setup::screen, 150, 0);
  if (m_damage == 0) {
    snprintf(damage, 10, "0");
  } else {
    snprintf(damage, 10, "-%i", m_damage);
  }
  Setup::text->draw(damage, 190, m_height / 2, Text::CenterLeft, true);

  Draw::copy(m_surface_time, Setup::screen, 520, 0);
  secs = get_remaining_secs();
  mins = floor(secs / 60);
  secs = secs % 60;
  if (secs < 10) {
    snprintf(time, 10, "%i:0%i", mins, secs);
  } else {
    snprintf(time, 10, "%i:%i", mins, secs);
  }
  Setup::text->draw(time, 560, m_height / 2, Text::CenterLeft, true);
}

int SantaRacer::Score::get_points(void) { return m_points; }

void SantaRacer::Score::set_points(int points) { m_points = points; }

void SantaRacer::Score::add_points(int points) { m_points += points; }

int SantaRacer::Score::get_damage(void) { return m_damage; }

void SantaRacer::Score::set_damage(int damage) { m_damage = damage; }

void SantaRacer::Score::add_damage(int damage) {
  m_damage += damage;

  if (m_damage < 0) {
    m_damage = 0;
  }
}

int SantaRacer::Score::get_remaining_secs(void) {
  if (m_time_start == 0) {
    return m_total_time_secs;
  } else {
    return m_total_time_secs - floor((SDL_GetTicks() - m_time_start) / 1000);
  }
}

void SantaRacer::Score::add_to_remaining_secs(int secs) {
  m_time_start += secs * 1000;
}

void SantaRacer::Score::reset_clock(int total_time_secs) {
  m_time_start = SDL_GetTicks();
  m_total_time_secs = total_time_secs;
}

int SantaRacer::Score::get_score(void) {
  return score_points_per_point * get_points() +
         score_points_per_damage * get_damage() +
         score_points_per_remaining_sec * get_remaining_secs();
}
