#include "graphics.h"

namespace {
  const unsigned int width = 640;
  const unsigned int height = 360;
}

Graphics::Graphics() {
  int flags = SDL_WINDOW_OPENGL | SDL_WINDOW_RESIZABLE | SDL_WINDOW_FULLSCREEN_DESKTOP;

  window_ = SDL_CreateWindow("Catapults", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags);
  renderer_ = SDL_CreateRenderer(window_, -1, 0);

  SDL_SetHint(SDL_HINT_RENDER_SCALE_QUALITY, "nearest"); // retro!
  SDL_RenderSetLogicalSize(renderer_, width, height);
  SDL_SetRenderDrawBlendMode(renderer_, SDL_BLENDMODE_BLEND);
}

Graphics::~Graphics() {
  for (TextureMap::iterator i = textures_.begin(); i != textures_.end(); ++i) {
    SDL_DestroyTexture(i->second);
  }

  SDL_DestroyRenderer(renderer_);
  SDL_DestroyWindow(window_);
}

void Graphics::blit(const std::string& file, const SDL_Rect* srect, const SDL_Rect* drect) {
  SDL_Texture* texture = load_image(file);
  SDL_RenderCopy(renderer_, texture, srect, drect);
}

void Graphics::blit_ex(const std::string& file, const SDL_Rect* srect, const SDL_Rect* drect, const float angle, const SDL_Point* center, const Graphics::FlipDirection flip) {
  SDL_RendererFlip f = SDL_FLIP_NONE;
  switch (flip) {
    case NONE:
      f = SDL_FLIP_NONE;
      break;

    case HORIZONTAL:
      f = SDL_FLIP_HORIZONTAL;
      break;

    case VERTICAL:
      f = SDL_FLIP_VERTICAL;
      break;

    case BOTH:
      f = (SDL_RendererFlip) (SDL_FLIP_HORIZONTAL | SDL_FLIP_VERTICAL);
      break;
  }

  SDL_Texture* texture = load_image(file);
  SDL_RenderCopyEx(renderer_, texture, srect, drect, angle * 180.0f / M_PI, center, f);
}

void Graphics::flip() {
  SDL_RenderPresent(renderer_);
}

void Graphics::clear() {
  SDL_SetRenderDrawColor(renderer_, 0, 0, 0, 255);
  SDL_RenderClear(renderer_);
}

void Graphics::draw_pixel(int x, int y, int color) {
  set_color(color);
  SDL_RenderDrawPoint(renderer_, x, y);
}

void Graphics::draw_line(int x1, int y1, int x2, int y2, int color) {
  set_color(color);
  SDL_RenderDrawLine(renderer_, x1, y1, x2, y2);
}

void Graphics::draw_rect(const SDL_Rect* rect, int color, bool filled) {
  set_color(color);
  filled ? SDL_RenderFillRect(renderer_, rect) : SDL_RenderDrawRect(renderer_, rect);
}

SDL_Texture* Graphics::load_image(const std::string& file) {
  const std::string path("content/" + file+ ".bmp");
  if (textures_.count(path) == 0) {
    SDL_Surface* surface = SDL_LoadBMP(path.c_str());
    const Uint32 black = SDL_MapRGB(surface->format, 0, 0, 0);
    SDL_SetColorKey(surface, SDL_TRUE, black);

    textures_[path] = SDL_CreateTextureFromSurface(renderer_, surface);
  }

  return textures_[path];
}

void Graphics::set_color(int color) {
  const int r = (color & 0xff000000) >> 24;
  const int g = (color & 0x00ff0000) >> 16;
  const int b = (color & 0x0000ff00) >> 8;
  const int a = (color & 0x000000ff);

  SDL_SetRenderDrawColor(renderer_, r, g, b, a);
}
