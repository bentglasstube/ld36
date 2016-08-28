#include "particle.h"

Particle::Particle(float x, float y, float vx, float vy, float r, float g, float b, int duration) :
  x_(x), y_(y), vx_(vx), vy_(vy),
  r_(r), g_(g), b_(b),
  duration_(duration), timer_(0) {}

void Particle::update(unsigned int elapsed) {
  x_ += vx_ * elapsed;
  y_ += vy_ * elapsed;
  timer_ += elapsed;
}

void Particle::draw(Graphics& graphics) const {
  graphics.draw_pixel(x_, y_, r_, g_, b_, 1 - (timer_ / (float) duration_));
}
