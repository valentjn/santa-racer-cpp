/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

#include <string>

namespace SantaRacer {

class Printer {
 public:
  template <typename... ArgumentType>
  static void debug(std::string text, ArgumentType... arguments);

  template <typename... ArgumentType>
  static void print(std::string text, ArgumentType... arguments);

  template <typename... ArgumentType>
  static void fatalError(std::string text, ArgumentType... arguments);

  template <typename... ArgumentType>
  static std::string printToString(std::string text, ArgumentType... arguments);

  static bool isVerbose();
  static void setVerbose(bool verbose);

 protected:
  static bool verbose;
};

}  // namespace SantaRacer

#include "SantaRacer/Printer.inl"
