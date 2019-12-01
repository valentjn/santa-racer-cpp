/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include "Args.hpp"

#include "Globals.hpp"

#include <string>

void SantaRacer::Args::check_args(int argc, char *argv[]) {
  int i;
  std::string arg;

  Setup::fullscreen = false;
  Setup::verbose = false;

  if (argc == 1) {
    return;
  }

  for (i = 1; i < argc; i++) {
    arg = std::string(argv[i]);

    if (arg == "--help") {
      Output::print("Santa Racer\n");
      Output::print("- a free port of \"Nikolaus Express\"\n");
      Output::print(
          "Source code: Copyright (C) 2010 Julian Valentin. "
          "Licensed under GPL.\n"
          "This does not apply to external material "
          "(textures, sounds, music), as these may be subject "
          "to be intellectual property of third parties.\n");
      Output::print("\n");
      Output::print("-f, --fullscreen  enable fullscreen mode\n");
      Output::print("-v, --verbose     enable verbose mode\n");
      Output::print("-h, --help        display help message\n");
      Output::print("--version         display version information\n");
      Output::print("--license         display license information\n");
      exit(0);
    } else if (arg == "-f" || arg == "--fullscreen") {
      Setup::fullscreen = true;
    } else if (arg == "-v" || arg == "--verbose") {
      Setup::verbose = true;
    } else if (arg == "--license") {
      Output::print("Copyright (C) 2010 Julian Valentin.\n\n");
      Output::print(
          "This program is free software: you can "
          "redistribute it and/or modify\n"
          "it under the terms of the GNU General Public License "
          "as published by\n"
          "the Free Software Foundation, either version 3 of the "
          "License, or\n"
          "(at your option) any later version.\n\n");
      Output::print(
          "This program is distributed in the hope that it "
          "will be useful,\n"
          "but WITHOUT ANY WARRANTY; without even the implied "
          "warranty of\n"
          "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  "
          "See the\n"
          "GNU General Public License for more details.\n\n");
      Output::print(
          "You should have received a copy of the GNU General "
          "Public License\n"
          "along with this program.  If not, see "
          "<http://www.gnu.org/licenses/>.\n\n");
      exit(0);
    } else if (arg == "--version") {
      Output::print("Santa Racer 1.0\n");
      exit(0);
    }
  }
}
