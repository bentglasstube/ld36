#pragma once

#include <memory>

#include "graphics.h"

class Map {
  public:

    Map();

    void generate_terrain();
    void smooth_terrain();
    void draw(Graphics& graphics) const;

    int get_height(int x) const { return heights_[x]; }

    void impact(int x);

  private:

    int heights_[640];
};
