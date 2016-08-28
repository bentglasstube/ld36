#include "battle_screen.h"

#include "math.h"

#define randf(high, low)  (low + static_cast <float> (rand()) / static_cast <float> (RAND_MAX/(high - low)))

namespace {
  const static float ANGLE_ADJUST_RATE = 0.0001f;
}

void BattleScreen::init() {
  text_.reset(new Text("text", 8));

  p1score_ = p2score_ = 0;
  state_ = BattleScreen::COUNTDOWN;
  counter_ = 1500;

  reset_game();
}

bool BattleScreen::update(Input& input, Audio& audio, Graphics&, unsigned int elapsed) {
  auto particle = particles_.begin();
  while (particle != particles_.end()) {
    (*particle).update(elapsed);
    particle = (*particle).done() ? particles_.erase(particle) : ++particle;
  }

  counter_ -= elapsed;

  switch (state_) {
    case COUNTDOWN:
      if (counter_ < 0) {
        state_ = FIGHT;
        counter_ = 0;
      }
      break;

    case FIGHT:
      if (input.key_held(SDLK_a)) {
        p1_->set_movement(Catapult::LEFT);
      } else if (input.key_held(SDLK_d)) {
        p1_->set_movement(Catapult::RIGHT);
      } else {
        p1_->set_movement(Catapult::NONE);
      }

      if (input.key_held(SDLK_q)) {
        p1_->adjust_angle(-ANGLE_ADJUST_RATE * elapsed);
      } else if (input.key_held(SDLK_e)) {
        p1_->adjust_angle(ANGLE_ADJUST_RATE * elapsed);
      }

      if (input.key_pressed(SDLK_s)) {
        if (p1_->ready_launch()) audio.play_sample("ready");
      } else if (input.key_pressed(SDLK_w)) {
        if (p1_->launch()) {
          audio.play_sample("launch");
          launch_boulder(
            p1_->get_x() - 7,
            p1_->get_y() - 7,
            0.2, 2 * M_PI - p1_->get_launch_angle() + p1_->get_angle());
        }
      }

      if (input.key_held(SDLK_k)) {
        p2_->set_movement(Catapult::LEFT);
      } else if (input.key_held(SDLK_SEMICOLON)) {
        p2_->set_movement(Catapult::RIGHT);
      } else {
        p2_->set_movement(Catapult::NONE);
      }

      if (input.key_held(SDLK_i)) {
        p2_->adjust_angle(-ANGLE_ADJUST_RATE * elapsed);
      } else if (input.key_held(SDLK_p)) {
        p2_->adjust_angle(ANGLE_ADJUST_RATE * elapsed);
      }

      if (input.key_pressed(SDLK_l)) {
        if (p2_->ready_launch()) audio.play_sample("ready");
      } else if (input.key_pressed(SDLK_o)) {
        if (p2_->launch()) {
          audio.play_sample("launch");
          launch_boulder(
            p2_->get_x() + 7,
            p2_->get_y() - 7,
            0.2, M_PI + p2_->get_launch_angle() + p2_->get_angle());
        }
      }

      p1_->update(map_, elapsed);
      p2_->update(map_, elapsed);

      {
        auto boulder = boulders_.begin();
        while (boulder != boulders_.end()) {
          (*boulder).update(audio, elapsed);

          bool erase = false;
          int ground_height = map_.get_height((*boulder).get_x());

          if (p1_->point_within((*boulder).get_x(), (*boulder).get_y())) {
            p1_->destroy();
            erase = true;
          } else if (p2_->point_within((*boulder).get_x(), (*boulder).get_y())) {
            p2_->destroy();
            erase = true;
          } else if ((*boulder).get_y() > ground_height) {
            map_.impact((*boulder).get_x());
            add_dirt_particles((*boulder).get_x(), (*boulder).get_y(), 50);

            audio.play_sample("thud");

            erase = true;
          }

          boulder = erase ? boulders_.erase(boulder) : boulder + 1;
        }
      }

      if (p1_->is_dead()) {
        add_dirt_particles(p1_->get_x(), p1_->get_y(), 500);
        add_smoke_particles(p1_->get_x(), p1_->get_y(), 100);
        audio.play_sample("explode");

        state_ = WINNER;
        counter_ = 5000;
        p2score_++;
      }

      if (p2_->is_dead()) {
        add_dirt_particles(p2_->get_x(), p2_->get_y(), 500);
        add_smoke_particles(p2_->get_x(), p2_->get_y(), 100);
        audio.play_sample("explode");

        state_ = WINNER;
        counter_ = 5000;
        p1score_++;
      }

      break;

    case WINNER:
      if (counter_ < 0) {
        state_ = COUNTDOWN;
        counter_ = 1500;
        reset_game();
      }

      break;
  }

  return !input.key_pressed(SDLK_ESCAPE);
}

void BattleScreen::draw(Graphics& graphics) {
  SDL_Rect full = { 0, 0, 640, 360 };
  graphics.draw_rect(&full, 0x31a2f2ff, true);

  map_.draw(graphics);

  p1_->draw(graphics, false);
  p2_->draw(graphics, true);

  for (auto i = boulders_.begin(); i != boulders_.end(); ++i) (*i).draw(graphics);
  for (auto i = particles_.begin(); i != particles_.end(); ++i) (*i).draw(graphics);

  char buffer[32];

  snprintf(buffer, 32, "%2.0f*", p1_->get_launch_angle() * 180 / M_PI);
  text_->draw(graphics, buffer, 4, 340);

  snprintf(buffer, 32, "%2.0f*", p2_->get_launch_angle() * 180 / M_PI);
  text_->draw(graphics, buffer, 636, 340, Text::RIGHT);

  if (state_ == COUNTDOWN) {
    snprintf(buffer, 32, "%d", counter_ / 500 + 1);
    text_->draw(graphics, buffer, 320, 100, Text::CENTER);
  } else if (state_ == WINNER) {
    int p = p1_->is_dead() ? 2 : 1;
    snprintf(buffer, 32, "Player %d scores!", p);
    text_->draw(graphics, buffer, 320, 100, Text::CENTER);
  }

  snprintf(buffer, 32, "%d : %d", p1score_, p2score_);
  text_->draw(graphics, buffer, 320, 340, Text::CENTER);
}

Screen* BattleScreen::next_screen() {
  return NULL;
}

void BattleScreen::launch_boulder(int x, int y, float v, float angle) {
  boulders_.push_back(Boulder(x, y, v * cosf(angle), v * sinf(angle)));
}

void BattleScreen::add_dirt_particles(int x, int y, int n) {
  for (int i = 0; i < n; ++i) {
    const float a = randf(M_PI, 2 * M_PI);
    const float v = randf(0, 0.2);
    particles_.push_back(Particle(x, y, v * cosf(a), v * sinf(a), 0xa46422ff, 400));
  }
}

void BattleScreen::add_smoke_particles(int x, int y, int n) {
  for (int i = 0; i < n; ++i) {
    particles_.push_back(Particle(x + randf(-3, 3), y + randf(-3, 3), randf(-0.02, 0.02), randf(-0.06, 0), 0xffffffff, randf(400, 600)));
  }
}

void BattleScreen::reset_game() {
  map_.generate_terrain();
  p1_.reset(new Catapult(48, map_.get_height(48)));
  p2_.reset(new Catapult(592, map_.get_height(592)));
  boulders_.clear();

  p1_->update(map_, 0);
  p2_->update(map_, 0);
}
