/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
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
