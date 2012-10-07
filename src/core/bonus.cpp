#include <iostream>
#include <cmath>
#include <string>
#include <vector>
#include <SFML/Graphics.hpp>

#include "main.h"

using namespace std;

Bonus::Bonus(Player *p) {
    this->player = p;

    for (int n = 0; n < 6; n++)
        this->actived_turns.push_back(0);
}

void Bonus::add_bonus(int bonus) {
    this->bonuses.push_back(bonus);
}

void Bonus::activate_bonus(int bonus, int x, int y) {
    int idx = index_of<int>(bonus, this->bonuses), def;

    if (idx < 0 || index_of<int>(bonus, this->active_bonuses) != -1 || x > this->player->grid->w-1 || x < 0 || y > this->player->grid->h-1 || y < 0)
      return;

    switch (bonus) {
        case BONUS_EXCHANGE:
            def = this->player->grid->gui->matrix[x][y].def;
            this->player->grid->gui->matrix[x][y].def = this->player->grid->gui->matrix[x][y].atk;
            this->player->grid->gui->matrix[x][y].atk = def;
            break;

        case BONUS_TELEPORT:
            this->player->grid->set(x, y, this->player);
            break;

        default:
            this->active_bonuses.push_back(bonus);
            break;
    }

    this->bonuses.erase(this->bonuses.begin() + idx);
}

void Bonus::on_end_turn() {
    for (int n = 0; n < this->active_bonuses.size(); n++)
        this->actived_turns[abs(this->active_bonuses[n]) - 1]++;

    if (this->actived_turns[abs(BONUS_INVULNERABILITY) - 1] == 4) {
        this->deactivate(BONUS_INVULNERABILITY);
    }
}

void Bonus::on_move(int sx, int sy, int x, int y) {
    if (index_of<int>(BONUS_INVULNERABILITY, this->active_bonuses) != -1) {
        this->deactivate(BONUS_INVULNERABILITY);
    }
}

void Bonus::deactivate(int bonus) {
    this->actived_turns[abs(bonus) - 1] = 0;
    this->active_bonuses.erase(this->active_bonuses.begin() + index_of<int>(bonus, this->active_bonuses));
}

bool Bonus::is_actived(int bonus) {
    return (bool) index_of<int>(bonus, this->active_bonuses) != -1;
}