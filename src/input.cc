#include "input.h"

void Input::begin_frame() {
  pressed.clear();
  released.clear();
}

void Input::key_down(const SDL_Event& event) {
  pressed[event.key.keysym.sym] = true;
  held[event.key.keysym.sym] = true;
}

void Input::key_up(const SDL_Event& event) {
  released[event.key.keysym.sym] = true;
  held[event.key.keysym.sym] = false;
}
