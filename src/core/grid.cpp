#include <vector>
#include <iostream>
#include <cstdlib>
#include <ctime>
#include <cmath>

#include "main.h"

using namespace std;

Grid::Grid( const int w, const int h ) {
    vector< vector<Cell> > matrix(w, vector<Cell>(h));

    this->w = w;
    this->h = h;
    this->matrix = matrix;
    this->gui = new Gui();
}

Cell Grid::operator()(int x, int y) {
    return this->matrix[x][y];
}

bool Grid::set(int x, int y, Player *p) {
    // call GUI methods

    this->matrix[x][y].player = p;
    return true;
}

bool Grid::is_cell_free( const int x, const int y ) {
    return ( bool ) ( !this->matrix[x][y].player );
}

void Grid::spawn_player( const int cell_free ) {
    int i, j, rand_seed_n, rand_seed_m;
    bool flag;
    
    do {
        flag = false;
        rand_seed_n = rand() % this->w;
        rand_seed_m = rand() % this->w;

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
            //this->matrix[ rand_seed_n + mid ][ rand_seed_m + mid ] = (Cell) NULL; // TODO: Spawn Player
        }

    } while( flag );
}

void Grid::print_matrix() {
    int i, j;

    for( i = 0; i < this->w; i++ ) {
        for( j = 0; j < this->h; j++ ) {
            cout << this->matrix[ i ][ j ].player << " ";
        }
        cout << endl;
    }
}

int main() {}