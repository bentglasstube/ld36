#pragma once

#include <memory>

#include "audio.h"
#include "graphics.h"
#include "input.h"
#include "screen.h"
#include "text.h"

class TitleScreen : public Screen {
  public:

    void init();
    bool update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed);
    void draw(Graphics& graphics);

    Screen* next_screen();
    std::string get_music_track() { return ""; }

  private:

    std::unique_ptr<Text> text_;
};
