#pragma once

#include <memory>

#include "graphics.h"
#include "spritemap.h"

class Map {
  public:

    Map();

    void generate_terrain();
    void draw(Graphics& graphics) const;

    int get_height(int x) const;

    void destroy(int x, int y);

  private:

    std::unique_ptr<SpriteMap> tiles_;
    int data_[120][160];
};
