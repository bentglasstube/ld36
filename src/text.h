#pragma once

#include <string>

#include "graphics.h"

class Text {
  public:

    enum Alignment { LEFT, CENTER, RIGHT };

    Text(const std::string& file, const int width = 8);

    void draw(Graphics& graphics, const std::string& text, int x, int y, Alignment alignment=LEFT);

  private:

    std::string file;
    int width;
};

