/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include <filesystem>
#include <string>
#include <unordered_map>

#include "SantaRacer/Asset/Image.hpp"
#include "SantaRacer/Asset/ImageLibrary.hpp"

namespace fs = std::filesystem;

namespace SantaRacer {
namespace Asset {

const std::unordered_map<std::string, size_t> ImageLibrary::numberOfFramesMap = {
      {"angel", 13},
      {"balloon1", 8},
      {"balloon2", 7},
      {"balloon3", 8},
      {"balloon4", 8},
      {"balloon5", 8},
      {"big_star", 10},
      {"gift1", 15},
      {"gift2", 15},
      {"gift3", 15},
      {"goblin", 19},
      {"level", 78},
      {"reindeer", 14},
      {"shield", 8},
      {"sleigh", 14},
      {"snowman", 8},
      {"star", 17},
      {"star_drunk", 17},
      {"star_small", 17},
    };

Image ImageLibrary::loadAsset(std::string assetName) const {
  const auto it = numberOfFramesMap.find(assetName);
  const size_t numberOfFrames = ((it != numberOfFramesMap.end()) ? it->second : 1);
  return Image(getDirectory() / (assetName + getExtension().string()), numberOfFrames);
}

fs::path ImageLibrary::getDirectory() const {
  return fs::path(".") / "assets" / "images";
}

fs::path ImageLibrary::getExtension() const {
  return fs::path(".tga");
}

}  // namespace Asset
}  // namespace SantaRacer
