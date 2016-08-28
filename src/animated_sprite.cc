#include "animated_sprite.h"

AnimatedSprite::AnimatedSprite(
    const std::string& file,
    int x, int y, int w, int h,
    unsigned int frames, unsigned int fps, LoopType loop) :
  Sprite(file, x, y, w, h), bx(x),
  count(frames), start(0), fps(fps), loop(loop) {}

void AnimatedSprite::draw(Graphics& graphics, int x, int y) {
  if (start == 0) start = SDL_GetTicks();

  const unsigned int max = loop == NORMAL ? count : 2 * count - 2;
  const unsigned int frame = ((SDL_GetTicks() - start) * fps / 1000) % max;

  rect.x = bx + rect.w * (frame < count ? frame : max - frame);

  Sprite::draw(graphics, x, y);
}
