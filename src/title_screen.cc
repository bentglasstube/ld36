#include "title_screen.h"

#include "battle_screen.h"

void TitleScreen::init() {
  text_.reset(new Text("text"));
  backdrop_.reset(new Backdrop("title"));
}

bool TitleScreen::update(Input& input, Audio&, unsigned int) {
  return !input.any_pressed();
}

void TitleScreen::draw(Graphics& graphics) const {
  backdrop_->draw(graphics);
  text_->draw(graphics, "Press any key", 320, 340, Text::Alignment::CENTER);

  text_->draw(graphics, "- Player 1 - \nA/D - Move\nQ/E - Adjust angle\nS - Load catapult\nW - Fire", 8, 200);
  text_->draw(graphics, "- Player 2 - \nJ/L - Move\nU/O - Adjust angle\nK - Load catapult\nI - Fire", 480, 200);
}

Screen* TitleScreen::next_screen() {
  return new BattleScreen();
}
