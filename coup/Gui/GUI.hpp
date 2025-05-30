/**
 * @file GUI.hpp
 * @author Gal Maymon
 */
#pragma once
#include <SFML/Graphics.hpp>
#include "GameState.hpp"

class MainMenuGUI {
public:
    MainMenuGUI(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, GameState& state);
    void update();
    void render();
	bool isStartClicked() const;

private:
	bool startClicked = false;
    sf::RenderWindow& window;
    sf::Sprite backgroundSprite;
    sf::Texture backgroundTexture;

    sf::FloatRect startButtonBounds;
    sf::FloatRect exitButtonBounds;

    sf::RectangleShape startOverlay;
    sf::RectangleShape exitOverlay;

    sf::Text feedback;
    sf::Font font;

    sf::Cursor arrowCursor;
    sf::Cursor handCursor;

    float scaleX;
    float scaleY;
};
