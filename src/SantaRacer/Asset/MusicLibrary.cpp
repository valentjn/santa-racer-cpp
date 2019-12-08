/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include <filesystem>
#include <string>

#include "SantaRacer/Asset/Music.hpp"
#include "SantaRacer/Asset/MusicLibrary.hpp"

namespace fs = std::filesystem;

namespace SantaRacer {
namespace Asset {

Music MusicLibrary::loadAsset(std::string assetName) const {
  return Music(getDirectory() / (assetName + getExtension().string()));
}

fs::path MusicLibrary::getDirectory() const {
  return fs::path(".") / "assets" / "sounds";
}

fs::path MusicLibrary::getExtension() const {
  return fs::path(".ogg");
}

}  // namespace Asset
}  // namespace SantaRacer
