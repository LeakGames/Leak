#include <vector>
#include "player.h"

using namespace std;

class Grid
{
public:
    int w, h;
    vector<vector<Cell> > matrix;

    Grid( const int n, const int m );
    Cell operator()( const int x, const int y);
    bool is_cell_free( const int x, const int y );
    void spawn_bonuses();
    void set(int x, int y, Player *p);    
    void spawn_player( const int cell_free );
    void print_matrix();
};
