#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

class Gui {	
	public:
		int w, h;
		Gui(const int, const int);
		~Gui();
		void create_matrix(int, int);
		void display_window(int, int);

	protected:
		sf::RenderWindow window;
		sf::Font font;
		sf::Text text;
		vector< vector<sf::RectangleShape> > matrix;
		sf::RectangleShape rectangle;
};
