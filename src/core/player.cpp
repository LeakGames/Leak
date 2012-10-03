#include <cmath>
#include <boost/bind.hpp>

#include "main.h"
#include "../gui/gui.h"

extern "C" {
    #include "lua.h"
    #include "lualib.h"
    #include "lauxlib.h"
}


Player::Player(Grid *grid, sf::Color color, const char *fname) {
    int ptr = (int) this;
    this->color = color;
    this->grid = grid;
    this->l = luaL_newstate();
    luaL_dofile(this->l, fname);

    lua_pushlightuserdata(this->l, this);
    lua_setglobal(this->l, "player");

    lua_pushcfunction(this->l, API_move);
    lua_setglobal(this->l, "move");
}

int Player::move(int sx, int sy, int x, int y) {
    if (this->grid->matrix[sy][sx].player->color == this->color && (abs(y - sy) == 1 || abs(y - sy) == 0) && (abs(x - sx) == 1 || abs(x - sx) == 0))
        this->grid->set(x, y, this);

    return 0;
}

void Player::turn() {
    lua_getglobal(this->l, "turn");
    lua_pcall(this->l, 0, 0, 0);
}