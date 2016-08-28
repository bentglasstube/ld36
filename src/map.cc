#include "map.h"

Map::Map() {
  tiles_.reset(new SpriteMap("tiles", 16, 8, 8));

  for (int y = 0; y < 60; ++y) {
    for (int x = 0; x < 80; ++x) {
      data_[y][x] = 0;
    }
  }
}

void Map::generate_terrain() {
  int h = 40;
  for (int x = 0; x < 80; ++x) {
    for (int y = 0; y < 60; ++y) {
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
  for (int x = 1; x < 80; ++x) {
    int h1 = get_height(8 * x - 8);
    int h2 = get_height(8 * x);

    if (h2 < h1) data_[h2 + 1][x] = 5;
    if (h2 > h1) data_[h2][x - 1] = 6;
  }
}

void Map::draw(Graphics& graphics) {
  for (int y = 0; y < 60; ++y) {
    for (int x = 0; x < 80; ++x) {
      tiles_->draw(graphics, data_[y][x], x * 8, y * 8, false);
    }
  }
}

int Map::get_tile(int x, int y) {
  return data_[y / 8][x / 8];
}

int Map::get_height(int x) {
  const int ix = x / 8;
  for (int y = 59; y > 0; --y) {
    if (data_[y][ix] == 0) return y;
  }

  return 0;
}
