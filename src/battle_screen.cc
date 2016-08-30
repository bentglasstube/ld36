#include "battle_screen.h"

#include "math.h"

#define randf(high, low)  (low + static_cast <float> (rand()) / static_cast <float> (RAND_MAX/(high - low)))

namespace {
  const static float BOULDER_VELOCITY = 0.2f;
  const static SDL_Scancode P1_KEYS[6] = {
    SDL_SCANCODE_A, SDL_SCANCODE_D,
    SDL_SCANCODE_Q, SDL_SCANCODE_E,
    SDL_SCANCODE_S, SDL_SCANCODE_W,
  };
  const static SDL_Scancode P2_KEYS[6] = {
    SDL_SCANCODE_J, SDL_SCANCODE_L,
    SDL_SCANCODE_U, SDL_SCANCODE_O,
    SDL_SCANCODE_K, SDL_SCANCODE_I,
  };
}

void BattleScreen::init() {
  text_.reset(new Text("text", 8));

  p1score_ = p2score_ = 0;
  state_ = BattleScreen::COUNTDOWN;
  counter_ = 1500;

  reset_game();
}

bool BattleScreen::update(Input& input, Audio& audio, unsigned int elapsed) {
  auto particle = particles_.begin();
  while (particle != particles_.end()) {
    (*particle).update(elapsed);
    particle = (*particle).done() ? particles_.erase(particle) : ++particle;
  }

  clouds_.update(elapsed);
  counter_ -= elapsed;

  switch (state_) {
    case COUNTDOWN:
      if (counter_ < 0) {
        state_ = FIGHT;
        counter_ = 0;
      }
      break;

    case FIGHT:
      if (p1_->update(input, map_, elapsed)) {
        switch (p1_->get_state()) {

          case Catapult::LOADING:
            audio.play_sample("ready");
            break;

          case Catapult::LAUNCHING:
            audio.play_sample("launch");
            launch_boulder(p1_->launch_x(), p1_->launch_y(), p1_->launch_angle());
            break;

          default:
            break;
        }
      }

      if (p2_->update(input, map_, elapsed)) {
        switch (p2_->get_state()) {

          case Catapult::LOADING:
            audio.play_sample("ready");
            break;

          case Catapult::LAUNCHING:
            audio.play_sample("launch");
            launch_boulder(p2_->launch_x(), p2_->launch_y(), p2_->launch_angle());
            break;

          default:
            break;
        }
      }

      {
        auto boulder = boulders_.begin();
        while (boulder != boulders_.end()) {
          (*boulder).update(elapsed);

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
          } else if ((*boulder).get_x() < 0 || (*boulder).get_x() > 640) {
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

  return !input.key_pressed(SDL_SCANCODE_ESCAPE);
}

void BattleScreen::draw(Graphics& graphics) const {
  map_.draw(graphics);

  p1_->draw(graphics);
  p2_->draw(graphics);

  for (auto i = boulders_.begin(); i != boulders_.end(); ++i) (*i).draw(graphics);
  for (auto i = particles_.begin(); i != particles_.end(); ++i) (*i).draw(graphics);

  clouds_.draw(graphics);

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

void BattleScreen::launch_boulder(int x, int y, float angle) {
  boulders_.emplace_back(x, y, BOULDER_VELOCITY * cosf(angle), BOULDER_VELOCITY * sinf(angle));
}

void BattleScreen::add_dirt_particles(int x, int y, int n) {
  for (int i = 0; i < n; ++i) {
    const float a = randf(M_PI, 2 * M_PI);
    const float v = randf(0, 0.2);
    particles_.emplace_back(x, y, v * cosf(a), v * sinf(a), 0.001f, 0xa46422ff, 400);
  }
}

void BattleScreen::add_smoke_particles(int x, int y, int n) {
  for (int i = 0; i < n; ++i) {
    particles_.emplace_back(x + randf(-3, 3), y + randf(-3, 3), randf(-0.02, 0.02), randf(-0.06, 0), 0, 0xffffffff, randf(400, 600));
  }
}

void BattleScreen::reset_game() {
  map_.generate_terrain();
  clouds_.randomize();
  p1_.reset(new Catapult(48, map_.get_height(48), false, P1_KEYS));
  p2_.reset(new Catapult(592, map_.get_height(592), true, P2_KEYS));
  boulders_.clear();

  p1_->settle(map_);
  p2_->settle(map_);
}
