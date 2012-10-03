#ifndef MAIN_H
#define MAIN_H

#include <vector>
#include <SFML/Graphics.hpp>

#include "../gui/gui.h"

extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

class Grid;
class Player;

using namespace std;

class Grid {
public:
    int w, h;
    vector<vector<Cell> > matrix;
    Gui *gui;

    Grid( const int n, const int m );
    Cell operator()( const int x, const int y);
    bool is_cell_free( const int x, const int y );
    void spawn_bonuses();
    bool set(int x, int y, Player *p);    
    void spawn_player( const int cell_free );
    void print_matrix();
};

class Player {
public:
    vector<int> bonuses;
    int starting_x, starting_y, kills, deaths;
    sf::Color color;
    float exp;
    Grid *grid;
    lua_State *L;

    Player(Grid *grid, sf::Color color);
    ~Player();
    bool move(const int sx, const int sy, const int x, const int y);
    int scan(const int x, const int y);
};

#endif
