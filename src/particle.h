#pragma once

#include "graphics.h"

class Particle {
  public:
    Particle(float x, float y, float vx, float vy, float ay, float r, float g, float b, int duration);

    void update(unsigned int elapsed);
    void draw(Graphics& graphics) const;

    bool done() const { return timer_ > duration_; }

  private:

    float x_, y_, vx_, vy_, ay_;
    float r_, g_, b_;
    int duration_, timer_;
};
