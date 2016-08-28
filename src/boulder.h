#pragma once

#include <memory>

#include "audio.h"
#include "graphics.h"
#include "sprite.h"

class Boulder {
  public:

    Boulder(int x, int y, float vx, float vy);

    void update(Audio& audio, unsigned int elapsed);
    void draw(Graphics& graphics);

    float get_x() { return x_; }
    float get_y() { return y_; }

  private:

    float x_, y_, vx_, vy_;
    std::unique_ptr<Sprite> sprite_;
};
