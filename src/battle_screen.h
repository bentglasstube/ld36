#pragma once

#include <memory>
#include <vector>

#include "audio.h"
#include "boulder.h"
#include "catapult.h"
#include "clouds.h"
#include "graphics.h"
#include "input.h"
#include "map.h"
#include "particle.h"
#include "screen.h"
#include "text.h"

class BattleScreen : public Screen {
  public:

    void init();
    bool update(Input& input, Audio& audio, unsigned int elapsed);
    void draw(Graphics& graphics);

    Screen* next_screen();

  private:

    enum GameState { COUNTDOWN, FIGHT, WINNER };

    GameState state_;
    int p1score_, p2score_;
    int counter_;
    std::unique_ptr<Text> text_;

    std::unique_ptr<Catapult> p1_, p2_;
    std::vector<Boulder> boulders_;
    std::vector<Particle> particles_;

    Map map_;
    Clouds clouds_;

    void launch_boulder(int x, int y, float v, float angle);

    void add_dirt_particles(int x, int y, int n);
    void add_smoke_particles(int x, int y, int n);
    void reset_game();
};
