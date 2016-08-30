#pragma once

#include <memory>

#include "audio.h"
#include "backdrop.h"
#include "graphics.h"
#include "input.h"
#include "screen.h"
#include "text.h"

class TitleScreen : public Screen {
  public:

    void init();
    bool update(Input& input, Audio& audio, unsigned int elapsed);
    void draw(Graphics& graphics);

    Screen* next_screen();

  private:

    std::unique_ptr<Text> text_;
    std::unique_ptr<Backdrop> backdrop_;
};
