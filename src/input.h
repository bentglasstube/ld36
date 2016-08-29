#pragma once

#include <map>
#include <SDL2/SDL.h>

#define MAX_AXES 64

class Input {
  public:

    void begin_frame();
    void key_down(const SDL_Event& event);
    void key_up(const SDL_Event& event);

    bool key_pressed(SDL_Scancode key) { return pressed[key]; }
    bool key_released(SDL_Scancode key) { return released[key]; }
    bool key_held(SDL_Scancode key) { return held[key]; }

    bool any_pressed() { return pressed.size() > 0; }

  private:

    std::map<SDL_Scancode, bool> held;
    std::map<SDL_Scancode, bool> pressed;
    std::map<SDL_Scancode, bool> released;

};
