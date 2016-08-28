#pragma once

#include <memory>

#include "audio.h"
#include "graphics.h"
#include "spritemap.h"

class Catapult {
  public:

    enum Direction { NONE, LEFT, RIGHT };

    Catapult(int x, int y);
    void update(Audio& audio, unsigned int elapsed);
    void draw(Graphics& graphics, bool flip);

    SDL_Rect hit_box();

    void adjust_angle(float amount);
    void set_movement(Direction dir);
    void ready_launch();
    bool launch();

    float get_x() { return x_; }
    float get_y() { return y_; }

    float get_launch_angle() { return launch_angle_; }

  private:

    enum State { MOBILE, LOADING, READY, LAUNCHING };

    float x_, y_, launch_angle_;
    Direction dir_;
    State state_;
    int wait_counter_;
    std::unique_ptr<SpriteMap> sprites_;
};
