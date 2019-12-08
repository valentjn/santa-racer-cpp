/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include <filesystem>
#include <string>
#include <unordered_map>

#include "SantaRacer/Asset/AssetLibrary.hpp"

namespace fs = std::filesystem;

namespace SantaRacer {
namespace Asset {

template <typename AssetType>
AssetLibrary<AssetType>::~AssetLibrary() {
}

template <typename AssetType>
AssetType& AssetLibrary<AssetType>::getAsset(std::string assetName) {
  auto it = assetMap.find(assetName);

  if (it == assetMap.end()) {
    it = assetMap.insert({assetName, loadAsset(assetName)}).first;
  }

  return it->second;
}

template <typename AssetType>
void AssetLibrary<AssetType>::loadAssets() {
  for (const fs::path& file : fs::directory_iterator(getDirectory())) {
    if (file.extension() == getExtension()) {
      getAsset(file.stem());
    }
  }
}

}  // namespace Asset
}  // namespace SantaRacer
