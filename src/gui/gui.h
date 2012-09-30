#include <vector>
#include <SFML/Graphics.hpp>

class Gui {	
	public:
		Gui(const int,const int);
		~Gui();

	protected:
		sf::RenderWindow window;
		sf::Font font;
		sf::Text text;
		vector< vector<sf::RectangleShape> > matrix;
};
