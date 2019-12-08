/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include <cstdlib>
#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

#include "SantaRacer/Options.hpp"
#include "SantaRacer/Printer.hpp"

namespace fs = std::filesystem;

namespace SantaRacer {

Options::Options() : fullScreen(false), verbose(false) {
  std::ifstream f(highscoresPath);

  for (size_t i = 0; i < 10; i++) {
    Highscore highscore;
    f >> highscore.name;
    f >> highscore.score;
    highscores.push_back(highscore);
  }
}

Options::~Options() {
  if (!highscores.empty()) {
    std::ofstream f(highscoresPath);

    for (size_t i = 0; i < highscores.size(); i++) {
      if (i > 0) {
        f << " ";
      }

      f << highscores[i].name << " " << highscores[i].score;
    }
  }
}

void Options::checkArguments(int argc, char *argv[]) {
  for (size_t i = 1; i < static_cast<size_t>(argc); i++) {
    std::string argument(argv[i]);

    if (argument == "--help") {
      Printer::print("Santa Racer\n");
      Printer::print("- an open-source clone of \"Nikolaus Express 2000\"\n");
      Printer::print(
          "Source code: Copyright (C) 2010--2019 Julian Valentin. "
          "Licensed under GPL.\n"
          "This does not apply to external material "
          "(textures, sounds, music), as these may be subject "
          "to be intellectual property of third parties.\n");
      Printer::print("\n");
      Printer::print("-f, --fullscreen  enable fullscreen mode\n");
      Printer::print("-v, --verbose     enable verbose mode\n");
      Printer::print("-h, --help        display help message\n");
      Printer::print("--version         display version information\n");
      Printer::print("--license         display license information\n");
      exit(0);
    } else if (argument == "-f" || argument == "--fullscreen") {
      fullScreen = true;
    } else if (argument == "-v" || argument == "--verbose") {
      verbose = true;
    } else if (argument == "--license") {
      Printer::print("Copyright (C) 2010--2019 Julian Valentin.\n\n");
      Printer::print(
          "This program is free software: you can redistribute it and/or modify\n"
          "it under the terms of version 3 of the GNU General Public License as published by\n"
          "the Free Software Foundation.\n\n");
      Printer::print(
          "This program is distributed in the hope that it will be useful,\n"
          "but WITHOUT ANY WARRANTY; without even the implied warranty of\n"
          "MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the\n"
          "GNU General Public License for more details.\n\n");
      Printer::print(
          "You should have received a copy of the GNU General Public License\n"
          "along with this program.  If not, see <http://www.gnu.org/licenses/>.\n\n");
      exit(0);
    } else if (argument == "--version") {
      Printer::print("Santa Racer 1.0\n");
      exit(0);
    }
  }
}

bool Options::isFullScreen() const {
  return fullScreen;
}

bool Options::isVerbose() const {
  return verbose;
}

std::vector<Options::Highscore>& Options::getHighscores() {
  return highscores;
}

}  // namespace SantaRacer
