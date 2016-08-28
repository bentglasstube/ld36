#pragma once

#include <memory>

#include "audio.h"
#include "catapult.h"
#include "graphics.h"
#include "input.h"
#include "screen.h"
#include "spritemap.h"
#include "text.h"

class BattleScreen : public Screen {
  public:

    void init();
    bool update(Input& input, Audio& audio, Graphics& graphics, unsigned int elapsed);
    void draw(Graphics& graphics);

    Screen* next_screen();
    std::string get_music_track() { return ""; }

  private:

    std::unique_ptr<Text> text_;
    std::unique_ptr<SpriteMap> tiles_;

    std::unique_ptr<Catapult> p1_, p2_;
};
