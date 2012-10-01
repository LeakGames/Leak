#include <SFML/Graphics.h>
#include <vector>

class Player {
public:
    sf::RectangleShape rect;
    int starting_x, starting_y, kills, deaths;
    vector<int> *bonuses;
    float exp;

    Player();
    ~Player();
    int move(const int sx, const int sy, const int x, const int y);
    int scan(const int x, const int y);
};