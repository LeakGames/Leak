#include <cmath>
#include <boost/bind.hpp>
#include <iostream>

#include "main.h"
#include "../gui/gui.h"

extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

using namespace std;

Player::Player(Grid *grid, sf::Color color, const char *fname) {
    int ptr = (int) this;
    this->color = color;
    this->grid = grid;
    this->excluded = false;
    this->l = luaL_newstate();
    this->atk = 0;
    this->def = 0;

    // CLASS, TODO: Make it read-only
    lua_pushlightuserdata(this->l, this);
    lua_setglobal(this->l, "player");

    // APIs
    lua_pushcfunction(this->l, API_move);
    lua_setglobal(this->l, "move");
    lua_pushcfunction(this->l, API_getprop);
    lua_setglobal(this->l, "getprop");

    if (luaL_dofile(this->l, fname)) {
        cerr << (string) lua_tostring(this->l, -1) << endl;
        return;
    }

    luaL_openlibs(this->l);

    if (lua_pcall(this->l, 0, LUA_MULTRET, 0)) {
        cerr << (string) lua_tostring(this->l, -1) << endl;
        return;
    }
}

int Player::move(int sx, int sy, int x, int y) {
    if (this->excluded || this->moved)
        return 0;

    if ((abs(y - sy) == 1 || abs(y - sy) == 0) && (abs(x - sx) == 1 || abs(x - sx) == 0)) {
        if (this->grid->matrix[sy][sx].player->color == this->color)
            this->grid->set(x, y, this);
        else
            this->attack(sx, sy, x, y);
    }

    this->moved = true;

    return 0;
}

int Player::attack(int sx, int sy, int x, int y) {
    Player *attacker = this->grid->matrix[sx][sy].player,
           *defender = this->grid->matrix[sx][sy].player;

    if (attacker->atk + this->grid->matrix[sx][sy].atk > defender->def + this->grid->matrix[x][y].def) {
        this->grid->set(x, y, this);
        defender->atk--;
        defender->def--;
    }
    
    return 0;
}

void Player::turn() {
    lua_getglobal(this->l, "turn");
    lua_pcall(this->l, 0, 0, 0);
    this->moved = false;
}