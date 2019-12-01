/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

namespace SantaRacer {

class Balloon {
 public:
  enum BalloonType {
    CashBalloon,
    PointsBalloon,
    ChampagneBalloon,
    GiftBalloon,
    ShieldBalloon
  };

  Balloon(void *parent);

  void reinit(int tile_x, int tile_y, int gfx_index);
  void draw(void);
  void move(void);

  int get_level_x(void);
  int get_y(void);
  int get_frame(void);
  BalloonType get_type(void);

 private:
  static const int balloon_frame_count = 8;
  static const int balloon_frame_speed = balloon_frame_count;
  static const int cash_frame_count = 7;
  static const int cash_frame_speed = cash_frame_count;
  static const int speed = 50;

  void *m_parent;
  BalloonType m_ballon_type;
  int m_time;
  int m_frame_speed;

  int m_level_x;
  int m_y;
  int m_frame;
};

}  // namespace SantaRacer
