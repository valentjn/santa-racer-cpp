/*
 *      Santa Racer
 *      game.cpp
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

#include "game.hpp"

#include "draw.hpp"
#include "globals.hpp"
#include "random.hpp"
#include "sound.hpp"

SantaRacer::Game::Game(void) { m_initialized = false; }

SantaRacer::Game::~Game(void) {
  int i;

  if (!m_initialized) {
    return;
  }

  SDL_FreeSurface(m_highscore_bg);

  for (i = 0; i < max_gift_count; i++) {
    delete gifts[i];
  }

  delete[] gifts;

  for (i = 0; i < snowflake_count; i++) {
    delete snowflakes[i];
  }

  delete[] snowflakes;
  delete sleigh;
  delete level;
  delete landscape;
  delete score;

  m_initialized = false;
}

void SantaRacer::Game::init(void) {
  int i;

  m_last_time = 0;

  landscape = new Landscape();
  level = new Level(Setup::std_level_map, Setup::std_level_objects_map,
                    Setup::std_level_width, Setup::std_level_height);

  sleigh = new Sleigh();
  sleigh->reset_stars();
  snowflakes = new Snowflake *[snowflake_count];

  for (i = 0; i < snowflake_count; i++) {
    snowflakes[i] = new Snowflake();
  }

  gifts = new Gift *[max_gift_count];
  for (i = 0; i < max_gift_count; i++) {
    gifts[i] = new Gift();
  }

  score = new Score();

  m_highscore_bg =
      SDL_CreateRGBSurface(SDL_SWSURFACE, 400, 300, 32, 0, 0, 0, 0);

  if (m_highscore_bg == NULL) {
    Output::fatal_error("could not create RGB surface: %s\n", SDL_GetError());
  }
  SDL_SetAlpha(m_highscore_bg, SDL_SRCALPHA, 128);

  m_quit = false;
  m_fire_pressed = false;
  m_up_pressed = false;
  m_down_pressed = false;
  m_left_pressed = false;
  m_right_pressed = false;
  m_escape_pressed = false;

  mode = menu_mode;
  fps = 0;
  m_last_fps_update_time = 0;
  m_frame_counter = 0;

  m_key_state = SDL_GetKeyState(NULL);

  countdown_mode = false;
  countdown_start_time = 0;

  m_bell_time = SDL_GetTicks() + Random::rnd(bell_time_min, bell_time_max);
  m_dog_time = SDL_GetTicks() + Random::rnd(dog_time_min, dog_time_max);

  m_bonus_time_start = 0;

  m_last_gift_time = 0;

  m_highscore_score = 0;
  m_highscore_place = 0;
  m_highscore_name = "";
  m_highscore_caret_blink_time = 0;

  m_initialized = true;
}

void SantaRacer::Game::loop(void) {
  while (!m_quit) {
    process_events();
    check_keys();
    logic();
    draw();
    frame_tick();
  }
}

void SantaRacer::Game::process_events(void) {
  SDL_Event event;
  char ch;

  while (SDL_PollEvent(&event)) {
    if (event.type == SDL_QUIT) {
      m_quit = true;
      break;
    } else if (event.key.type == SDL_KEYDOWN) {
      if (mode == new_highscore_mode) {
        if ((event.key.keysym.sym == SDLK_BACKSPACE) ||
            (event.key.keysym.sym == SDLK_DELETE)) {
          if (m_highscore_name.length() > 0) {
            m_highscore_name =
                m_highscore_name.erase(m_highscore_name.length() - 1);
            m_highscore_caret_blink_time = SDL_GetTicks();
          }
        } else if (event.key.keysym.sym == SDLK_RETURN) {
          Config::highscores[m_highscore_place].name = m_highscore_name;
          return_to_menu();
          mode = highscore_mode;

        } else if ((event.key.keysym.unicode & 0xff80) == 0) {
          ch = event.key.keysym.unicode & 0x7f;

          if (((ch >= 65) && (ch <= 90)) || ((ch >= 97) && (ch <= 120)) ||
              ((ch >= 48) && (ch <= 57)) || (ch == 64) || (ch == 95) ||
              (ch == 45) || (ch == 46) || (ch == 47) || (ch == 58)) {
            if (m_highscore_name.length() < highscore_name_max_length) {
              m_highscore_name += event.key.keysym.unicode;
              m_highscore_caret_blink_time = SDL_GetTicks();
            }
          }
        }
      }
    }
  }
}

void SantaRacer::Game::check_keys(void) {
  SDLMod mod_state;
  int i;
  int result;
  int drunken_factor;

  mod_state = SDL_GetModState();
  if (m_key_state[SDLK_c] && (mod_state & KMOD_CTRL)) {
    m_quit = true;

  } else if (mod_state & KMOD_CTRL && mod_state & KMOD_ALT &&
             m_key_state[SDLK_RETURN]) {
    result = SDL_WM_ToggleFullScreen(Setup::screen);
    if (!result) {
      Output::fatal_error("could not toggle fullscreen mode: %s\n",
                          SDL_GetError());
    }
  }

  if (mode == menu_mode) {
    if (m_key_state[SDLK_F1]) {
      mode = help1_mode;
    } else if (m_key_state[SDLK_F2]) {
      mode = help2_mode;
    } else if (m_key_state[SDLK_F3]) {
      mode = highscore_mode;
    } else if (m_key_state[SDLK_F5]) {
      start_new_game();
    } else if (m_key_state[SDLK_ESCAPE] && !m_escape_pressed) {
      m_quit = true;
    }

  } else if (mode == help1_mode || mode == help2_mode) {
    if (m_key_state[SDLK_F1]) {
      mode = help1_mode;
    } else if (m_key_state[SDLK_F2]) {
      mode = help2_mode;
    } else if (m_key_state[SDLK_SPACE] ||
               (m_key_state[SDLK_ESCAPE] && !m_escape_pressed)) {
      mode = menu_mode;
    }

  } else if (mode == highscore_mode) {
    if (m_key_state[SDLK_F1]) {
      mode = help1_mode;
    } else if (m_key_state[SDLK_F2]) {
      mode = help2_mode;
    } else if (m_key_state[SDLK_SPACE] ||
               (m_key_state[SDLK_ESCAPE] && !m_escape_pressed)) {
      mode = menu_mode;
    }

  } else if ((mode == running_game) && !countdown_mode) {
    if (sleigh->is_drunken()) {
      drunken_factor = -1;
    } else {
      drunken_factor = 1;
    }

    if (m_key_state[SDLK_UP]) {
      sleigh->set_speed_y(drunken_factor * -1);
    } else if (m_key_state[SDLK_DOWN]) {
      sleigh->set_speed_y(drunken_factor * 1);
    } else {
      sleigh->set_speed_y(0);
    }
    if (m_key_state[SDLK_LEFT]) {
      sleigh->set_speed_x(drunken_factor * -1);
    } else if (m_key_state[SDLK_RIGHT]) {
      sleigh->set_speed_x(drunken_factor * 1);
    } else {
      sleigh->set_speed_x(0);
    }
    if (m_key_state[SDLK_SPACE] && !m_fire_pressed &&
        (m_last_gift_time + gift_wait_duration < SDL_GetTicks()) &&
        !sleigh->is_unmovable()) {
      i = 0;
      while (i < max_gift_count && gifts[i]->exists()) {
        i++;
      }
      if (i < max_gift_count) {
        gifts[i]->reinit();
        m_last_gift_time = SDL_GetTicks();
      }
    }

    if (m_key_state[SDLK_ESCAPE] && !m_escape_pressed) {
      return_to_menu();
    }
  }

  m_left_pressed = m_key_state[SDLK_LEFT];
  m_right_pressed = m_key_state[SDLK_RIGHT];
  m_up_pressed = m_key_state[SDLK_UP];
  m_down_pressed = m_key_state[SDLK_DOWN];
  m_fire_pressed = m_key_state[SDLK_SPACE];
  m_escape_pressed = m_key_state[SDLK_ESCAPE];
}

void SantaRacer::Game::logic(void) {
  int i;
  int time_diff;
  int countdown_number;
  int x;
  LevelObject *level_object;
  LevelObject::ObjectType type;
  Balloon::BalloonType balloon_type;

  int points;
  std::string snd_name;

  if (mode == running_game) {
    if (sleigh->is_colliding()) {
      Output::debug("collision detected: %i\n", SDL_GetTicks());

      sleigh->collided();
      score->add_damage(collision_damage);
      landscape->set_pause(true);
      level->set_pause(true);
      sleigh->set_pause(true);

      if (Random::rnd(0, 1) == 0) {
        snd_name = "damaged1";
      } else {
        snd_name = "damaged2";
      }

      Sound::play_panned_x(snd_name, sleigh->get_x());
    }

    level_object = sleigh->touched_level_object();
    if (level_object != NULL) {
      type = level_object->get_type();
      x = level_object->get_level_x() - Setup::game->level->get_offset();

      if (type == LevelObject::CloudObject) {
        Output::debug("touched cloud: %i\n", SDL_GetTicks());
        score->add_damage(collision_damage);
        Sound::play_panned_x("electrified", x);
        sleigh->electrified();

      } else if (type == LevelObject::BalloonObject) {
        balloon_type = level_object->get_balloon()->get_type();

        if (balloon_type == Balloon::PointsBalloon) {
          score->add_points(points_balloon_pts);
          Sound::play_panned_x("success", x);

        } else if (balloon_type == Balloon::CashBalloon) {
          score->add_damage(-cash_balloon_pts);
          Sound::play_panned_x("cash", x);

        } else if (balloon_type == Balloon::GiftBalloon) {
          m_bonus_time_start = SDL_GetTicks();
          Sound::play_panned_x("bonus", x);

        } else if (balloon_type == Balloon::ShieldBalloon) {
          sleigh->shield();
          Sound::play_panned_x("shield", x);

        } else if (balloon_type == Balloon::ChampagneBalloon) {
          sleigh->drunken();
          Sound::play_panned_x("drunken", x);
        }

        level_object->hide();

      } else if ((type == LevelObject::AngelObject) ||
                 (type == LevelObject::GoblinObject) ||
                 (type == LevelObject::GoblinSnowballObject) ||
                 (type == LevelObject::SnowmanObject)) {
        score->add_damage(collision_damage);
        Sound::play_panned_x("hit", x);
        sleigh->hit();
      }
    }

    if (score->get_remaining_secs() <= 0) {
      mode = lost_time_mode;
      m_won_lost_time = SDL_GetTicks();
      Sound::play("lost");
      return;
    }

    if (score->get_damage() > max_damage) {
      mode = lost_damage_mode;
      m_won_lost_time = SDL_GetTicks();
      Sound::play("lost");
      return;
    }
  } else if (mode == won_mode) {
    if (m_won_lost_time + won_splash_duration <= SDL_GetTicks()) {
      for (i = 0; i < 10; i++) {
        if (m_highscore_score > Config::highscores[i].score) {
          mode = new_highscore_mode;
          m_highscore_place = i;
          m_highscore_caret_blink_time = SDL_GetTicks();
          break;
        }
      }

      if (mode == new_highscore_mode) {
        for (i = 9; i > m_highscore_place; i--) {
          Config::highscores[i] = Config::highscores[i - 1];
        }
        Config::highscores[m_highscore_place].name = "";
        Config::highscores[m_highscore_place].score = m_highscore_score;
      } else {
        return_to_menu();
        mode = highscore_mode;
      }
    }

    return;
  } else if ((mode == lost_time_mode) || (mode == lost_damage_mode)) {
    if (m_won_lost_time + lost_splash_duration <= SDL_GetTicks()) {
      return_to_menu();
    }

    return;
  }

  for (i = 0; i < snowflake_count; i++) {
    snowflakes[i]->move();
  }

  for (i = 0; i < max_gift_count; i++) {
    if (!gifts[i]->exists()) {
      continue;
    }

    gifts[i]->move();
    x = gifts[i]->get_level_x() - Setup::game->level->get_offset();

    if (gifts[i]->query_hit_ground()) {
      score->add_damage(gift_ground_damage);
      Sound::play_panned_x("gift_missed", x);

    } else if (gifts[i]->query_hit_chimney()) {
      points = gifts[i]->get_points();

      if ((m_bonus_time_start != 0) &&
          (m_bonus_time_start + bonus_duration > SDL_GetTicks())) {
        points *= 2;
        gifts[i]->double_points();
      }

      score->add_points(points);
      Sound::play_panned_x("success", x);
    }
  }

  landscape->move();
  level->move();
  level->move_objects();
  sleigh->stars_move();

  if (countdown_mode) {
    time_diff = SDL_GetTicks() - countdown_start_time;
    countdown_number = countdown_start - floor(time_diff / 1000);
    if (countdown_number <= 0) {
      countdown_mode = false;
      landscape->set_pause(false);
      level->set_pause(false);
      sleigh->set_pause(false);
      sleigh->set_alpha(255);
    }

    score->reset(total_time_secs);
  }

  if (sleigh->get_pause() && !sleigh->is_unmovable()) {
    landscape->set_pause(false);
    level->set_pause(false);
    sleigh->set_pause(false);
  }

  for (i = 0; i < Level::max_level_object_count; i++) {
    level_object = level->get_level_object(i);

    if (level_object->exists() &&
        (level_object->get_type() == LevelObject::GoblinObject) &&
        level_object->get_goblin()->query_snowball_thrown()) {
      x = level_object->get_level_x() - Setup::game->level->get_offset();
      Sound::play_panned_x("snowball", x);
    } else if (level_object->exists() &&
               (level_object->get_type() == LevelObject::SnowmanObject) &&
               level_object->get_snowman()->query_triggered()) {
      x = level_object->get_level_x() - Setup::game->level->get_offset();
      Sound::play_panned_x("snowman", x);
    } else if (level_object->exists() &&
               (level_object->get_type() == LevelObject::FinishObject) &&
               level_object->get_finish()->reached() &&
               ((mode == running_game) || (mode == menu_mode))) {
      if (mode == running_game) {
        mode = won_mode;
        m_won_lost_time = SDL_GetTicks();
        m_highscore_score = score->get_score();
        Sound::play("won");

        return;
      } else {
        return_to_menu();
      }
    }
  }

  if (SDL_GetTicks() >= m_bell_time) {
    Sound::play_volume("bell", bell_volume);
    m_bell_time = SDL_GetTicks() + Random::rnd(bell_time_min, bell_time_max);
  }
  if (SDL_GetTicks() >= m_dog_time) {
    Sound::play_volume("dog", dog_volume);
    m_dog_time = SDL_GetTicks() + Random::rnd(dog_time_min, dog_time_max);
  }
}

void SantaRacer::Game::draw(void) {
  int i;
  char string[11];

  if (mode == help1_mode) {
    Draw::copy(Setup::images["help1"], Setup::screen, 0, 0);

  } else if (mode == help2_mode) {
    Draw::copy(Setup::images["help2"], Setup::screen, 0, 0);

  } else if (mode == won_mode) {
    Draw::copy(Setup::images["finished"], Setup::screen, 0, 0);

  } else if (mode == new_highscore_mode) {
    Draw::copy(Setup::images["finished"], Setup::screen, 0, 0);
    draw_highscores();

  } else if (mode == lost_time_mode) {
    Draw::copy(Setup::images["lost_time"], Setup::screen, 0, 0);

  } else if (mode == lost_damage_mode) {
    Draw::copy(Setup::images["lost_damage"], Setup::screen, 0, 0);

  } else {
    Draw::copy(Setup::images["bg"], Setup::screen, 0, 0);
    landscape->draw();
    level->draw_ballons();
    level->draw();
    sleigh->draw();
    level->draw_objects();

    for (i = 0; i < max_gift_count; i++) {
      if (gifts[i]->exists()) {
        gifts[i]->draw();
      }
    }

    SDL_LockSurface(Setup::screen);

    for (i = 0; i < snowflake_count; i++) {
      snowflakes[i]->draw();
    }

    SDL_UnlockSurface(Setup::screen);

    draw_text();

    if (mode == highscore_mode) {
      draw_highscores();
    }
  }

  if (Setup::debug_mode) {
    snprintf(string, 10, "%i FPS", fps);
    Setup::text->draw(string, Setup::screen_width, Setup::screen_height,
                      Text::BottomRight);
  }

  if ((mode == menu_mode) || (mode == highscore_mode)) {
    Draw::copy(Setup::images["logo"], Setup::screen, 0,
               Setup::screen_height - Setup::images["logo"]->h);
  }

  SDL_Flip(Setup::screen);
}

void SantaRacer::Game::frame_tick(void) {
  int cur_time;

  cur_time = SDL_GetTicks();
  if (m_last_fps_update_time + 1000 < cur_time) {
    fps = (m_frame_counter * 1000) / (cur_time - m_last_fps_update_time);
    // debug("%i", frame_counter);
    m_last_fps_update_time = cur_time;
    m_frame_counter = 0;
  }

  fps_delay();
  m_frame_counter++;
}

void SantaRacer::Game::fps_delay(void) {
  float cur_fps;
  int cur_delay;
  int cur_time;
  float target_delay;
  int exec_delay;

  cur_time = SDL_GetTicks();

  if (m_last_time != 0) {
    cur_delay = cur_time - m_last_time;
    cur_fps = 1000.0 / cur_delay;
    target_delay = 1000.0 / Setup::target_fps;
    if (cur_delay < target_delay) {
      exec_delay = round((target_delay - cur_delay));
      // debug("%f\n", target_delay - cur_delay);
      // debug("%i\n", exec_delay);
      SDL_Delay(exec_delay);
    }
  }

  m_last_time = cur_time;
}

void SantaRacer::Game::start_new_game(void) {
  int i;

  mode = running_game;

  countdown_mode = true;
  countdown_start_time = SDL_GetTicks();

  sleigh->reset();
  sleigh->reset_stars();
  sleigh->set_menu_mode(false);
  sleigh->set_alpha(128);
  sleigh->set_x(sleigh_start_x);
  sleigh->set_y(sleigh_start_y);
  sleigh->set_pause(true);

  level->set_menu_mode(false);
  level->set_offset(0);
  level->set_pause(true);
  level->clear_objects();

  landscape->reset();
  landscape->set_pause(true);

  sleigh->reset_stars();

  for (i = 0; i < snowflake_count; i++) {
    snowflakes[i]->reinit(true);
  }

  for (i = 0; i < max_gift_count; i++) {
    gifts[i]->reset();
  }

  score->reset(total_time_secs);
}

void SantaRacer::Game::return_to_menu(void) {
  int i;

  mode = menu_mode;

  countdown_mode = false;

  sleigh->reset();
  sleigh->reset_stars();
  sleigh->set_menu_mode(true);

  level->set_menu_mode(true);
  level->set_offset(0);
  level->set_pause(false);
  level->clear_objects();

  landscape->reset();
  landscape->set_pause(false);

  sleigh->reset_stars();

  for (i = 0; i < snowflake_count; i++) {
    snowflakes[i]->reinit(true);
  }

  for (i = 0; i < max_gift_count; i++) {
    gifts[i]->reset();
  }
}

void SantaRacer::Game::draw_text(void) {
  int time_diff;
  int countdown_number;
  char string[11];

  if (mode == menu_mode || mode == highscore_mode) {
    Setup::text->draw("F1/F2 - Hilfe", 0, 0, Text::TopLeft);
    Setup::text->draw("F3 - Highscores", Setup::screen_width / 2, 0,
                      Text::TopCenter);
    Setup::text->draw("F5 - Spielen", Setup::screen_width, 0, Text::TopRight);

    return;
  }

  score->draw();

  if (countdown_mode) {
    time_diff = SDL_GetTicks() - countdown_start_time;
    countdown_number = countdown_start - floor(time_diff / 1000);
    if (countdown_number <= 0) {
      countdown_number = 1;
    }
    snprintf(string, 10, "%i", countdown_number);
    Setup::text->draw(string, sleigh->get_x() - 10,
                      sleigh->get_y() + sleigh->get_height() / 2,
                      Text::CenterRight);
  }
}

void SantaRacer::Game::draw_highscores(void) {
  int x;
  int y;
  int line_spacing;
  int i;
  char score_string[11];
  std::string name;

  x = Setup::screen_width / 2 - highscore_width / 2;
  y = Setup::screen_height / 2 - highscore_height / 2;
  line_spacing = (highscore_height - Setup::text->get_line_height() -
                  2 * highscore_padding_y) /
                 9;

  Draw::blit(m_highscore_bg, 0, 0, highscore_width, highscore_height,
             Setup::screen, x, y);

  x += highscore_padding_x;
  y += highscore_padding_y;

  for (i = 0; i < 10; i++) {
    snprintf(score_string, 10, "%i", Config::highscores[i].score);

    if ((mode == new_highscore_mode) && (i == m_highscore_place)) {
      if ((SDL_GetTicks() - m_highscore_caret_blink_time) %
              (2 * highscore_caret_blink_duration) <
          highscore_caret_blink_duration) {
        name = m_highscore_name + "_";
      } else {
        name = m_highscore_name;
      }
    } else {
      name = Config::highscores[i].name;
    }

    Setup::text->draw(name.c_str(), x, y, Text::TopLeft);

    Setup::text->draw(score_string,
                      x + highscore_width - 2 * highscore_padding_x, y,
                      Text::TopRight);

    y += line_spacing;
  }
}
