#ifndef MAIN_H
#define MAIN_H

#include <vector>
#include <SFML/Graphics.hpp>
#include <string>

#include "../gui/gui.h"

extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

class Grid;
class Player;
class Bonus;

using namespace std;

extern sf::Color colors[8];
extern string names[8];
extern string bonus_names[6];

enum Bonuses {
    BONUS_VELOCITY = -1,
    BONUS_TELEPORT = -2,
    BONUS_INVULNERABILITY = -3,
    BONUS_ATK = -4,
    BONUS_EXCHANGE = -5,
    BONUS_BLACKSTAR = -6
};

class Grid {
public:
    int w, h;
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
    int starting_x, starting_y, kills, deaths, atk, def;
    sf::Color color;
    float exp;
    Grid *grid;
    Bonus *bonus;
    lua_State *l;
    bool excluded, moved;


    Player(Grid *grid, sf::Color color, const char *fname);
    ~Player();

    int move(int sx, int sy, int x, int y);
    int attack(int sx, int sy, int x, int y);
    int scan(const int x, const int y);
    void turn();
};

class Bonus {
public:
    Player *player;
    vector<int> active_bonuses;
    vector<int> bonuses;
    vector<int> actived_turns;

    Bonus(Player *p);

    void on_move(int sx, int sy, int x, int y);
    void on_attack(int sx, int sy, int x, int y);
    void on_end_turn();
    void activate_bonus(int bonus, int x, int y);
    void add_bonus(int bonus);
    void deactivate(int bonus);
    bool is_actived(int bonus);
};

// APIs
int API_move(lua_State *L);
int API_getprop(lua_State *L);
int API_getgridprops(lua_State *L);
int API_getactivebonuses(lua_State *L);
int API_getbonuses(lua_State *L);
int API_activatebonus(lua_State *L);

// helpers
string *color_to_string(sf::Color color);
bool in_range(int sx, int sy, int x, int y, int range);

template <class T>
int index_of(T needle, vector<T> haystack) { // This should be in helpers.cpp, but C++ is so shitty that you can't declare a prototype of a templated function. Hate.
    for (int n = 0; n < haystack.size(); n++) {
        if (haystack[n] == needle)
            return n;
    }

    return -1;
}

#endif
