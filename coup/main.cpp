
/**
 * @file main.cpp
 * @author Gal Maymon
 */
#include <SFML/Graphics.hpp>
#include "Gui/gameScreen.hpp"

int main() {
    const int W = 700, H = 800;
    sf::RenderWindow window(
        sf::VideoMode(sf::Vector2u(W, H)),
        "Coup",
        sf::Style::Titlebar | sf::Style::Close
    );
    window.setFramerateLimit(60);

    LogicGame game;
    game.run(window);

    return 0;
}
