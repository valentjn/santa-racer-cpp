/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

#include <SDL/SDL.h>

#include <filesystem>
#include <memory>
#include <string>
#include <vector>

namespace SantaRacer {
namespace Asset {

class Image {
 public:
  class Rectangle : public SDL_Rect {
   public:
    Rectangle() : Rectangle(0, 0, 0, 0) {}
    Rectangle(int x, int y, size_t w, size_t h) :
        SDL_Rect({static_cast<Sint16>(x), static_cast<Sint16>(y),
          static_cast<Uint16>(w), static_cast<Uint16>(h)}) {}
  };

  class Point : public SDL_Rect {
   public:
    Point() : Point(0, 0) {}
    Point(int x, int y) : SDL_Rect({static_cast<Sint16>(x), static_cast<Sint16>(y), 0, 0}) {}
  };

  Image();
  explicit Image(std::filesystem::path imagePath, size_t numberOfFrames = 1);
  explicit Image(SDL_Surface* surface, size_t numberOfFrames = 1);
  Image(const Image& other) = delete;
  Image(Image&& other);
  ~Image();

  Image& operator=(const Image& other) = delete;
  Image& operator=(Image&& other);

  void blit(Rectangle sourceRectangle, SDL_Surface *targetSurface, Point targetPoint,
      size_t frame = 0) const;
  void copy(SDL_Surface *targetSurface, Point targetPoint,  // NOLINT(build/include_what_you_use)
      size_t frame = 0) const;
  void setAlpha(Uint8 alpha);

  bool checkCollision(Point point, int frame, Image *other, Point otherPoint, size_t otherFrame);

  SDL_Surface& getSurface() const;
  size_t getWidth() const;
  size_t getHeight() const;
  size_t getNumberOfFrames() const;
  std::vector<bool> getMask();

 protected:
  SDL_Surface* surface;
  size_t numberOfFrames;
  std::vector<bool> mask;
};

}  // namespace Asset
}  // namespace SantaRacer
