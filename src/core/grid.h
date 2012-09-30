#include <vector>

class Grid {
public:
  Grid();
  ~Grid();
  bool is_cell_free(unsigned int x, unsigned int y);
  void spawn_bonuses();

protected:
  Vector<short int> *vector;
}