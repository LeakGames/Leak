#include "gui.h"

Gui::Gui(const int width_window = 500, const int height_window = 500, const int width_matrix = 100, const int height_matrix = 100) {
	vector<vector<Cell> > matrix(width_matrix, vector<Cell>( height_matrix ));
	this->width_window = width_window;
	this->height_window = height_window;
	this->width_matrix = width_matrix;
	this->height_matrix = height_matrix;
	//this->matrix = new vector<vector<Cell> >(width_matrix, vector<Cell>( height_matrix ));
	this->matrix = matrix;
}

void Gui::create_matrix() {
	int x, y;
	float w = (float)this->width_window/(float)this->width_matrix;
	float h = (float)this->height_window/(float)this->height_matrix;

	for (x = 0; x < this->width_matrix; x++) {
		for (y = 0; y < this->height_matrix; y++) {
			this->matrix[x][y].rect = new sf::RectangleShape(sf::Vector2f(w,h));
			this->matrix[x][y].rect->setOutlineColor(sf::Color::Red);
			this->matrix[x][y].rect->setOutlineThickness(1);
			this->matrix[x][y].rect->setPosition(x*w, y*h);
		}
	}
}

void Gui::set_color(int x, int y, sf::Color color) {
	return this->matrix[x][y].rect->setFillColor(color);
}

void Gui::display_window() { 
	int x, y;

	this->window.create(sf::VideoMode(this->width_window, this->height_window), "Leak");
	
	while (window.isOpen()) {
		sf::Event event;
		while (window.pollEvent(event)) {
			if (event.type == sf::Event::Closed)
				window.close();

			 if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::F3))
				 this->set_color(3,3, sf::Color::Blue);
		}

     	for (x = 0; x < this->width_matrix; x++) {
			for (y = 0; y < this->height_matrix; y++) {
				this->window.draw(*this->matrix[x][y].rect);
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
	Gui *g = new Gui();
	g->create_matrix();
	g->display_window();

	return 0;
}
