#include "map.h"

Map::Map() {
  for (int x = 0; x < 640; ++x) {
    heights_[x] = 0;
  }
}

void Map::generate_terrain() {
  int h = 320;
  for (int x = 0; x < 640; ++x) {
    heights_[x] = h;

    if (x % 4 == 3) {
      int r = rand();
      if (r % 4 == 0) h--;
      if (r % 4 == 1) h++;
    }
  }
}

void Map::draw(Graphics& graphics) const {
  for (int x = 0; x < 640; ++x) {
    graphics.draw_pixel(x, heights_[x], .26, .53, .10, 1);
    graphics.draw_line(x, heights_[x] + 1, x, 640, .64, .39, .13, 1);
  }
}

void Map::impact(int x) {
  heights_[x - 3] += 1;
  heights_[x - 2] += 2;
  heights_[x - 1] += 3;
  heights_[x + 0] += 3;
  heights_[x + 1] += 3;
  heights_[x + 2] += 2;
  heights_[x + 3] += 1;
}
