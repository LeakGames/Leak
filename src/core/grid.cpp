#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>
#include <boost/thread.hpp>
#include <string>
#include <map>

#include "main.h"
#include "../gui/gui.h"

using namespace std;

Grid::Grid( const int w, const int h ) {
    int i, j, c;

    this->w = w;
    this->h = h;
    this->gui = new Gui(500, 500, w, h);
    this->gui->create_matrix();
    this->gui->set_color(1, 1, sf::Color::Green);

    boost::thread t1(&Gui::display_window, this->gui);

    for( c = 0; c < ceil( (float)this->w / 2 ); c++ ) {
        for( i = c; i < this->w - c; i++ ) {
            for( j = c; j < this->h - c; j++ ) {
                this->gui->matrix[i][j].atk = ( c <= ceil( ( float )this->w / 2 ) / 2 ) ? c : ( c * c );
                this->gui->matrix[i][j].def = -( ( ceil( ( float )this->w / 2 ) / 4 ) + c / 2 );

                if( c == ceil( ( float ) this->w/ 2 ) - 1 ) {
                    this->gui->matrix[i][j].atk = 100;
                    this->gui->matrix[i][j].def = -10;
                }

                this->gui->matrix[i][j].player = NULL;
                this->gui->matrix[i][j].bonus = 0;
            }
        }
    }

    this->gui->matrix[3][3].bonus = BONUS_EXCHANGE;
    this->gui->matrix[2][2].bonus = BONUS_TELEPORT;
}

Cell Grid::operator()(int x, int y) {
    return this->gui->matrix[x][y];
}

int Grid::set(int x, int y, Player *p) {
    // call GUI methods
    if (this->gui->matrix[x][y].player && this->gui->matrix[x][y].player == p)
        return 0;

    this->gui->set_color(x, y, p->color);
    this->gui->matrix[x][y].player = p;
    p->atk++;
    p->def++;
    
    return 0;
}

bool Grid::is_cell_free( const int x, const int y ) {
    return ( bool ) ( !this->gui->matrix[x][y].player );
}

void Grid::spawn_player( const int cell_free ) {
    int i, j, rand_seed_n, rand_seed_m;
    bool flag;
    
    do {
        flag = false;
        rand_seed_n = rand() % this->w;
        rand_seed_m = rand() % this->h;

        if( ( rand_seed_n > ( this->w - cell_free )) || ( rand_seed_n > ( this->h - cell_free ) ) ) {
            rand_seed_n -= cell_free;
        }

        if( ( rand_seed_m > ( this->w - cell_free )) || ( rand_seed_m > ( this->h - cell_free ) ) ) {
            rand_seed_m -= cell_free;
        }

        if( this->is_cell_free( rand_seed_n, rand_seed_m ) ) {
            for( i = rand_seed_n; i < cell_free && !flag; i++ ) {
                for( j = rand_seed_m; j < cell_free && !flag; j++ ) {
                    if( !this->is_cell_free( i, j ) ) {
                        flag = true;
                    }
                }
            }
        }

        if( !flag ) {
            int mid = ceil( (float)cell_free / (float)2 );
            //this->gui->matrix[ rand_seed_n + mid ][ rand_seed_m + mid ] = (Cell) NULL; // TODO: Spawn Player
        }

    } while( flag );
}

void Grid::print_matrix() {
    int i, j;

    for( i = 0; i < this->w; i++ ) {
        for( j = 0; j < this->h; j++ ) {
            cout << this->gui->matrix[ i ][ j ].player << " ";
        }
        cout << endl;
    }
}