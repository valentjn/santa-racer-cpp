/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include "SantaRacer/LevelObject/LevelObject.hpp"

#include "SantaRacer/Globals.hpp"

namespace SantaRacer {
namespace LevelObject {

LevelObject::LevelObject(void) {
  m_cloud = new Cloud(this);
  m_balloon = new Balloon(this);
  m_angel = new Angel(this);
  m_goblin = new Goblin(this);
  m_goblin_snowball = new GoblinSnowball(this);
  m_snowman = new Snowman(this);
  m_finish = new Finish(this);

  reset();
}

LevelObject::~LevelObject(void) {
  delete m_cloud;
  delete m_balloon;
  delete m_angel;
  delete m_goblin;
  delete m_goblin_snowball;
  delete m_snowman;
  delete m_finish;
  delete m_mask;
}

void LevelObject::reinit(int tile_x, int tile_y, int gfx_index) {
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

void LevelObject::reset(void) {
  // Output::debug("LevelObject::reset, tile_x %i, tile_y %i\n", m_tile_x,
  // m_tile_y);
  m_exists = false;
  m_type = EmptyObject;

  m_tile_x = 0;
  m_tile_y = 0;

  m_width = 0;
  m_height = 0;
  m_mask = nullptr;
  m_hidden = false;
}

void LevelObject::draw(void) {
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

void LevelObject::move(void) {
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

void LevelObject::hide(void) { m_hidden = true; }

LevelObject::ObjectType LevelObject::get_type(void) {
  return m_type;
}

int LevelObject::get_tile_x(void) { return m_tile_x; }

int LevelObject::get_tile_y(void) { return m_tile_y; }

int LevelObject::get_width(void) { return m_width; }

int LevelObject::get_height(void) { return m_height; }

SantaRacer::Mask *LevelObject::get_mask(void) { return m_mask; }

bool LevelObject::exists(void) { return m_exists; }

bool LevelObject::is_hidden(void) { return m_hidden; }

int LevelObject::get_level_x(void) {
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

int LevelObject::get_y(void) {
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

int LevelObject::get_frame(void) {
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

Cloud *LevelObject::get_cloud(void) { return m_cloud; }

Balloon *LevelObject::get_balloon(void) { return m_balloon; }

Angel *LevelObject::get_angel(void) { return m_angel; }

Goblin *LevelObject::get_goblin(void) { return m_goblin; }

GoblinSnowball *LevelObject::get_goblin_snowball(void) {
  return m_goblin_snowball;
}

Snowman *LevelObject::get_snowman(void) { return m_snowman; }

Finish *LevelObject::get_finish(void) { return m_finish; }

SDL_Surface *LevelObject::get_surface(void) { return m_surface; }

void LevelObject::set_surface(SDL_Surface *surface) {
  m_surface = surface;
}

int LevelObject::get_frame_count(void) { return m_frame_count; }

void LevelObject::set_frame_count(int frame_count) {
  m_frame_count = frame_count;
}

}  // namespace LevelObject
}  // namespace SantaRacer
