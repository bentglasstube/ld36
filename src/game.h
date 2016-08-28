#pragma once

#include <memory>

#include "graphics.h"
#include "screen.h"

class Game {
  public:

    Game();
    ~Game();

    void loop();

  private:

    std::shared_ptr<Screen> screen;
};
