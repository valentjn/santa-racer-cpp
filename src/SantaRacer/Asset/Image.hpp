/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#pragma once

#include <SDL2/SDL.h>

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
  explicit Image(SDL_Renderer* renderer, std::filesystem::path imagePath,
      size_t numberOfFramesX = 1, size_t numberOfFramesY = 1);
  explicit Image(SDL_Renderer* renderer, SDL_Surface* surface,
      size_t numberOfFramesX = 1, size_t numberOfFramesY = 1);
  Image(const Image& other) = delete;
  Image(Image&& other);
  ~Image();

  Image& operator=(const Image& other) = delete;
  Image& operator=(Image&& other);

  void blit(Rectangle sourceRectangle, Point targetPoint, size_t frame = 0);
  void copy(Point targetPoint, size_t frame = 0);  // NOLINT(build/include_what_you_use)
  void setAlpha(Uint8 alpha);

  std::vector<bool> getMask();
  bool checkCollision(Point point, int frame, Image *other, Point otherPoint, size_t otherFrame);

  inline SDL_Surface* getSurface() const {
    return surface;
  }

  inline SDL_Texture* getTexture() const {
    return texture;
  }

  inline SDL_Renderer* getRenderer() const {
    return renderer;
  }

  inline size_t getWidth() const {
    return static_cast<size_t>(surface->w) / numberOfFramesX;
  }

  inline size_t getHeight() const {
    return static_cast<size_t>(surface->h) / numberOfFramesY;
  }

  inline size_t getNumberOfFrames() const {
    return numberOfFramesX * numberOfFramesY;
  }

 protected:
  SDL_Renderer* renderer;
  SDL_Surface* surface;
  SDL_Texture* texture;
  size_t numberOfFramesX;
  size_t numberOfFramesY;
  std::vector<bool> mask;
};

}  // namespace Asset
}  // namespace SantaRacer
