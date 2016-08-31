#include "catapult.h"

#include <math.h>

namespace {
  const static float _X_VELO = 0.01f;
  const static float _Y_VELO = 0.1f;
  const static int _LOAD_TIME = 1000;
  const static int _LAUNCH_TIME = 150;
  const static float ANGLE_ADJUST_RATE = 0.0001f;
}

Catapult::Catapult(int x, int y, bool flipped, const SDL_Scancode *inputs) :
  x_(x), y_(y), angle_(0), launch_angle_(M_PI / 4.0f),
  dir_(Direction::NONE), state_(State::MOBILE), wait_counter_(0), dead_(false), flipped_(flipped) {
  sprites_.reset(new SpriteMap("catapult", 6, 16, 16));
  for (int i = 0; i < 6; ++i) inputs_[i] = inputs[i];
}

bool Catapult::update(const Input& input, const Map& map, const unsigned int elapsed) {
  if (dead_) return false;

  const State old_state = state_;

  if (input.key_held(inputs_[0])) {
    set_movement(Direction::LEFT);
  } else if (input.key_held(inputs_[1])) {
    set_movement(Direction::RIGHT);
  } else {
    set_movement(Direction::NONE);
  }

  if (input.key_held(inputs_[2])) {
    adjust_angle(-ANGLE_ADJUST_RATE * elapsed);
  } else if (input.key_held(inputs_[3])) {
    adjust_angle(ANGLE_ADJUST_RATE * elapsed);
  }

  if (input.key_pressed(inputs_[4])) ready_launch();
  if (input.key_pressed(inputs_[5])) launch();

  if (wait_counter_ > 0) {
    wait_counter_ -= elapsed;

    if (wait_counter_ <= 0) {
      switch (state_) {
        case State::LOADING:
          state_ = State::READY;
          break;

        case State::LAUNCHING:
          state_ = State::MOBILE;
          break;

        default:
          break;
      }
    }

  } else {

    switch (dir_) {
      case Direction::LEFT:
        x_ -= elapsed * _X_VELO;
        break;

      case Direction::RIGHT:
        x_ += elapsed * _X_VELO;
        break;

      default:
        break;
    }
  }

  settle(map);

  return state_ != old_state;
}

void Catapult::settle(const Map& map) {
  const float y1 = map.get_height(x_ - 4), y2 = map.get_height(x_ + 4);
  const float ny = (y1 + y2) / 2.0f;

  y_ = ny;
  angle_ = atan2f(y2 - y1, 8.0f);
}

void Catapult::draw(Graphics& graphics) const {
  if (dead_) return;

  int tile = 0;

  switch (state_) {
    case State::MOBILE:
      tile = 0;
      break;

    case State::LOADING:
      tile = (_LOAD_TIME - wait_counter_) / (_LOAD_TIME / 4);
      break;

    case State::READY:
      tile = 4;
      break;

    case State::LAUNCHING:
      tile = wait_counter_ / (_LAUNCH_TIME / 4);
      break;
  }

  sprites_->draw_ex(graphics, tile, x_ - 8, y_ - 16, flipped_, angle_, 8, 16);
}

SDL_Rect Catapult::hit_box() const {
  return { (int)x_ - 6, (int)y_ - 6, 12, 6 };
}

bool Catapult::point_within(float x, float y) const {
  const SDL_Rect b = hit_box();
  return x > b.x && x < b.x + b.w && y > b.y && y < b.y + b.h;
}

void Catapult::adjust_angle(float amount) {
  if (state_ == State::MOBILE) {
    launch_angle_ += amount;
    if (launch_angle_ < M_PI / 6.0f) launch_angle_ = M_PI / 6.0f;
    if (launch_angle_ > M_PI / 3.0f) launch_angle_ = M_PI / 3.0f;
  }
}

void Catapult::set_movement(Catapult::Direction dir) {
  if (state_ == State::MOBILE) dir_ = dir;
}

void Catapult::ready_launch() {
  if (state_ == State::MOBILE) {
    state_ = State::LOADING;
    wait_counter_ = _LOAD_TIME;
    dir_ = Direction::NONE;
  }
}

void Catapult::launch() {
  if (state_ == State::READY) {
    state_ = State::LAUNCHING;
    wait_counter_ = _LAUNCH_TIME;
    dir_ = Direction::NONE;
  }
}
