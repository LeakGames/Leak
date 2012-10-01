#include <cmath>
#include "main.h"


Player::Player(Grid *grid, sf::Color color) {
  this->color = color;
  this->grid = grid;
}

bool Player::move(int sy, int sx, int x, int y) {
  if (this->grid(sy, sx).color == this->color && (abs(y - sy) == 1 || abs(y - sy) == 0) && (abs(x - sx) == 1 || abs(x - sx) == 0))
    return this->grid->set(x, y, this);

  return false;
}