#include <vector>
#include <cstdlib>
#include <ctime>

#include "main.h"

using namespace std;

Grid::Grid( const int n, const int m ) {
  vector<vector<int> > matrix( n, vector<int>( m ) );

  this->n = n;
  this->m = m;
  this->matrix = matrix;

  for( int i = 1; i <= 6; i++ )
      this->gift.push_back( i * -1 );
}

int Grid::operator()(int x, int y) {
    return this->matrix[x][y];
}

void Grid::set(int x, int y, int n) {
    // call GUI methods

    this->matrix[x][y] = n;
}

bool Grid::is_cell_free( const int x, const int y ) {
    return ( bool ) ( !this->matrix[x][y] );
}

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

void Grid::spawn_player( const int cell_free ) {
    int i, j, flag, rand_seed_n, rand_seed_m;

    do {
        flag = 0;
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
                        flag = 1;
                    }
                }
            }
        }

        if( !flag ) {
            int mid = ceil( (float)cell_free / (float)2 );
            this->matrix[ rand_seed_n + mid ][ rand_seed_m + mid ] = 1; // Spawn Player
        }

    } while( flag );
}

void Grid::print_matrix() {
    int i, j;

    for( i = 0; i < this->n; i++ ) {
        for( j = 0; j < this->m; j++ ) {
            cout << this->matrix[ i ][ j ] << " ";
        }
        cout << endl;
    }
}
