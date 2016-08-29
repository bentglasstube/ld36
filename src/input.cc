#include "input.h"

void Input::begin_frame() {
  pressed.clear();
  released.clear();
}

void Input::key_down(const SDL_Event& event) {
  pressed[event.key.keysym.scancode] = true;
  held[event.key.keysym.scancode] = true;
}

void Input::key_up(const SDL_Event& event) {
  released[event.key.keysym.scancode] = true;
  held[event.key.keysym.scancode] = false;
}
