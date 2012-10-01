#include <vector>
#include <cstdlib>
#include <ctime>

#include "player.h"
#include "main.h"

using namespace std;

Grid::Grid( const int w, const int h ) {
  this->w = w;
  this->h = h;
  this->matrix = new vector< vector<Cell> >(n, vector<Cell>(m));

  for( int i = 1; i <= 6; i++ )
      this->gift.push_back( i * -1 );
}

int Grid::operator()(int x, int y) {
    return this->matrix[x][y];
}

void Grid::set(int x, int y, Player *p) {
    // call GUI methods

    this->matrix[x][y]->p = player;
}

bool Grid::is_cell_free( const int x, const int y ) {
    return ( bool ) ( !this->matrix[x][y]->p );
}

/*
void Grid::spawn_bonuses() {
    int rand_n, rand_m, rand_gift;

    do {
        rand_n = rand() % this->n;
        rand_m = rand() % this->m;
        rand_gift = rand() % 6;

        if( this->is_cell_free( rand_n, rand_m ) ) {
            this->matrix[ rand_n ][ rand_m ] = this->gift.at( rand_gift );
        }

    } while( this->is_cell_free( rand_n, rand_m ) );
}
*/

void Grid::spawn_player( const int cell_free ) {
    int i, j, rand_seed_n, rand_seed_m;
    bool flag;
    
    do {
        flag = false;
        rand_seed_n = rand() % this->n;
        rand_seed_m = rand() % this->n;

        if( ( rand_seed_n > ( this->n - cell_free )) || ( rand_seed_n > ( this->m - cell_free ) ) ) {
            rand_seed_n -= cell_free;
        }

        if( ( rand_seed_m > ( this->n - cell_free )) || ( rand_seed_m > ( this->m - cell_free ) ) ) {
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
            this->matrix[ rand_seed_n + mid ][ rand_seed_m + mid ] = NULL; // TODO: Spawn Player
        }

    } while( flag );
}

void Grid::print_matrix() {
    int i, j;

    for( i = 0; i < this->n; i++ ) {
        for( j = 0; j < this->m; j++ ) {
            cout << this->matrix[ i ][ j ]->P << " ";
        }
        cout << endl;
    }
}
