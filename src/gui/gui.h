#ifndef GUI_H
#define GUI_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>

#include "../core/main.h"

class Player;

using namespace std;

typedef struct Cell {
    sf::RectangleShape *rect;
    Player *player;
    int x;
    int y;
    int atk;
    int def;
} Cell;

class Gui {    
public:
    int width_window, height_window;
    int width_matrix, height_matrix;
    Gui(const int, const int, const int, const int);
    ~Gui();
    void create_matrix();
    void display_window();
    sf::RenderWindow get_window();
    void set_color(int, int, sf::Color);

protected:
    sf::RenderWindow window;
    sf::Font font;
    sf::Text text;
    vector< vector<Cell> > matrix;
    sf::RectangleShape rectangle;
};
#endif