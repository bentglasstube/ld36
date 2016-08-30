#include "backdrop.h"

Backdrop::Backdrop(const std::string& file) : file_(file) {}

void Backdrop::draw(Graphics& graphics) {
  graphics.blit(file_, NULL, NULL);
}
