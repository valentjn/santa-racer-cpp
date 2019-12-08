/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>

#include "SantaRacer/Asset/AssetLibrary.hpp"
#include "SantaRacer/Asset/Image.hpp"

namespace SantaRacer {
namespace Asset {

class ImageLibrary : public AssetLibrary<Image> {
 public:
  Image loadAsset(std::string assetName) const override;
  std::filesystem::path getDirectory() const override;
  std::filesystem::path getExtension() const override;

 protected:
  static const std::unordered_map<std::string, size_t> numberOfFramesMap;
};

}  // namespace Asset
}  // namespace SantaRacer
