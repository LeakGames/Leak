#include <SFML/Graphics.hpp>
#include <vector>

#ifndef MAIN_H
#include "main.h"
#endif

#define CELL_H

typedef struct Cell {
    sf::RectangleShape *rect;
    Player *player;
    int x;
    int y;
    int atk_bonus;
    int def_bonus;
} Cell;