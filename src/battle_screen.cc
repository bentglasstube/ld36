#include "battle_screen.h"

#include "math.h"

void BattleScreen::init() {
  text_.reset(new Text("text"));
  p1_.reset(new Catapult(40, 0));
  p2_.reset(new Catapult(592, 0));

  map_.generate_terrain();

  p1_->set_y(map_.get_height(p1_->get_x()) * 8 - 8);
  p2_->set_y(map_.get_height(p2_->get_x()) * 8 - 8);
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
    if (p1_->launch()) launch_boulder(p1_->get_x(), p1_->get_y(), 0.2, 7 * M_PI / 4.0f);
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
    if (p2_->launch()) launch_boulder(p2_->get_x(), p2_->get_y(), 0.2, 5 * M_PI / 4.0f);
  }

  p1_->update(audio, elapsed);
  p2_->update(audio, elapsed);

  auto i = boulders_.begin();
  while (i != boulders_.end()) {
    (*i)->update(audio, elapsed);

    // TODO collisions

    ++i;
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

  // TODO draw UI
}

Screen* BattleScreen::next_screen() {
  return NULL;
}

void BattleScreen::launch_boulder(int x, int y, float v, float angle) {
  boulders_.push_back(std::unique_ptr<Boulder>(new Boulder(x, y, v * cosf(angle), v * sinf(angle))));
}
