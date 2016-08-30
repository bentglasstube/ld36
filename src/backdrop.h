#pragma once

#include <string>

#include "graphics.h"

class Backdrop {

  public:

    Backdrop(const std::string& file);

    void draw(Graphics& graphics);
    virtual void update() {}

  private:

    std::string file_;

};
