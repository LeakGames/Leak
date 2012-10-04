#include <cmath>
#include <cstdlib>
#include <boost/bind.hpp>
#include <iostream>
#include <string>

#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
 #endif

#include "main.h"
#include "../gui/gui.h"

extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}

using namespace std;

Player::Player(Grid *grid, sf::Color color, const char *fname) {
//    char temp[260];
    this->color = color;
    this->grid = grid;
    this->excluded = false;
    this->l = luaL_newstate();
    this->atk = 0;
    this->def = 0;

/*
    getcwd(temp, sizeof(temp));
    string path("LUA_PATH=");
    path.append(temp);
    path.append("\\Lua\\?.lua");
    cout << path << endl;
    putenv(path.c_str());
*/

    // CLASS, TODO: Make it read-only
    lua_pushlightuserdata(this->l, this);
    lua_setglobal(this->l, "player");

    // APIs
    lua_pushcfunction(this->l, API_move);
    lua_setglobal(this->l, "move");

    lua_pushcfunction(this->l, API_getprop);
    lua_setglobal(this->l, "getprop");

    lua_pushcfunction(this->l, API_getgridprops);
    lua_setglobal(this->l, "getgridprops");

    luaL_openlibs(this->l);

    if (luaL_dofile(this->l, fname)) {
        cerr << (string) lua_tostring(this->l, -1) << endl;
        return;
    }

    if (lua_pcall(this->l, 0, LUA_MULTRET, 0)) {
        cerr << (string) lua_tostring(this->l, -1) << endl;
        return;
    }
}

int Player::move(int sx, int sy, int x, int y) {
    if 
    (
        this->excluded      ||
        this->moved         ||
        x < 0               ||
        x > this->grid->w-1 ||
        y < 0               ||
        y > this->grid->h-1
    ) return 0;

    if ((abs(y - sy) == 1 || abs(y - sy) == 0) && (abs(x - sx) == 1 || abs(x - sx) == 0) && this->grid->gui->matrix[x][y].player != this && this->grid->gui->matrix[sx][sy].player == this) {
        if (!this->grid->gui->matrix[x][y].player)
            this->grid->set(x, y, this);
        else
            this->attack(sx, sy, x, y);
    }

    this->moved = true;

    return 0;
}

int Player::attack(int sx, int sy, int x, int y) {
    Player *attacker = this->grid->gui->matrix[sx][sy].player,
           *defender = this->grid->gui->matrix[x][y].player;

    cout << "ONATTACK" << endl;
    cout << defender->def << endl;
    cout << attacker->atk << endl;

    if (attacker->atk + this->grid->gui->matrix[sx][sy].atk > defender->def + this->grid->gui->matrix[x][y].def) {
        this->grid->set(x, y, this);
        defender->atk--;
        defender->def--;
    }
    
    return 0;
}

void Player::turn() {
    lua_getglobal(this->l, "turn");

    if (lua_pcall(this->l, 0, 0, 0))
        cerr << (string) lua_tostring(this->l, -1) << endl;
    
    this->moved = false;
}