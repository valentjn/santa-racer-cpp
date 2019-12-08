/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include <filesystem>
#include <fstream>
#include <iterator>
#include <string>
#include <vector>

#include "SantaRacer/Asset/DataLibrary.hpp"

namespace fs = std::filesystem;

namespace SantaRacer {
namespace Asset {

std::vector<double> DataLibrary::loadAsset(std::string assetName) const {
  std::ifstream f(getDirectory() / (assetName + getExtension().string()));
  std::istream_iterator<double> begin(f);
  std::istream_iterator<double> end;

  return std::vector<double>(begin, end);
}

fs::path DataLibrary::getDirectory() const {
  return fs::path(".") / "assets" / "data";
}

fs::path DataLibrary::getExtension() const {
  return fs::path(".txt");
}

}  // namespace Asset
}  // namespace SantaRacer
