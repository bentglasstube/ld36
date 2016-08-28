#include "catapult.h"

#include <math.h>

namespace {
  const static float _X_VELO = 0.01f;
  const static int _LOAD_TIME = 1000;
  const static int _LAUNCH_TIME = 150;
};

Catapult::Catapult(int x, int y) :
  x_(x), y_(y), launch_angle_(M_PI / 4.0f),
  dir_(Catapult::NONE), state_(Catapult::MOBILE), wait_counter_(0) {
  sprites_.reset(new SpriteMap("catapult", 8, 16, 16));
}

void Catapult::update(Audio&, unsigned int elapsed) {
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
}

void Catapult::draw(Graphics& graphics, bool flip) {
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

  sprites_->draw(graphics, tile, x_ - 8, y_ - 16, flip);

  SDL_Rect b = hit_box();
  graphics.draw_rect(&b, 1, 0, 0, 0.5f, false);
}

SDL_Rect Catapult::hit_box() {
  return { (int)x_ - 7, (int)y_ - 8, 14, 8 };
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

void Catapult::ready_launch() {
  if (state_ == Catapult::MOBILE) {
    state_ = Catapult::LOADING;
    wait_counter_ = _LOAD_TIME;
    dir_ = Catapult::NONE;
  }
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
