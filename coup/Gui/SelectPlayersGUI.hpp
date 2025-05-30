
/**
 * @file SelectPlayersGUI.hpp
 * @author Gal Maymon
 */
#pragma once
#include <SFML/Graphics.hpp>
#include <vector>
#include "GameState.hpp"

class SelectPlayersGUI {
public:
    SelectPlayersGUI(sf::RenderWindow& window);
    void handleEvent(const sf::Event& event, GameState& state);
    void update();
    void render();
int getSelectedPlayerCount() const {
    return selectedPlayers;
}
void resetSelection() { selectedPlayers = 0; }

private:
    sf::RenderWindow& window;
    sf::Texture        backgroundTexture;
    sf::Sprite         backgroundSprite;
    sf::Font           font;
    sf::Text           title;

    std::vector<sf::RectangleShape> playerButtons;
    std::vector<sf::Text>           playerTexts;
    int                              selectedPlayers = 0;

    sf::RectangleShape continueButton;
    sf::Text           continueText;

    sf::RectangleShape backButton;
    sf::Text           backText;

    float scaleX = 1.f, scaleY = 1.f;
    sf::Cursor arrowCursor;
    sf::Cursor handCursor;

  
    inline static const sf::Color GOLD_COLOR   = sf::Color(212, 175,  55);
    inline static const sf::Color DARK_BUTTON  = sf::Color( 40,  40,  40);
};