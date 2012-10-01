#include "gui.h"

using namespace std;

Gui::Gui(const int w = 100, const int h = 100) {
	vector<vector<sf::RectangleShape> > matrix( w, vector<sf::RectangleShape>( h ));

	this->window.create(sf::VideoMode(w, h), "Leak");
	this->matrix = matrix;
}

int main() {
/*	sf::RenderWindow window;

	window.create(sf::VideoMode(200,200), "SFML");
	sf::Font font;
	sf::Text text("Grid");
	sf::RectangleShape rectangle;

	rectangle.setSize(sf::Vector2f(10, 10));
	rectangle.setFillColor(sf::Color::Blue);
	rectangle.setOutlineColor(sf::Color::Red);
	rectangle.setOutlineThickness(2);
	rectangle.setPosition(30, 10);
	
	font.loadFromFile("/usr/share/fonts/TTF/arial.ttf");
 	
	text.setFont(font);
	text.setCharacterSize(10);
	text.setStyle(sf::Text::Bold);
	text.setColor(sf::Color::Red);

	while (window.isOpen())
	{
     	sf::Event event;
     	while (window.pollEvent(event))
     	{
          	if (event.type == sf::Event::Closed)
               	window.close();
     	}

		window.clear();
		window.draw(rectangle);
		window.draw(text);
     	window.display();
	}*/

	Gui *g = new Gui();

	return 0;
}
