#pragma once

#include "sprite.h"

class AnimatedSprite : public Sprite {
  public:

    enum LoopType { NORMAL, BOUNCE };

    AnimatedSprite(const std::string& file, int x, int y, int w, int h, unsigned int frames, unsigned int fps, LoopType loop = NORMAL);

    void draw(Graphics& graphics, int x, int y);

  private:

    int bx;
    unsigned int count, start, fps;
    LoopType loop;
};
