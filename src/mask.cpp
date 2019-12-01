/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include "mask.hpp"

#include "globals.hpp"

SantaRacer::Mask::Mask(SDL_Surface *surface, int frame_count) {
  int x;
  int y;
  Uint8 r;
  Uint8 g;
  Uint8 b;
  Uint8 a;
  Uint32 *pixel;

  m_surface = surface;
  m_frame_count = frame_count;
  m_complete_width = m_surface->w;
  m_width = m_complete_width / m_frame_count;
  m_height = m_surface->h;
  m_array = new bool *[m_height];

  SDL_LockSurface(m_surface);

  for (y = 0; y < m_height; y++) {
    m_array[y] = new bool[m_complete_width];
    for (x = 0; x < m_complete_width; x++) {
      pixel = (Uint32 *)m_surface->pixels + y * m_surface->pitch / 4 + x;
      SDL_GetRGBA(*pixel, m_surface->format, &r, &g, &b, &a);
      m_array[y][x] = (a == 0xff);
    }
  }

  SDL_UnlockSurface(m_surface);
}

SantaRacer::Mask::~Mask(void) {
  int y;

  for (y = 0; y < m_height; y++) {
    delete[] m_array[y];
  }
  delete[] m_array;
}

bool SantaRacer::Mask::is_colliding(int x1, int y1, int frame1, Mask *mask2, int x2,
                               int y2, int frame2) {
  bool **array1;
  bool **array2;

  int width1;
  int height1;
  int width2;
  int height2;

  int clip_x;
  int clip_y;
  int clip_w;
  int clip_h;

  int test_x;
  int test_y;
  int test_x1;
  int test_y1;
  int test_x2;
  int test_y2;
  int test_x1_start;
  int test_x2_start;

  width1 = get_width();
  height1 = get_height();
  width2 = mask2->get_width();
  height2 = mask2->get_height();

  if ((x1 < x2 && x1 + width1 < x2) || (x2 < x1 && x2 + width2 < x1) ||
      (y1 < y2 && y1 + height1 < y2) || (y2 < y1 && y2 + height2 < y1)) {
    return false;
  }

  if (x1 < x2) {
    clip_x = x2;
    clip_w = x1 + width1 - x2;
    if (clip_w > width2) {
      clip_w = width2;
    }

  } else {
    clip_x = x1;
    clip_w = x2 + width2 - x1;
    if (clip_w > width1) {
      clip_w = width1;
    }
  }

  if (y1 < y2) {
    clip_y = y2;
    clip_h = y1 + height1 - y2;
    if (clip_h > height2) {
      clip_h = height2;
    }

  } else {
    clip_y = y1;
    clip_h = y2 + height2 - y1;
    if (clip_h > height1) {
      clip_h = height1;
    }
  }

  // Output::debug("y1: %i, y2: %i, height1: %i, height2: %i, clip_h: %i\n", y1,
  // y2, height1, height2, clip_h);
  array1 = get_array();
  array2 = mask2->get_array();
  test_y1 = clip_y - y1;
  test_y2 = clip_y - y2;
  test_x1_start = clip_x - x1 + width1 * frame1;
  test_x2_start = clip_x - x2 + width2 * frame2;

  for (test_y = clip_y; test_y < clip_y + clip_h; test_y++) {
    test_x1 = test_x1_start;
    test_x2 = test_x2_start;
    for (test_x = clip_x; test_x < clip_x + clip_w; test_x++) {
      // Output::debug("c: %i, test_x1: %i, test_y1: %i, test_x2: %i, test_y2:
      // %i\n", clip_h, test_x1, test_y1, test_x2, test_y2);
      if (array1[test_y1][test_x1] && array2[test_y2][test_x2]) {
        return true;
      }
      test_x1++;
      test_x2++;
    }
    test_y1++;
    test_y2++;
  }

  return false;
}

int SantaRacer::Mask::get_width(void) { return m_width; }

int SantaRacer::Mask::get_height(void) { return m_height; }

bool **SantaRacer::Mask::get_array(void) { return m_array; }
