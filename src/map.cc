#include "map.h"

Map::Map() {
  tiles_.reset(new SpriteMap("tiles", 32, 4, 4));

  for (int y = 0; y < 120; ++y) {
    for (int x = 0; x < 160; ++x) {
      data_[y][x] = 0;
    }
  }
}

void Map::generate_terrain() {
  int h = 80;
  for (int x = 0; x < 160; ++x) {
    for (int y = 0; y < 120; ++y) {
      data_[y][x] = y < h ? 0 : y == h ? 1 : 2;
    }

    // TODO generate better terrain
    if (x % 4 == 3) {
      int r = rand();
      if (r % 4 == 0) h--;
      if (r % 4 == 1) h++;
    }
  }

  // smooth edges
  for (int x = 1; x < 160; ++x) {
    int h1 = get_height(4 * x - 1);
    int h2 = get_height(4 * x);

    if (h2 < h1) data_[h2 / 4][x] = 5;
    if (h2 > h1) data_[h2 / 4 - 1][x - 1] = 6;
  }
}

void Map::draw(Graphics& graphics) const {
  for (int y = 0; y < 120; ++y) {
    for (int x = 0; x < 160; ++x) {
      tiles_->draw(graphics, data_[y][x], x * 4, y * 4);
    }
  }

  for (int x = 0; x < 640; ++x) {
    graphics.draw_pixel(x, get_height(x), 1, 1, 1, 0.5f);
  }
}

int Map::get_height(int x) const {
  const int ix = x / 4;
  for (int y = 118; y > 0; --y) {
    if (data_[y][ix] == 0) {
      const int t = data_[y + 1][ix];
      if (t == 5) return y * 4 + 7 - x % 4;
      if (t == 6) return y * 4 + 4 + x % 4;
      return y * 4 + 4;
    }
  }

  return 0;
}

void Map::destroy(int x, int y) {
  const int tx = x / 4;

  for (int ty = y / 4; ty >= 0; --ty) {
    data_[ty][tx] = 0;
  }
}
