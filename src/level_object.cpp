/*
 *      Santa Racer
 *      level_object.cpp
 *
 *      Copyright (C) 2010 Julian Valentin.
 *
 *      This program is free software: you can redistribute it and/or modify
 *      it under the terms of the GNU General Public License as published by
 *      the Free Software Foundation, either version 3 of the License, or
 *      (at your option) any later version.
 *
 *      This program is distributed in the hope that it will be useful,
 *      but WITHOUT ANY WARRANTY; without even the implied warranty of
 *      MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 *      GNU General Public License for more details.
 *
 *      You should have received a copy of the GNU General Public License
 *      along with this program.  If not, see <http://www.gnu.org/licenses/>.
 */

#include "level_object.hpp"

#include "globals.hpp"

Santa::LevelObject::LevelObject(void) {
  m_cloud = new Cloud(this);
  m_balloon = new Balloon(this);
  m_angel = new Angel(this);
  m_goblin = new Goblin(this);
  m_goblin_snowball = new GoblinSnowball(this);
  m_snowman = new Snowman(this);
  m_finish = new Finish(this);

  reset();
}

Santa::LevelObject::~LevelObject(void) {
  delete m_cloud;
  delete m_balloon;
  delete m_angel;
  delete m_goblin;
  delete m_goblin_snowball;
  delete m_snowman;
  delete m_finish;
  delete m_mask;
}

void Santa::LevelObject::reinit(int tile_x, int tile_y, int gfx_index) {
  m_exists = true;
  m_tile_x = tile_x;
  m_tile_y = tile_y;

  // Output::debug("LevelObject::reinit, tile_x %i, tile_y %i, index %i\n",
  // tile_x, tile_y, gfx_index);

  if (gfx_index == 75) {
    m_type = CloudObject;
    m_cloud->reinit(tile_x, tile_y);

  } else if ((gfx_index == 71) || (gfx_index == 72) || (gfx_index == 73) ||
             (gfx_index == 74) || (gfx_index == 76)) {
    m_type = BalloonObject;
    m_balloon->reinit(tile_x, tile_y, gfx_index);

  } else if (gfx_index == 70) {
    m_type = AngelObject;
    m_angel->reinit(tile_x, tile_y);

  } else if (gfx_index == 69) {
    m_type = GoblinObject;
    m_goblin->reinit(tile_x, tile_y);

  } else if (gfx_index == 200) {
    m_type = GoblinSnowballObject;
    m_goblin_snowball->reinit(tile_x, tile_y);

  } else if (gfx_index == 30) {
    m_type = SnowmanObject;
    m_snowman->reinit(tile_x, tile_y);

  } else if (gfx_index == 77) {
    m_type = FinishObject;
    m_finish->reinit(tile_x, tile_y);
  }

  m_width = m_surface->w / m_frame_count;
  m_height = m_surface->h;
  m_mask = new Mask(m_surface, m_frame_count);
  m_hidden = false;
}

void Santa::LevelObject::reset(void) {
  // Output::debug("LevelObject::reset, tile_x %i, tile_y %i\n", m_tile_x,
  // m_tile_y);
  m_exists = false;
  m_type = EmptyObject;

  m_tile_x = 0;
  m_tile_y = 0;

  m_width = 0;
  m_height = 0;
  m_mask = NULL;
  m_hidden = false;
}

void Santa::LevelObject::draw(void) {
  if (m_hidden) {
    return;
  }

  if (m_type == CloudObject) {
    m_cloud->draw();
  } else if (m_type == BalloonObject) {
    m_balloon->draw();
  } else if (m_type == AngelObject) {
    m_angel->draw();
  } else if (m_type == GoblinObject) {
    m_goblin->draw();
  } else if (m_type == GoblinSnowballObject) {
    m_goblin_snowball->draw();
  } else if (m_type == SnowmanObject) {
    m_snowman->draw();
  } else if (m_type == FinishObject) {
    m_finish->draw();
  }
}

void Santa::LevelObject::move(void) {
  if (m_hidden) {
    return;
  }

  if (m_type == CloudObject) {
    m_cloud->move();
  } else if (m_type == BalloonObject) {
    m_balloon->move();
  } else if (m_type == AngelObject) {
    m_angel->move();
  } else if (m_type == GoblinObject) {
    m_goblin->move();
  } else if (m_type == GoblinSnowballObject) {
    m_goblin_snowball->move();
  } else if (m_type == SnowmanObject) {
    m_snowman->move();
  } else if (m_type == FinishObject) {
    m_finish->move();
  }
}

void Santa::LevelObject::hide(void) { m_hidden = true; }

Santa::LevelObject::ObjectType Santa::LevelObject::get_type(void) {
  return m_type;
}

int Santa::LevelObject::get_tile_x(void) { return m_tile_x; }

int Santa::LevelObject::get_tile_y(void) { return m_tile_y; }

int Santa::LevelObject::get_width(void) { return m_width; }

int Santa::LevelObject::get_height(void) { return m_height; }

Santa::Mask *Santa::LevelObject::get_mask(void) { return m_mask; }

bool Santa::LevelObject::exists(void) { return m_exists; }

bool Santa::LevelObject::is_hidden(void) { return m_hidden; }

int Santa::LevelObject::get_level_x(void) {
  if (m_type == CloudObject) {
    return m_cloud->get_level_x();
  } else if (m_type == BalloonObject) {
    return m_balloon->get_level_x();
  } else if (m_type == AngelObject) {
    return m_angel->get_level_x();
  } else if (m_type == GoblinObject) {
    return m_goblin->get_level_x();
  } else if (m_type == GoblinSnowballObject) {
    return m_goblin_snowball->get_level_x();
  } else if (m_type == SnowmanObject) {
    return m_snowman->get_level_x();
  } else if (m_type == FinishObject) {
    return m_finish->get_level_x();
  } else {
    return 0;
  }
}

int Santa::LevelObject::get_y(void) {
  if (m_type == CloudObject) {
    return m_cloud->get_y();
  } else if (m_type == BalloonObject) {
    return m_balloon->get_y();
  } else if (m_type == AngelObject) {
    return m_angel->get_y();
  } else if (m_type == GoblinObject) {
    return m_goblin->get_y();
  } else if (m_type == GoblinSnowballObject) {
    return m_goblin_snowball->get_y();
  } else if (m_type == SnowmanObject) {
    return m_snowman->get_y();
  } else if (m_type == FinishObject) {
    return m_finish->get_y();
  } else {
    return 0;
  }
}

int Santa::LevelObject::get_frame(void) {
  if (m_type == CloudObject) {
    return m_cloud->get_frame();
  } else if (m_type == BalloonObject) {
    return m_balloon->get_frame();
  } else if (m_type == AngelObject) {
    return m_angel->get_frame();
  } else if (m_type == GoblinObject) {
    return m_goblin->get_frame();
  } else if (m_type == GoblinSnowballObject) {
    return m_goblin_snowball->get_frame();
  } else if (m_type == SnowmanObject) {
    return m_snowman->get_frame();
  } else if (m_type == FinishObject) {
    return m_finish->get_frame();
  } else {
    return 0;
  }
}

Santa::Cloud *Santa::LevelObject::get_cloud(void) { return m_cloud; }

Santa::Balloon *Santa::LevelObject::get_balloon(void) { return m_balloon; }

Santa::Angel *Santa::LevelObject::get_angel(void) { return m_angel; }

Santa::Goblin *Santa::LevelObject::get_goblin(void) { return m_goblin; }

Santa::GoblinSnowball *Santa::LevelObject::get_goblin_snowball(void) {
  return m_goblin_snowball;
}

Santa::Snowman *Santa::LevelObject::get_snowman(void) { return m_snowman; }

Santa::Finish *Santa::LevelObject::get_finish(void) { return m_finish; }

SDL_Surface *Santa::LevelObject::get_surface(void) { return m_surface; }

void Santa::LevelObject::set_surface(SDL_Surface *surface) {
  m_surface = surface;
}

int Santa::LevelObject::get_frame_count(void) { return m_frame_count; }

void Santa::LevelObject::set_frame_count(int frame_count) {
  m_frame_count = frame_count;
}
