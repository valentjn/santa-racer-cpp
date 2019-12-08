/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

#include <filesystem>
#include <string>
#include <unordered_map>

namespace SantaRacer {
namespace Asset {

template <typename AssetType>
class AssetLibrary {
 public:
  virtual ~AssetLibrary();

  AssetType& getAsset(std::string assetName);
  void loadAssets();

  virtual AssetType loadAsset(std::string assetName) const = 0;
  virtual std::filesystem::path getDirectory() const = 0;
  virtual std::filesystem::path getExtension() const = 0;

 protected:
  std::unordered_map<std::string, AssetType> assetMap;
};

}  // namespace Asset
}  // namespace SantaRacer

#include "SantaRacer/Asset/AssetLibrary.inl"
