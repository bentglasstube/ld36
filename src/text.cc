#include "text.h"

Text::Text(const std::string& file, const int width) : file(file), width(width) {}

void Text::draw(Graphics& graphics, const std::string& text, int x, int y, Text::Alignment alignment) {
  SDL_Rect source = { 0, 0, width, width * 2};
  SDL_Rect dest = { x, y, width, width * 2 };

  switch (alignment) {
    case LEFT:
      break;

    case CENTER:
      dest.x -= width / 2 * text.length();
      break;

    case RIGHT:
      dest.x -= width * text.length();
      break;
  }

  for (std::string::const_iterator i = text.begin(); i != text.end(); ++i) {
    unsigned int n = 0;
    if ((*i) >= ' ' && (*i) <= '~') n = (*i) - ' ';

    source.x = width * (n % 16);
    source.y = width * 2 * (n / 16);

    graphics.blit(file, &source, &dest);

    if ((*i) == '\n' && alignment == LEFT) {
      dest.x = x;
      dest.y += width * 2;
    } else {
      dest.x += width;
    }
  }
}
