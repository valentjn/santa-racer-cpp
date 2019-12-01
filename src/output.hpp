/*
 *      Santa Racer
 *      output.hpp
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

#ifndef SANTA_OUTPUT_H
#define SANTA_OUTPUT_H

#include <string>

namespace SantaRacer {
namespace Output {

void fatal_error(const char *message, ...);
void print(const char *message, ...);
void debug(const char *message, ...);
std::string string_printf(const char *format, ...);
std::string string_vprintf(const char *format, va_list args);

}  // namespace Output
}  // namespace SantaRacer

#endif
