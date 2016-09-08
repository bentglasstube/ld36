#pragma once

#include <memory>

#include "map.h"

#include "graphics.h"
#include "input.h"
#include "spritemap.h"

class Catapult {
  public:

    enum class State { MOBILE, LOADING, READY, LAUNCHING };

    Catapult(int x, int y, bool flipped, const SDL_Scancode *inputs);

    bool update(const Input& input, const Map& map, const unsigned int elapsed);
    void settle(const Map& map);
    void draw(Graphics& graphics) const;

    SDL_Rect hit_box() const;

    bool point_within(float x, float y) const;

    void destroy() { dead_ = true; }

    State get_state() const { return state_; }
    float get_x() const { return x_; }
    float get_y() const { return y_; }
    float get_angle() const { return angle_; }
    float get_launch_angle() const { return launch_angle_; }
    bool is_dead() const { return dead_; }

    float launch_x() const { return x_ + (flipped_ ? 7 : -7); }
    float launch_y() const { return y_ - 7; }
    float launch_angle() const { return (flipped_ ? M_PI + launch_angle_ : 2 * M_PI - launch_angle_) + angle_; }

  private:

    enum class Direction { NONE, LEFT, RIGHT };

    float x_, y_, angle_, launch_angle_;
    Direction dir_;
    State state_;
    int wait_counter_;
    bool dead_, flipped_;
    SDL_Scancode inputs_[6];
    std::unique_ptr<SpriteMap> sprites_;

    void adjust_angle(float amount);
    void set_movement(Direction dir);
    void ready_launch();
    void launch();
};
