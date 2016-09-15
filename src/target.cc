#include "target.h"

Target::Target(float x, float y) : x_(x), y_(y), sprite_("catapult", 80, 0, 16, 16) {}

void Target::draw(Graphics& graphics) const {
  sprite_.draw(graphics, x_ - 8, y_ - 16);
}

bool Target::point_within(float x, float y) const {
  const SDL_Rect b = { (int)x_ - 4, (int)y_ - 8, 8, 8 };
  return x > b.x && x < b.x + b.w && y > b.y && y < b.y + b.h;
}
