#pragma once

#include <SDL2/SDL.h>
#include <string>
#include <map>

class Graphics {
  public:

    enum FlipDirection { NONE, HORIZONTAL, VERTICAL, BOTH };

    Graphics();
    ~Graphics();

    void blit(const std::string& file, const SDL_Rect* srect, const SDL_Rect* drect);
    void blit_ex(const std::string& file, const SDL_Rect* s, const SDL_Rect* d, const float angle, const SDL_Point* center, const FlipDirection flip);
    void flip();
    void clear();

    void draw_pixel(int x, int y, int color);
    void draw_line(int x1, int y1, int x2, int y2, int color);
    void draw_rect(SDL_Rect* rect, int color, bool filled);

    SDL_Texture* load_image(const std::string& file);

  private:

    typedef std::map<std::string, SDL_Texture*> TextureMap;
    TextureMap textures;
    SDL_Window* window;
    SDL_Renderer* renderer;

    void set_color(int color);
};
