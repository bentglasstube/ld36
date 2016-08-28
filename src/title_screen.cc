#include "title_screen.h"

#include "battle_screen.h"

void TitleScreen::init() {
  text_.reset(new Text("text"));
}

bool TitleScreen::update(Input& input, Audio&, Graphics&, unsigned int) {
  return !input.any_pressed();
}

void TitleScreen::draw(Graphics& graphics) {
  text_->draw(graphics, "<Insert Title Here>", 320, 128, Text::CENTER);
  text_->draw(graphics, "Press any key", 320, 264, Text::CENTER);
}

Screen* TitleScreen::next_screen() {
  return new BattleScreen();
}
