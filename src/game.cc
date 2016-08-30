#include "game.h"

#include <SDL2/SDL.h>
#include <stdlib.h>
#include <time.h>

#include "audio.h"
#include "input.h"
#include "text.h"
#include "title_screen.h"

namespace {
  // const unsigned int FPS = 60;
  // const unsigned int MSPF = 1000 / FPS;
}

Game::Game() {
  srand(static_cast<unsigned int>(time(NULL)));
  SDL_Init(SDL_INIT_EVERYTHING);
}

Game::~Game() {
  SDL_Quit();
}

void Game::loop() {
  Graphics graphics;
  Audio audio;
  Input input;

  Text text("text");

  unsigned int last_update = SDL_GetTicks();

  screen_.reset(new TitleScreen());
  screen_->init();

  while (true) {
    // const unsigned int start = SDL_GetTicks();

    if (!audio.music_playing()) audio.play_music(screen_->get_music_track());
    if (!screen_->process_input(input)) return;

    const unsigned int update = SDL_GetTicks();
    const unsigned int frame_ticks = update - last_update;
    if (screen_->update(input, audio, frame_ticks)) {

      graphics.clear();
      screen_->draw(graphics);
      graphics.flip();

    } else {

      screen_.reset(screen_->next_screen());
      if (!screen_) return;
      screen_->init();

      audio.stop_music();
    }

    last_update = update;

    // const unsigned int elapsed = SDL_GetTicks() - start;
    // if (MSPF > elapsed) SDL_Delay(MSPF - elapsed);
  }
}
