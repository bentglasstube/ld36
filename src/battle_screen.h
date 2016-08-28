#pragma once

#include <memory>
#include <vector>

#include "audio.h"
#include "boulder.h"
#include "catapult.h"
#include "graphics.h"
#include "input.h"
#include "map.h"
#include "particle.h"
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

    std::unique_ptr<Catapult> p1_, p2_;
    std::vector<std::unique_ptr<Boulder>> boulders_;
    std::vector<Particle> particles_;

    Map map_;

    void launch_boulder(int x, int y, float v, float angle);

    void add_dirt_particles(int x, int y, int n);
    void add_smoke_particles(int x, int y, int n);
};
