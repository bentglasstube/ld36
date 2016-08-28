#include "sprite.h"

Sprite::Sprite(const std::string& file, int x, int y, int w, int h) : file(file) {
  rect.x = x;
  rect.y = y;
  rect.w = w;
  rect.h = h;
}

void Sprite::draw(Graphics& graphics, int x, int y) {
  SDL_Rect dest;

  dest.x = x;
  dest.y = y;
  dest.w = rect.w;
  dest.h = rect.h;

  graphics.blit(file, &rect, &dest, Graphics::NONE);
}
