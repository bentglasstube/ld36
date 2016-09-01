#include <SDL2/SDL.h>

#include "title_screen.h"

#include "framework/game.h"

int main(int, char**) {
  Game game(640, 360);
  game.loop(new TitleScreen());

  return 0;
}
