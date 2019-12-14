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

const std::unordered_map<std::string, size_t> ImageLibrary::numberOfFramesXMap = {
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
      {"level", 13},
      {"reindeer", 14},
      {"shield", 8},
      {"sleigh", 14},
      {"snowman", 8},
      {"star", 17},
      {"star_drunk", 17},
      {"star_small", 17},
    };
const std::unordered_map<std::string, size_t> ImageLibrary::numberOfFramesYMap = {
      {"level", 6},
    };

ImageLibrary::ImageLibrary() : renderer(nullptr) {
}

ImageLibrary::ImageLibrary(SDL_Renderer* renderer) : renderer(renderer) {
}

Image ImageLibrary::loadAsset(std::string assetName) const {
  const auto itX = numberOfFramesXMap.find(assetName);
  const size_t numberOfFramesX = ((itX != numberOfFramesXMap.end()) ? itX->second : 1);
  const auto itY = numberOfFramesYMap.find(assetName);
  const size_t numberOfFramesY = ((itY != numberOfFramesYMap.end()) ? itY->second : 1);
  return Image(renderer, getDirectory() / (assetName + getExtension().string()),
      numberOfFramesX, numberOfFramesY);
}

fs::path ImageLibrary::getDirectory() const {
  return fs::path(".") / "assets" / "images";
}

fs::path ImageLibrary::getExtension() const {
  return fs::path(".tga");
}

SDL_Renderer* ImageLibrary::getRenderer() const {
  return renderer;
}

void ImageLibrary::setRenderer(SDL_Renderer* renderer) {
  this->renderer = renderer;
}

}  // namespace Asset
}  // namespace SantaRacer
