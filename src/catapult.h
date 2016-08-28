#pragma once

#include <memory>

#include "graphics.h"
#include "map.h"
#include "spritemap.h"

class Catapult {
  public:

    enum Direction { NONE, LEFT, RIGHT };

    Catapult(int x, int y);
    void update(const Map& map, const unsigned int elapsed);
    void draw(Graphics& graphics, bool flip) const;

    SDL_Rect hit_box() const;

    bool point_within(float x, float y) const;

    void adjust_angle(float amount);
    void set_movement(Direction dir);
    bool ready_launch();
    bool launch();
    void destroy() { dead_ = true; }

    float get_x() const { return x_; }
    float get_y() const { return y_; }
    float get_angle() const { return angle_; }
    float get_launch_angle() const { return launch_angle_; }
    bool is_dead() const { return dead_; }

  private:

    enum State { MOBILE, LOADING, READY, LAUNCHING };

    float x_, y_, angle_, launch_angle_;
    Direction dir_;
    State state_;
    int wait_counter_;
    bool dead_;
    std::unique_ptr<SpriteMap> sprites_;
};
