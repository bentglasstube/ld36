#include "backdrop.h"

Backdrop::Backdrop(const std::string& file) : file(file) {}

void Backdrop::draw(Graphics& graphics) {
  graphics.blit(file, NULL, NULL, Graphics::NONE);
}
