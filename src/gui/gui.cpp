#include "gui.h"

Gui::Gui(const int w = 500, const int h = 500) {
	this->w = w;
	this->h = h;
	vector<vector<sf::RectangleShape> > matrix(w, vector<sf::RectangleShape>( h ));
	this->matrix = matrix;
	this->window.create(sf::VideoMode(w, h), "Leak");
}

void Gui::create_matrix(int w, int h) {
	int x, y;
	
	for (x = 0; x < this->w/w; x++) {
		for (y = 0; y < this->h/h; y++) {
			this->matrix[x][y].setSize(sf::Vector2f(50, 50));
			this->matrix[x][y].setOutlineColor(sf::Color::Red);
			this->matrix[x][y].setOutlineThickness(2);
			this->matrix[x][y].setPosition(x*50, y*50);
		}
	}
}

void Gui::display_window(int w, int h) { 
	int x, y;
	
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();
		}

        for (x = 0; x < this->w/w; x++) {
			for (y = 0; y < this->h/h; y++) {
				this->window.draw(this->matrix[x][y]);
			}
		}
		this->window.display();
	}
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
	int w, h;
	w = 50;
	h = 50;
	Gui *g = new Gui();
	g->create_matrix(w, h);
	g->display_window(w, h);

	return 0;
}
