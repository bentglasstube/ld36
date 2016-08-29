#include "clouds.h"

#include <stdlib.h>

#include "stb_perlin.h"

#define randf(high, low)  (low + static_cast <float> (rand()) / static_cast <float> (RAND_MAX/(high - low)))

Clouds::Clouds() : offset_(0), velocity_(0), height_(0) {}

void Clouds::randomize() {
  offset_ = 0;
  velocity_ = randf(0.005f, 0.015f);
  height_ = randf(0, 256);

  if (rand() % 2) velocity_ *= -1;
}

void Clouds::update(const unsigned int elapsed) {
  offset_ += elapsed * velocity_;
  height_ += elapsed * velocity_ * 0.01f;
}

void Clouds::draw(Graphics& graphics) const {
  for (int y = 0; y < 240; ++y) {
    for (int x = 0; x < 640; ++x) {
      float f = stb_perlin_noise3((x + offset_) / 80.0f, y / 33.0f, height_) + .5;
      if (f > 0) {
        int alpha = 255 * f;
        if (alpha > 255) alpha = 255;
        if (y > 150) alpha *= 1 - (y - 150) / 90.0f;
        graphics.draw_pixel(x, y, 0xffffff00 | alpha);
      }
    }
  }
}
