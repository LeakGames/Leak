#include <vector>

using namespace std;

class Grid
{
protected:
    int n, m;

public:
    vector<vector<int> > matrix;

    Grid( const int n, const int m ) {
      vector<vector<int> > matrix( n, vector<int>( m ) );

      this->n = n;
      this->m = m;
      this->matrix = matrix;
    }

    int operator()(int x, int y) {
        return this->matrix[x][y];
    }
    
    ~Grid();
    bool is_cell_free(unsigned int x, unsigned int y);
    void spawn_bonuses();
};