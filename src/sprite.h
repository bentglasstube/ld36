#pragma once

#include <SDL2/SDL.h>
#include <string>

#include "graphics.h"

class Sprite {
  public:

    Sprite(const std::string& file, int x, int y, int w, int h);

    virtual void draw(Graphics& graphics, int x, int y);

  protected:
    SDL_Rect rect;

  private:
    std::string file;
};
