/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include "SantaRacer/Output.hpp"

#include <cstdarg>
#include <iostream>
#include <string>

#include "SantaRacer/Globals.hpp"

namespace SantaRacer {
namespace Output {

void m_fatal_error(std::string message);
void m_print(std::string message);

}  // namespace Output
}  // namespace SantaRacer

void SantaRacer::Output::fatal_error(const char *message, ...) {
  std::string result;
  va_list args;

  va_start(args, message);
  result = string_vprintf(message, args);
  va_end(args);
  m_fatal_error(result);
}

void SantaRacer::Output::m_fatal_error(std::string message) {
  std::cerr << message << std::flush;
  exit(1);
}

void SantaRacer::Output::print(const char *message, ...) {
  std::string result;
  va_list args;

  va_start(args, message);
  result = string_vprintf(message, args);
  va_end(args);
  m_print(result);
}

void SantaRacer::Output::debug(const char *message, ...) {
  std::string result;
  va_list args;

  if (!Setup::debug_mode && !Setup::verbose) {
    return;
  }

  va_start(args, message);
  result = string_vprintf(message, args);
  va_end(args);
  m_print(result);
}

void SantaRacer::Output::m_print(std::string message) {
  std::cout << message << std::flush;
}

std::string SantaRacer::Output::string_printf(const char *format, ...) {
  std::string result;
  va_list args;

  va_start(args, format);
  result = string_vprintf(format, args);
  va_end(args);
  return std::string(result);
}

std::string SantaRacer::Output::string_vprintf(const char *format, va_list args) {
  char text[1000];

  vsnprintf(text, 1000, format, args);
  return std::string(text);
}
