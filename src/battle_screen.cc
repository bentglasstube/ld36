#include "battle_screen.h"

void BattleScreen::init() {
  text_.reset(new Text("text"));
  tiles_.reset(new SpriteMap("tiles", 16, 8, 8));
  p1_.reset(new Catapult(30, 304));
  p2_.reset(new Catapult(594, 304));
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
  if (input.key_pressed(SDLK_w)) p1_->launch();

  if (input.key_held(SDLK_k)) {
    p2_->set_movement(Catapult::LEFT);
  } else if (input.key_held(SDLK_SEMICOLON)) {
    p2_->set_movement(Catapult::RIGHT);
  } else {
    p2_->set_movement(Catapult::NONE);
  }

  if (input.key_pressed(SDLK_l)) p2_->ready_launch();
  if (input.key_pressed(SDLK_o)) p2_->launch();

  p1_->update(audio, elapsed);
  p2_->update(audio, elapsed);

  return true;
}

void BattleScreen::draw(Graphics& graphics) {
  for (int y = 0; y < 60; ++y) {
    for (int x = 0; x < 80; ++x) {
      // TODO real map data structure
      int tile = y < 40 ? 0 : y == 40 ? 1 : 2;
      tiles_->draw(graphics, tile, x * 8, y * 8, false);
    }
  }

  p1_->draw(graphics, false);
  p2_->draw(graphics, true);

  // TODO draw UI
}

Screen* BattleScreen::next_screen() {
  return NULL;
}
