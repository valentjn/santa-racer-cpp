/*      
 *      Santa Racer
 *      random.cpp
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

#include "globals.hpp"
#include "random.hpp"

// both min and max inclusive
int Santa::Random::rnd(int min, int max) {
    return int(rand() / (float(RAND_MAX) + 1) * (max - min + 1)) + min;
}

void Santa::Random::seed(void) {
    srand(time(NULL));
}
