#include <cmath>
#include <cstdlib>
#include <boost/algorithm/string.hpp>
#include <iostream>
#include <string>

/*
#ifdef WINDOWS
    #include <direct.h>
    #define GetCurrentDir _getcwd
#else
    #include <unistd.h>
    #define GetCurrentDir getcwd
 #endif
*/

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
    this->bonus = new Bonus(this);

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

    // CONSTANTS
    for (int i = 0; i < 8; i++) {
        lua_pushstring(this->l, names[i].c_str());
        lua_setglobal(this->l, boost::to_upper_copy(names[i]).c_str());
    }

    for (int x = 1; x <= 6; x++) {
        lua_pushnumber(this->l, -x);
        lua_setglobal(this->l, boost::to_upper_copy(bonus_names[x-1]).c_str());
    }

    lua_pushstring(this->l, color_to_string(this->color)->c_str());
    lua_setglobal(this->l, "COLOR");

    // APIs
    lua_pushcfunction(this->l, API_move);
    lua_setglobal(this->l, "move");

    lua_pushcfunction(this->l, API_getprop);
    lua_setglobal(this->l, "getprop");

    lua_pushcfunction(this->l, API_getgridprops);
    lua_setglobal(this->l, "getgridprops");

    lua_pushcfunction(this->l, API_getbonuses);
    lua_setglobal(this->l, "getbonuses");

    lua_pushcfunction(this->l, API_getactivebonuses);
    lua_setglobal(this->l, "getactivebonuses");

    lua_pushcfunction(this->l, API_activatebonus);
    lua_setglobal(this->l, "activatebonus");

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
    int range = 1;

    if
    (
        this->excluded      ||
        this->moved         ||
        x < 0               ||
        x > this->grid->w-1 ||
        y < 0               ||
        y > this->grid->h-1
    ) return 0;

    if (this->bonus->is_actived(BONUS_VELOCITY))
        range = 2;

    if ((in_range(sx, sy, x, y, range) || this->bonus->is_actived(BONUS_TELEPORT)) && this->grid->gui->matrix[x][y].player != this && this->grid->gui->matrix[sx][sy].player == this) {
        if (!this->grid->gui->matrix[x][y].player) {
            this->grid->set(x, y, this);
            
            if (this->grid->gui->matrix[x][y].bonus < 0)
                this->bonus->add_bonus(this->grid->gui->matrix[x][y].bonus);

            if (!in_range(sx, sy, x, y, range))
                this->bonus->deactivate(BONUS_TELEPORT);

        } else if (!this->bonus->is_actived(BONUS_TELEPORT))
            this->attack(sx, sy, x, y);
    }

    this->bonus->on_move(sx, sy, x, y);
    this->moved = true;

    return 0;
}

int Player::attack(int sx, int sy, int x, int y) {
    Player *attacker = this->grid->gui->matrix[sx][sy].player,
           *defender = this->grid->gui->matrix[x][y].player;

    cout << "ONATTACK" << endl;
    cout << defender->def << endl;
    cout << attacker->atk << endl;

    if (attacker->atk + this->grid->gui->matrix[sx][sy].atk > defender->def + this->grid->gui->matrix[x][y].def && !defender->bonus->is_actived(BONUS_INVULNERABILITY)) {
        this->grid->set(x, y, this);

        if (this->grid->gui->matrix[x][y].bonus < 0) {
            attacker->bonus->add_bonus(this->grid->gui->matrix[x][y].bonus);
            defender->bonus->deactivate(this->grid->gui->matrix[x][y].bonus);
        }

        defender->atk--;
        defender->def--;
    }
    
    return 0;
}

void Player::turn() {
    lua_getglobal(this->l, "turn");

    if (lua_pcall(this->l, 0, 0, 0))
        cerr << (string) lua_tostring(this->l, -1) << endl;
    
    this->bonus->on_end_turn();
    this->moved = false;
}