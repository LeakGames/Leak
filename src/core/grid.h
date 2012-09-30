#include <vector>

using namespace std;

class Grid
{
protected:
    int n, m;

public:
    vector<vector<int> > matrix;

    Grid( const int n, const int m );
    int operator()( const int x, const int y);
    bool is_cell_free( const int x, const int y );
};
