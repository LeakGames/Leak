#include <SFML/Graphics.hpp>
#include "player.h"
#include <vector>

typedef struct Cell {
    sf::RectangleShape *rect;
    Player *player;
    int x;
    int y;
    int atk_bonus;
    int def_bonus;
} Cell;