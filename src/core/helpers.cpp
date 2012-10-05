#include <vector>
#include <string>
#include <SFML/Graphics.hpp>

using namespace std;

#include "main.h"

sf::Color colors[] = {
    sf::Color::Black,
    sf::Color::White,
    sf::Color::Red,
    sf::Color::Green,
    sf::Color::Blue,
    sf::Color::Yellow,
    sf::Color::Magenta,
    sf::Color::Cyan
};

string names[] = {
    "black",
    "white",
    "red",
    "green",
    "blue",
    "yellow",
    "magenta",
    "cyan"
};

string *color_to_string(sf::Color color) {
    for (int n = 0; n < 8; n++)
        if (colors[n] == color) return &(names[n]);
}