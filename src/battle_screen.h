#pragma once

#include <memory>
#include <vector>

#include "boulder.h"
#include "catapult.h"
#include "clouds.h"
#include "map.h"
#include "target.h"

#include "graphics.h"
#include "input.h"
#include "audio.h"
#include "particle.h"
#include "screen.h"
#include "text.h"

class BattleScreen : public Screen {
  public:

    enum class GameMode { PRACTICE, SIEGE, BATTLE };

    BattleScreen(GameMode mode);

    void init();
    bool update(const Input& input, Audio& audio, unsigned int elapsed);
    void draw(Graphics& graphics) const;

    Screen* next_screen();

    void set_mode(GameMode mode);

  private:

    enum class GameState { COUNTDOWN, FIGHT, WINNER };

    GameState state_;
    GameMode mode_;
    int p1score_, p2score_;
    int counter_;
    std::unique_ptr<Text> text_;

    std::vector<Catapult> players_;
    std::vector<Boulder> boulders_;
    std::vector<Particle> particles_;
    std::vector<Target> targets_;

    Map map_;
    Clouds clouds_;

    void launch_boulder(int x, int y, float angle);

    void spawn_target(int count);

    void add_dirt_particles(int x, int y, int n);
    void add_smoke_particles(int x, int y, int n);
    void reset_game();
};
