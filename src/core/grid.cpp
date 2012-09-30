#include <vector>
#include "grid.h"

using namespace std;

Grid::Grid( const int n, const int m ) {
  vector<vector<int> > matrix( n, vector<int>( m ) );

  this->n = n;
  this->m = m;
  this->matrix = matrix;
}

int Grid::operator()(int x, int y) {
    return this->matrix[x][y];
}

int main() {}
