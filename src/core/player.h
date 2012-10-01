#include <SFML/Graphics.h>

class Player {
public:
    sf::Color color;
    int starting_x, starting_y, kills, deaths;
    vector<int> *bonuses;
    float exp;

    Player();
    ~Player();
    int move(int x, int y);
    int scan(int x, int y);
};