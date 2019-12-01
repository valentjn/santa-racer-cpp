/*
 *      Santa Racer
 *      output.cpp
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

#include "output.hpp"

#include <cstdarg>
#include <iostream>
#include <string>

#include "globals.hpp"

namespace Santa {
namespace Output {

void m_fatal_error(std::string message);
void m_print(std::string message);

}  // namespace Output
}  // namespace Santa

void Santa::Output::fatal_error(const char *message, ...) {
  std::string result;
  va_list args;

  va_start(args, message);
  result = string_vprintf(message, args);
  va_end(args);
  m_fatal_error(result);
}

void Santa::Output::m_fatal_error(std::string message) {
  std::cerr << message << std::flush;
  exit(1);
}

void Santa::Output::print(const char *message, ...) {
  std::string result;
  va_list args;

  va_start(args, message);
  result = string_vprintf(message, args);
  va_end(args);
  m_print(result);
}

void Santa::Output::debug(const char *message, ...) {
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

void Santa::Output::m_print(std::string message) {
  std::cout << message << std::flush;
}

std::string Santa::Output::string_printf(const char *format, ...) {
  std::string result;
  va_list args;

  va_start(args, format);
  result = string_vprintf(format, args);
  va_end(args);
  return std::string(result);
}

std::string Santa::Output::string_vprintf(const char *format, va_list args) {
  char text[1000];

  vsnprintf(text, 1000, format, args);
  return std::string(text);
}
