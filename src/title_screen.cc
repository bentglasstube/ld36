#include "title_screen.h"

#include "battle_screen.h"

void TitleScreen::init() {
  text_.reset(new Text("text"));
  backdrop_.reset(new Backdrop("title"));
  menu_.reset(new Menu("text"));

  menu_->add_entry("Practice");
  menu_->add_entry("Siege");
  menu_->add_entry("Local Battle");
  menu_->add_entry("Online Battle");
  menu_->add_entry("Quit");
}

bool TitleScreen::update(const Input& input, Audio&, unsigned int) {
  if (input.key_pressed(SDL_SCANCODE_W)) menu_->prev();
  if (input.key_pressed(SDL_SCANCODE_S)) menu_->next();

  if (input.key_pressed(SDL_SCANCODE_RETURN)) return false;

  if (input.key_pressed(SDL_SCANCODE_ESCAPE)) {
    menu_->select(4);
    return false;
  }

  return true;
}

void TitleScreen::draw(Graphics& graphics) const {
  backdrop_->draw(graphics);
  menu_->draw(graphics, 264, 200);
}

Screen* TitleScreen::next_screen() {
  switch (menu_->selected()) {
    case 0:
      return new BattleScreen(BattleScreen::GameMode::PRACTICE);

    case 1:
      return new BattleScreen(BattleScreen::GameMode::SIEGE);

    case 2:
      return new BattleScreen(BattleScreen::GameMode::BATTLE);

    case 3:
      // TODO online mode
      return new BattleScreen(BattleScreen::GameMode::PRACTICE);

    default:
      return NULL;
  }
}
