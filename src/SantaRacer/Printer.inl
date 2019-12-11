/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include <cstdio>
#include <iostream>
#include <string>

#include "SantaRacer/Printer.hpp"

namespace SantaRacer {

template <typename... ArgumentType>
void Printer::debug(std::string text, ArgumentType... arguments) {
  if (verbose) {
    std::cout << printToString(text, arguments...) << std::flush;
  }
}

template <typename... ArgumentType>
void Printer::print(std::string text, ArgumentType... arguments) {
  std::cout << printToString(text, arguments...) << std::flush;
}

template <typename... ArgumentType>
void Printer::fatalError(std::string text, ArgumentType... arguments) {
  std::cerr << printToString(text, arguments...) << std::flush;
  exit(1);
}

template <typename... ArgumentType>
std::string Printer::printToString(std::string text, ArgumentType... arguments) {
  if (text.find("%n") != std::string::npos) {
    return "insecure string formatting prevented";
  }

  #pragma clang diagnostic push
  #pragma clang diagnostic ignored "-Wformat-security"
  const size_t size = std::snprintf(nullptr, 0, text.c_str(), arguments...) + 1;
  char formattedText[size];
  std::snprintf(formattedText, size, text.c_str(), arguments...);
  #pragma clang diagnostic pop

  return std::string(formattedText);
}

}  // namespace SantaRacer
