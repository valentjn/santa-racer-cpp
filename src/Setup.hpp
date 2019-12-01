/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

namespace SantaRacer {
namespace Setup {

void santa_setup(void);
bool load_images(void);
bool load_text(void);
bool load_level(void);
bool load_level_objects(void);
bool load_chimneys(void);
bool load_sounds(void);
bool load_music(void);
void santa_cleanup(void);

}  // namespace Setup
}  // namespace SantaRacer
