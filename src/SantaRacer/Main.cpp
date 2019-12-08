/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include "SantaRacer/Game.hpp"
#include "SantaRacer/Options.hpp"

int main(int argc, char *argv[]) {
  SantaRacer::Options options;
  options.checkArguments(argc, argv);

  SantaRacer::Game game(std::move(options));
  game.loop();

  return 0;
}
