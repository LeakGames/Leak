#include <vector>
#include <SFML/Graphics.hpp>

using namespace std;

class Gui {	
	public:
		int width_window, height_window;
		int width_matrix, height_matrix;
		Gui(const int, const int, const int, const int);
		~Gui();
		void create_matrix();
		void display_window();

	protected:
		sf::RenderWindow window;
		sf::Font font;
		sf::Text text;
		vector< vector<sf::RectangleShape> > matrix;
		sf::RectangleShape rectangle;
};
