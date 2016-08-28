#include "text.h"

Text::Text(const std::string& file) : file(file) {}

void Text::draw(Graphics& graphics, const std::string& text, int x, int y, Text::Alignment alignment) {
  SDL_Rect source = { 0, 0, 8, 16 };
  SDL_Rect dest = { x, y, 8, 16 };

  switch (alignment) {
    case LEFT:
      break;

    case CENTER:
      dest.x -= 4 * text.length();
      break;

    case RIGHT:
      dest.x -= 8 * text.length();
      break;
  }

  for (std::string::const_iterator i = text.begin(); i != text.end(); ++i) {
    unsigned int n = 0;
    if ((*i) >= ' ' && (*i) <= '~') n = (*i) - ' ';

    source.x = 8 * (n % 16);
    source.y = 16 * (n / 16);

    graphics.blit(file, &source, &dest, Graphics::NONE);

    if ((*i) == '\n' && alignment == LEFT) {
      dest.x = x;
      dest.y += 16;
    } else {
      dest.x += 8;
    }
  }
}
