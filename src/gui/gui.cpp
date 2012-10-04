#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <sstream>

#include "../core/main.h"
#include "gui.h"

using namespace std;

Gui::Gui(const int width_window = 500, const int height_window = 500, const int width_matrix = 20, const int height_matrix = 20) {
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
    this->matrix[x][y].rect->setFillColor(color);
}

void Gui::display_window() {
    int x, y, w, h;
    int cursor = 0;

    w = this->width_window / this->width_matrix;
    h = this->height_window / this->height_matrix;

    this->window.create(sf::VideoMode(this->width_window, this->height_window), "Leak");
    
    while (window.isOpen()) {
     sf::Event event;
    while (window.pollEvent(event)) {
          if (event.type == sf::Event::Closed)
            window.close();

          if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::F3))
              cursor = !cursor;

		if ((event.type == sf::Event::MouseButtonPressed) && (event.mouseButton.button == sf::Mouse::Left) && cursor) {
			x = (event.mouseButton.x / w);
			y = (event.mouseButton.y / h);

			cout << "X: " << x << " Y: " << y << "\nATK: " << this->matrix[x][y].atk << "\nDEF: " <<  this->matrix[x][y].def << endl;
		}

          if ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::F2)) {
               sf::Image screen = window.capture();
              screen.saveToFile("screenshot.png");
               cout << "Screenshot saved!" << endl;
          }

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
    int w, h, i = 0;
    Grid *g = new Grid(20, 20);
    vector<Player *> p;
    sf::Time time = sf::seconds(0.6f);

    p.push_back(new Player(g, sf::Color::Red, "lol.lua"));
    p.push_back(new Player(g, sf::Color::Black, "example.lua"));

    g->set(18, 18, p[0]);
    g->set(3, 3, p[1]);

    p[1]->atk = 4000;
    p[1]->def = 4000;

    while(1) {
        for (int it = 0; it < p.size(); it++)
          p[it]->turn();

        sf::sleep(time);
    }

    return 0;
}
