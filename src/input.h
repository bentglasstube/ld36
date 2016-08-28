#pragma once

#include <map>
#include <SDL2/SDL.h>

#define MAX_AXES 64

class Input {
  public:

    void begin_frame();
    void key_down(const SDL_Event& event);
    void key_up(const SDL_Event& event);

    bool key_pressed(SDL_Keycode key) { return pressed[key]; }
    bool key_released(SDL_Keycode key) { return released[key]; }
    bool key_held(SDL_Keycode key) { return held[key]; }

    bool any_pressed() { return pressed.size() > 0; }

  private:

    std::map<SDL_Keycode, bool> held;
    std::map<SDL_Keycode, bool> pressed;
    std::map<SDL_Keycode, bool> released;

};
