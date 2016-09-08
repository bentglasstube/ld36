#pragma once

#include "graphics.h"

class Clouds {
  public:

    Clouds();

    void randomize();
    void update(const unsigned int elapsed);
    void draw(Graphics& graphics) const;

  private:
    float offset_, velocity_, height_;
};
