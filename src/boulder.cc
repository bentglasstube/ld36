#include "boulder.h"

namespace {
  static const float GRAVITY = 0.0001f;
}

Boulder::Boulder(int x, int y, float vx, float vy) : x_(x), y_(y), vx_(vx), vy_(vy) {
  sprite_.reset(new Sprite("catapult", 65, 9, 2, 2));
}

void Boulder::update(Audio&, unsigned int elapsed) {
  x_ += elapsed * vx_;
  y_ += elapsed * vy_;
  vy_ += elapsed * GRAVITY;
}

void Boulder::draw(Graphics& graphics) const {
  sprite_->draw(graphics, x_, y_);
}
