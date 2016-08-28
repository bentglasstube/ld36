#include "spritemap.h"

SpriteMap::SpriteMap(const std::string& file, int cols, int width, int height) :
  file_(file), cols_(cols), width_(width), height_(height) {}

void SpriteMap::draw(Graphics& graphics, int n, int x, int y, bool flip) {
  SDL_Rect source = { 0, 0, width_, height_ };
  SDL_Rect dest = { x, y, width_, height_ };

  source.x = width_ * (n % cols_);
  source.y = height_ * (n / cols_);

  graphics.blit(file_, &source, &dest, flip ? Graphics::HORIZONTAL : Graphics::NONE);
}