#pragma once

#include "graphics.h"
#include "sprite.h"

class Target {
  public:

    Target(float x, float y);

    void draw(Graphics& graphics) const;

    bool point_within(float x, float y) const;

  private:

    float x_, y_;
    Sprite sprite_;
};
