/*
 * Santa Racer - Copyright (C) 2010--2019 Julian Valentin.
 * This code is licensed under the GNU General Public License (GNU GPL), version 3.
 * See LICENSE.md in the project's root directory.
 */

#include <SDL2/SDL_image.h>

#include <algorithm>
#include <filesystem>
#include <memory>
#include <string>
#include <vector>

#include "SantaRacer/Printer.hpp"
#include "SantaRacer/Asset/Image.hpp"

namespace SantaRacer {
namespace Asset {

Image::Image() : renderer(nullptr), surface(nullptr), texture(nullptr),
    numberOfFramesX(1), numberOfFramesY(1) {
}

Image::Image(SDL_Renderer* renderer, std::filesystem::path imagePath,
    size_t numberOfFramesX, size_t numberOfFramesY) :
    renderer(renderer), surface(IMG_Load(imagePath.c_str())),
    texture(SDL_CreateTextureFromSurface(renderer, surface)),
    numberOfFramesX(numberOfFramesX), numberOfFramesY(numberOfFramesY) {
  if (surface == nullptr) {
    Printer::fatalError("couldn't load image: %s\n", IMG_GetError());
  }

  if (texture == nullptr) {
    Printer::fatalError("couldn't create texture: %s\n", SDL_GetError());
  }
}

Image::Image(SDL_Renderer* renderer, SDL_Surface* surface,
    size_t numberOfFramesX, size_t numberOfFramesY) :
    renderer(renderer), surface(surface),
    texture(SDL_CreateTextureFromSurface(renderer, surface)),
    numberOfFramesX(numberOfFramesX), numberOfFramesY(numberOfFramesY) {
}

Image::Image(Image&& other) :
    renderer(other.renderer), surface(other.surface), texture(other.texture),
    numberOfFramesX(other.numberOfFramesX), numberOfFramesY(other.numberOfFramesY) {
  other.renderer = nullptr;
  other.surface = nullptr;
  other.texture = nullptr;
}

Image::~Image() {
  if (surface != nullptr) {
    SDL_FreeSurface(surface);
  }

  if (texture != nullptr) {
    SDL_DestroyTexture(texture);
  }
}

Image& Image::operator=(Image&& other) {
  if (&other != this) {
    surface = other.surface;
    other.surface = nullptr;
  }

  return *this;
}

void Image::blit(Rectangle sourceRectangle, Point targetPoint, size_t frame) {
  sourceRectangle.x += (frame % numberOfFramesX) * getWidth();
  sourceRectangle.y += ((frame / numberOfFramesX) % numberOfFramesY) * getHeight();
  const Rectangle targetRectangle(targetPoint.x, targetPoint.y,
      sourceRectangle.w, sourceRectangle.h);
  SDL_RenderCopy(renderer, texture, &sourceRectangle, &targetRectangle);
}

void Image::copy(Point targetPoint, size_t frame) {  // NOLINT(build/include_what_you_use)
  Rectangle sourceRectangle((frame % numberOfFramesX) * getWidth(),
      ((frame / numberOfFramesX) % numberOfFramesY) * getHeight(), getWidth(), getHeight());
  const Rectangle targetRectangle(targetPoint.x, targetPoint.y,
      sourceRectangle.w, sourceRectangle.h);
  SDL_RenderCopy(renderer, texture, &sourceRectangle, &targetRectangle);
}

void Image::setAlpha(Uint8 alpha) {
  SDL_SetTextureAlphaMod(texture, alpha);
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

  for (int clipY = clipRectangle.y; clipY < clipRectangle.y + clipRectangle.h; clipY++) {
    for (int clipX = clipRectangle.x; clipX < clipRectangle.x + clipRectangle.w; clipX++) {
      const size_t testI1 = (clipX - point.x +
          (frame % numberOfFramesX) * width) +
          (clipY - point.y +
          ((frame / numberOfFramesX) % numberOfFramesY) * height) *
          surface->w;
      const size_t testI2 = (clipX - otherPoint.x +
          (otherFrame % other->numberOfFramesX) * otherWidth) +
          (clipY - otherPoint.y +
          ((otherFrame / other->numberOfFramesX) % other->numberOfFramesY) * otherHeight) *
          other->surface->w;

      if (mask[testI1] && otherMask[testI2]) {
        return true;
      }
    }
  }

  return false;
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
