/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include "SantaRacer/Printer.hpp"

namespace SantaRacer {

bool Printer::verbose =
#ifdef DEBUG
    true;
#else
    false;
#endif  // DEBUG

bool Printer::isVerbose() {
  return verbose;
}

void Printer::setVerbose(bool verbose) {
  Printer::verbose = verbose;
}

}  // namespace SantaRacer
