#include <SDL2/SDL.h>

#include "title_screen.h"

#include "game.h"

int main(int, char**) {
  Game game("Catapults", 640, 360);
  game.loop(new TitleScreen());

  return 0;
}
