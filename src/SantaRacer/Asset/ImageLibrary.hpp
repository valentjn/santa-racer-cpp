/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

#include <SDL2/SDL.h>

#include <filesystem>
#include <string>
#include <unordered_map>

#include "SantaRacer/Asset/AssetLibrary.hpp"
#include "SantaRacer/Asset/Image.hpp"

namespace SantaRacer {
namespace Asset {

class ImageLibrary : public AssetLibrary<Image> {
 public:
  ImageLibrary();
  explicit ImageLibrary(SDL_Renderer* renderer);

  Image loadAsset(std::string assetName) const override;
  std::filesystem::path getDirectory() const override;
  std::filesystem::path getExtension() const override;

  SDL_Renderer* getRenderer() const;
  void setRenderer(SDL_Renderer* renderer);

 protected:
  static const std::unordered_map<std::string, size_t> numberOfFramesXMap;
  static const std::unordered_map<std::string, size_t> numberOfFramesYMap;

  SDL_Renderer* renderer;
};

}  // namespace Asset
}  // namespace SantaRacer
