/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include <SDL/SDL_image.h>

#include <algorithm>
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include "SantaRacer/Printer.hpp"
#include "SantaRacer/Asset/Image.hpp"

namespace SantaRacer {
namespace Asset {

Image::Image() : Image(nullptr) {
}

Image::Image(std::filesystem::path imagePath, size_t numberOfFrames) :
    surface(IMG_Load(imagePath.c_str())), numberOfFrames(numberOfFrames) {
  if (surface == nullptr) {
    Printer::fatalError("couldn't load image: %s\n", IMG_GetError());
  }
}

Image::Image(SDL_Surface* surface, size_t numberOfFrames) :
    surface(surface), numberOfFrames(numberOfFrames) {
}

Image::Image(Image&& other) : surface(other.surface), numberOfFrames(other.numberOfFrames) {
  other.surface = nullptr;
}

Image::~Image() {
  if (surface != nullptr) {
    SDL_FreeSurface(surface);
  }
}

Image& Image::operator=(Image&& other) {
  if (&other != this) {
    surface = other.surface;
    other.surface = nullptr;
  }

  return *this;
}

void Image::blit(Rectangle sourceRectangle, SDL_Surface *targetSurface, Point targetPoint,
    size_t frame) const {
  sourceRectangle.x += (frame % numberOfFrames) * getWidth();
  SDL_BlitSurface(surface, &sourceRectangle, targetSurface, &targetPoint);
}

void Image::copy(SDL_Surface *targetSurface,  // NOLINT(build/include_what_you_use)
    Point targetPoint, size_t frame) const {
  Rectangle sourceRectangle((frame % numberOfFrames) * getWidth(), 0, getWidth(), getHeight());
  SDL_BlitSurface(surface, &sourceRectangle, targetSurface, &targetPoint);
}

void Image::setAlpha(Uint8 alpha) {
  SDL_LockSurface(surface);

  for (int y = 0; y < surface->h; y++) {
    for (int x = 0; x < surface->w; x++) {
      Uint8 r;
      Uint8 g;
      Uint8 b;
      Uint8 oldAlpha;
      Uint32 *pixel = static_cast<Uint32*>(surface->pixels) + y * surface->pitch / 4 + x;
      SDL_GetRGBA(*pixel, surface->format, &r, &g, &b, &oldAlpha);

      if (oldAlpha != 0) {
        *pixel = SDL_MapRGBA(surface->format, r, g, b, alpha);
      }
    }
  }

  SDL_UnlockSurface(surface);
}

bool Image::checkCollision(Point point, int frame, Image *other, Point otherPoint,
    size_t otherFrame) {
  const int width = static_cast<int>(getWidth());
  const int height = static_cast<int>(getHeight());
  const int otherWidth = static_cast<int>(other->getWidth());
  const int otherHeight = static_cast<int>(other->getHeight());

  if (((point.x < otherPoint.x) && (point.x + width < otherPoint.x)) ||
      ((otherPoint.x < point.x) && (otherPoint.x + otherWidth < point.x)) ||
      ((point.y < otherPoint.y) && (point.y + height < otherPoint.y)) ||
      ((otherPoint.y < point.y) && (otherPoint.y + otherHeight < point.y))) {
    // bounding boxes do not overlap at all
    return false;
  }

  Rectangle clipRectangle;

  if (point.x < otherPoint.x) {
    clipRectangle.x = otherPoint.x;
    clipRectangle.w = std::min(point.x + width - otherPoint.x, otherWidth);
  } else {
    clipRectangle.x = point.x;
    clipRectangle.w = std::min(otherPoint.x + otherWidth - point.x, width);
  }

  if (point.y < otherPoint.y) {
    clipRectangle.y = otherPoint.y;
    clipRectangle.h = std::min(point.y + height - otherPoint.y, otherHeight);
  } else {
    clipRectangle.y = point.y;
    clipRectangle.h = std::min(otherPoint.y + otherHeight - point.y, height);
  }

  const std::vector<bool>& mask = getMask();
  const std::vector<bool>& otherMask = other->getMask();
  frame %= numberOfFrames;
  otherFrame %= other->numberOfFrames;

  for (int clipY = clipRectangle.y; clipY < clipRectangle.y + clipRectangle.h; clipY++) {
    for (int clipX = clipRectangle.x; clipX < clipRectangle.x + clipRectangle.w; clipX++) {
      const size_t testI1 = (clipX - point.x + width * frame) + (clipY - point.y) * surface->w;
      const size_t testI2 = (clipX - otherPoint.x + otherWidth * otherFrame) +
          (clipY - otherPoint.y) * other->surface->w;

      if (mask[testI1] && otherMask[testI2]) {
        return true;
      }
    }
  }

  return false;
}

SDL_Surface& Image::getSurface() const {
  return *surface;
}

size_t Image::getWidth() const {
  return static_cast<size_t>(surface->w) / numberOfFrames;
}

size_t Image::getHeight() const {
  return static_cast<size_t>(surface->h);
}

size_t Image::getNumberOfFrames() const {
  return numberOfFrames;
}

std::vector<bool> Image::getMask() {
  if (mask.empty()) {
    SDL_LockSurface(surface);

    for (size_t y = 0; y < static_cast<size_t>(surface->h); y++) {
      for (size_t x = 0; x < static_cast<size_t>(surface->w); x++) {
        Uint8 r;
        Uint8 g;
        Uint8 b;
        Uint8 a;

        Uint32* pixel = static_cast<Uint32*>(surface->pixels) + y * surface->pitch / 4 + x;
        SDL_GetRGBA(*pixel, surface->format, &r, &g, &b, &a);
        mask.push_back(a == 0xff);
      }
    }

    SDL_UnlockSurface(surface);
  }

  return mask;
}

}  // namespace Asset
}  // namespace SantaRacer
