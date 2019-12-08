/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

#include <filesystem>
#include <string>

#include "SantaRacer/Asset/AssetLibrary.hpp"
#include "SantaRacer/Asset/Sound.hpp"

namespace SantaRacer {
namespace Asset {

class SoundLibrary : public AssetLibrary<Sound> {
 public:
  Sound loadAsset(std::string assetName) const override;
  std::filesystem::path getDirectory() const override;
  std::filesystem::path getExtension() const override;
};

}  // namespace Asset
}  // namespace SantaRacer
