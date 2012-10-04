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
    int set(int x, int y, Player *p);    
    void spawn_player( const int cell_free );
    void print_matrix();
};

class Player {
public:
    vector<int> bonuses;
    int starting_x, starting_y, kills, deaths, atk, def;
    sf::Color color;
    float exp;
    Grid *grid;
    lua_State *l;
    bool excluded, moved;

    Player(Grid *grid, sf::Color color, const char *fname);
    ~Player();

    int move(int sx, int sy, int x, int y);
    int attack(int sx, int sy, int x, int y);
    int scan(const int x, const int y);
    void turn();
};

// APIs
int API_move(lua_State *L);
int API_getprop(lua_State *L);

#endif
