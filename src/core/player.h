#include <SFML/Graphics.hpp>
#include <vector>

using namespace std;

class Player {
public:
    vector<int> bonuses;
    int starting_x, starting_y, kills, deaths;
    float exp;

    Player();
    ~Player();
    int move(const int sx, const int sy, const int x, const int y);
    int scan(const int x, const int y);
};


typedef struct Cell {
    sf::RectangleShape *rect;
    Player *player;
    int x;
    int y;
    int atk_bonus;
    int def_bonus;
} Cell;