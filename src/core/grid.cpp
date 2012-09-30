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

bool Grid::is_cell_free( const int x, const int y ) {
    return !( ( bool ) this->matrix[x][y] );
}

void Grid::spawn_bonuses() {
    srand(time(0));

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

int main() {}