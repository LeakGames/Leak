#include <cmath>
#include <string>
#include <vector>
#include <SFML/Graphics.cpp>

#include "main.h"

Bonus::Bonus(Player *p) {
    this->player = p;
}

void Bonus::activate_bonus(int bonus) {
    int idx = index_of<int>(bonus, this->bonuses);

    if (idx < 0 || index_of<int>(bonus, this->active_bonuses) != -1)
      return;

    this->active_bonuses.push_back(bonus);
    this->bonuses.erase(idx);
}

void Bonus::on_end_turn() {
    if (index_of<int>(BONUS_INVULNERABILITY, this->active_bonuses) != -1)
        (this->actived_turns[abs(BONUS_INVULNERABILITY) - 1])++;

    if (this->actived_turns[abs(BONUS_INVULNERABILITY) - 1] == 4) {
        this->actived_turns[abs(BONUS_INVULNERABILITY) - 1] = 0;
        this->actived_bonuses.erase(index_of<int>(BONUS_INVULNERABILITY, this->active_bonuses));
    }
}

void Bonus::on_move(int sx, int sy, int x, int y) {
    if (index_of<int>(BONUS_INVULNERABILITY, this->active_bonuses) != -1) {
        this->actived_turns[abs(BONUS_INVULNERABILITY) - 1] = 0;
        this->actived_bonuses.erase(index_of<int>(BONUS_INVULNERABILITY, this->active_bonuses));
    }
}

void Bonus::delete(int bonus) {
    this->actived_bonuses.erase(index_of<int>(bonus, this->active_bonuses));
}

bool Bonus::is_actived(int bonus) {
    return (bool) index_of<int>(bonus, this->active_bonuses) != -1;
}