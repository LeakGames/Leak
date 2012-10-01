#include <SFML/Graphics.h>
#include "player.h"
#include <vector>

typedef struct Cell {
    vector<sf::RectangleShape> *rect;
    Player *player;
    int x;
    int y;
    int atk_bonus;
    int def_bonus;
} Cell;