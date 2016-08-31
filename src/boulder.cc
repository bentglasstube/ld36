#include "boulder.h"

namespace {
  static const float GRAVITY = 0.0001f;
}

Boulder::Boulder(int x, int y, float vx, float vy) : x_(x), y_(y), vx_(vx), vy_(vy) {}

void Boulder::update(unsigned int elapsed) {
  x_ += elapsed * vx_;
  y_ += elapsed * vy_;
  vy_ += elapsed * GRAVITY;
}

void Boulder::draw(Graphics& graphics) const {
  graphics.draw_circle(x_, y_, 1, 0x697175ff, true);
}
