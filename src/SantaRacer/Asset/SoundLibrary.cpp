/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include <filesystem>
#include <string>

#include "SantaRacer/Asset/Sound.hpp"
#include "SantaRacer/Asset/SoundLibrary.hpp"

namespace fs = std::filesystem;

namespace SantaRacer {
namespace Asset {

Sound SoundLibrary::loadAsset(std::string assetName) const {
  return Sound(getDirectory() / (assetName + getExtension().string()));
}

fs::path SoundLibrary::getDirectory() const {
  return fs::path(".") / "assets" / "sounds";
}

fs::path SoundLibrary::getExtension() const {
  return fs::path(".wav");
}

}  // namespace Asset
}  // namespace SantaRacer
