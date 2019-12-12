/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

#include <filesystem>
#include <string>
#include <vector>

namespace SantaRacer {

class Options {
 public:
  struct Highscore {
    std::string name;
    int score;
  };

  Options();
  Options(const Options& other) = delete;
  Options(Options&& other) = default;
  ~Options();

  Options& operator=(const Options& other) = delete;
  Options& operator=(Options&& other) = default;

  void checkArguments(int argc, char *argv[]);

  bool isFullScreen() const;
  bool isSoundEnabled() const;
  bool isVerbose() const;
  std::vector<Highscore>& getHighscores();

 protected:
  bool fullScreen;
  bool soundEnabled;
  bool verbose;
  std::vector<Highscore> highscores;

  static const std::filesystem::path highscoresPath;
};

}  // namespace SantaRacer
