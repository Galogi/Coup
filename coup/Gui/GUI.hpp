/**
 * @file GUI.hpp
 * @author Gal Maymon
 */
#pragma once
#include <SFML/Graphics.hpp>
#include <optional>
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
    sf::Texture backgroundTexture;
    sf::Sprite backgroundSprite;

    sf::FloatRect startButtonBounds;
    sf::FloatRect exitButtonBounds;

    sf::RectangleShape startOverlay;
    sf::RectangleShape exitOverlay;

    sf::Font font;
    sf::Text feedback;

    std::optional<sf::Cursor> arrowCursor;
    std::optional<sf::Cursor> handCursor;

    float scaleX;
    float scaleY;
};
