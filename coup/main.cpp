
/**
 * @file main.cpp
 * @author Gal Maymon
 */
#include <SFML/Graphics.hpp>
#include "Gui/gameScreen.hpp"

int main() {
    const int W = 700, H = 800;
    sf::RenderWindow window(
        sf::VideoMode(W, H),
        "Coup",
        sf::Style::Titlebar | sf::Style::Close
    );

    LogicGame game;
    game.run(window);

    return 0;
}