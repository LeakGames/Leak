#include <SFML/Graphics.h>
#include "cell.h"
#include <vector>

class Player {
public:
    vector<Cell> *cells;
    vector<int> *bonuses;
    int starting_x, starting_y, kills, deaths;
    float exp;

    Player();
    ~Player();
    int move(const int sx, const int sy, const int x, const int y);
    int scan(const int x, const int y);
};