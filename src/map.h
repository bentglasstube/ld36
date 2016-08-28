#pragma once

#include <memory>

#include "graphics.h"
#include "spritemap.h"

class Map {
  public:

    Map();

    void generate_terrain();
    void draw(Graphics& graphics);

    int get_tile(int x, int y);
    int get_height(int x);

  private:

    std::unique_ptr<SpriteMap> tiles_;
    int data_[60][80];

};
