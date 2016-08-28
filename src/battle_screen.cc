#include "battle_screen.h"

#include "math.h"

#define randf(high, low)  (low + static_cast <float> (rand()) / static_cast <float> (RAND_MAX/(high - low)))

void BattleScreen::init() {
  text_.reset(new Text("text"));
  map_.generate_terrain();
  p1_.reset(new Catapult(48, map_.get_height(48)));
  p2_.reset(new Catapult(592, map_.get_height(592)));
}

bool BattleScreen::update(Input& input, Audio& audio, Graphics&, unsigned int elapsed) {
  if (input.key_held(SDLK_a)) {
    p1_->set_movement(Catapult::LEFT);
  } else if (input.key_held(SDLK_d)) {
    p1_->set_movement(Catapult::RIGHT);
  } else {
    p1_->set_movement(Catapult::NONE);
  }

  if (input.key_pressed(SDLK_s)) p1_->ready_launch();
  if (input.key_pressed(SDLK_w)) {
    // TODO adjustable angle
    if (p1_->launch()) launch_boulder(
        p1_->get_x() - 6,
        p1_->get_y() - 6,
        0.2, 7 * M_PI / 4.0f);
  }

  if (input.key_held(SDLK_k)) {
    p2_->set_movement(Catapult::LEFT);
  } else if (input.key_held(SDLK_SEMICOLON)) {
    p2_->set_movement(Catapult::RIGHT);
  } else {
    p2_->set_movement(Catapult::NONE);
  }

  if (input.key_pressed(SDLK_l)) p2_->ready_launch();
  if (input.key_pressed(SDLK_o)) {
    // TODO adjustable angle
    if (p2_->launch()) launch_boulder(
        p2_->get_x() + 6,
        p2_->get_y() - 6,
        0.2, 5 * M_PI / 4.0f);
  }

  p1_->update(audio, elapsed);
  p2_->update(audio, elapsed);

  // TODO adjust catapults to ground

  auto i = boulders_.begin();
  while (i != boulders_.end()) {
    bool erase = false;
    (*i)->update(audio, elapsed);

    const Boulder* boulder = (*i).get();

    int ground_height = map_.get_height(boulder->get_x());
    if (boulder->get_y() > ground_height) {
      map_.destroy(boulder->get_x(), boulder->get_y());
      erase = true;

      add_dirt_particles(boulder->get_x(), boulder->get_y(), 50);
    }

    // TODO collisions with players

    i = erase ? boulders_.erase(i) : i + 1;
  }

  auto j = particles_.begin();
  while (j != particles_.end()) {
    (*j).update(elapsed);
    j = (*j).done() ? particles_.erase(j) : ++j;
    // ++j;
  }

  return true;
}

void BattleScreen::draw(Graphics& graphics) {
  map_.draw(graphics);

  p1_->draw(graphics, false);
  p2_->draw(graphics, true);

  for (auto i = boulders_.begin(); i != boulders_.end(); ++i) {
    (*i)->draw(graphics);
  }

  for (auto i = particles_.begin(); i != particles_.end(); ++i) {
    (*i).draw(graphics);
  }

  // TODO draw UI
}

Screen* BattleScreen::next_screen() {
  return NULL;
}

void BattleScreen::launch_boulder(int x, int y, float v, float angle) {
  boulders_.push_back(std::unique_ptr<Boulder>(new Boulder(x, y, v * cosf(angle), v * sinf(angle))));
}

void BattleScreen::add_dirt_particles(int x, int y, int n) {
  for (int i = 0; i < n; ++i) {
    const float a = randf(M_PI, 2 * M_PI);
    const float v = randf(0, 0.2);
    particles_.push_back(Particle(x, y, v * cosf(a), v * sinf(a), .64f, .39f, .13f, 400));
  }
}

void BattleScreen::add_smoke_particles(int x, int y, int n) {
  for (int i = 0; i < n; ++i) {
    particles_.push_back(Particle(x + randf(-3, 3), y + randf(-3, 3), 0, randf(-0.06, 0), 1, 1, 1, randf(400, 600)));
  }
}
