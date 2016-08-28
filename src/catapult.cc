#include "catapult.h"

#include <math.h>

namespace {
  const static float _X_VELO = 0.01f;
  const static float _Y_VELO = 0.1f;
  const static int _LOAD_TIME = 1000;
  const static int _LAUNCH_TIME = 150;
};

Catapult::Catapult(int x, int y) :
  x_(x), y_(y), angle_(0), launch_angle_(M_PI / 4.0f),
  dir_(Catapult::NONE), state_(Catapult::MOBILE), wait_counter_(0) {
  sprites_.reset(new SpriteMap("catapult", 8, 16, 16));
}

void Catapult::update(const Map& map, const unsigned int elapsed) {
  if (wait_counter_ > 0) {
    wait_counter_ -= elapsed;

    if (wait_counter_ <= 0) {
      switch (state_) {
        case Catapult::LOADING:
          state_ = Catapult::READY;
          break;

        case Catapult::LAUNCHING:
          state_ = Catapult::MOBILE;
          break;

        default:
          break;
      }
    }

    return;
  }

  switch (dir_) {
    case Catapult::LEFT:
      x_ -= elapsed * _X_VELO;
      break;

    case Catapult::RIGHT:
      x_ += elapsed * _X_VELO;
      break;

    default:
      break;
  }

  const float y1 = map.get_height(x_ - 4), y2 = map.get_height(x_ + 4);
  const float ny = (y1 + y2) / 2.0f;

  if (y_ > ny + 10) {
    // TODO falling state
    y_ += elapsed * _Y_VELO;
  } else {
    y_ = ny;
    angle_ = atan2f(y2 - y1, 8.0f);
  }
}

void Catapult::draw(Graphics& graphics, bool flip) const {
  int tile = 0;

  switch (state_) {
    case Catapult::MOBILE:
      tile = 0;
      break;

    case Catapult::LOADING:
      tile = (_LOAD_TIME - wait_counter_) / (_LOAD_TIME / 4);
      break;

    case Catapult::READY:
      tile = 4;
      break;

    case Catapult::LAUNCHING:
      tile = wait_counter_ / (_LAUNCH_TIME / 4);
      break;
  }

  sprites_->draw_ex(graphics, tile, x_ - 8, y_ - 16, flip, angle_, 8, 16);

  SDL_Rect b = hit_box();
  graphics.draw_rect(&b, 1, 0, 0, 0.5f, false);
}

SDL_Rect Catapult::hit_box() const {
  return { (int)x_ - 6, (int)y_ - 6, 12, 6 };
}

bool Catapult::point_within(float x, float y) const {
  const SDL_Rect b = hit_box();
  return x > b.x && x < b.x + b.w && y > b.y && y < b.y + b.h;
}

void Catapult::adjust_angle(float amount) {
  if (state_ == Catapult::MOBILE) {
    launch_angle_ += amount;
    if (launch_angle_ < M_PI / 6.0f) launch_angle_ = M_PI / 6.0f;
    if (launch_angle_ > M_PI / 3.0f) launch_angle_ = M_PI / 3.0f;
  }
}

void Catapult::set_movement(Catapult::Direction dir) {
  if (state_ == Catapult::MOBILE) {
    dir_ = dir;
  }
}

bool Catapult::ready_launch() {
  if (state_ == Catapult::MOBILE) {
    state_ = Catapult::LOADING;
    wait_counter_ = _LOAD_TIME;
    dir_ = Catapult::NONE;

    return true;
  }

  return false;
}

bool Catapult::launch() {
  if (state_ == Catapult::READY) {
    state_ = Catapult::LAUNCHING;
    wait_counter_ = _LAUNCH_TIME;
    dir_ = Catapult::NONE;

    return true;
  }

  return false;
}
