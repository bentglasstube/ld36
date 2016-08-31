#pragma once

#include <memory>

#include "screen.h"

class Game {
  public:

    Game();
    ~Game();

    void loop(Screen* initial_screen);

  private:

    std::shared_ptr<Screen> screen_;
};
