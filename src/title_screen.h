#pragma once

#include <memory>

#include "framework/audio.h"
#include "framework/backdrop.h"
#include "framework/graphics.h"
#include "framework/input.h"
#include "framework/screen.h"
#include "framework/text.h"

class TitleScreen : public Screen {
  public:

    void init();
    bool update(Input& input, Audio& audio, unsigned int elapsed);
    void draw(Graphics& graphics) const;

    Screen* next_screen();

  private:

    std::unique_ptr<Text> text_;
    std::unique_ptr<Backdrop> backdrop_;
};
