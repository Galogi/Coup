/**
 * @file SelectPlayersGUI.cpp
 * @author Gal Maymon
 */
#include "SelectPlayersGUI.hpp"
#include <iostream>

SelectPlayersGUI::SelectPlayersGUI(sf::RenderWindow& win)
: window(win)
{

    arrowCursor.loadFromSystem(sf::Cursor::Arrow);
    handCursor.loadFromSystem(sf::Cursor::Hand);


    if (!font.loadFromFile("arial-font/arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        exit(1);
    }

  
    if (!backgroundTexture.loadFromFile("Gui/select_players_background.png")) {
        std::cerr << "Failed to load background!" << std::endl;
        exit(1);
    }
    backgroundSprite.setTexture(backgroundTexture);

   
    auto windowSize  = window.getSize();
    auto textureSize = backgroundTexture.getSize();
    scaleX = float(windowSize.x) / textureSize.x;
    scaleY = float(windowSize.y) / textureSize.y;
    backgroundSprite.setScale(scaleX, scaleY);


    title.setFont(font);
    title.setString("Select Number of Players");
    title.setCharacterSize(36);
    title.setFillColor(sf::Color::White);
    {
        auto tb = title.getLocalBounds();
        title.setPosition((windowSize.x - tb.width) * 0.5f - tb.left, 50);
    }

  
    const int   count     = 5;    
    const float btnW      = 80.f, btnH = 80.f;
    const float marginX   = 50.f;
    const float marginBot = 60.f;
    float totalW = count * btnW;
    float availW = windowSize.x - 2*marginX - totalW;
    float spacing = (count > 1 ? availW/(count-1) : 0);
    float btnY = windowSize.y - marginBot - btnH;

    for (int i = 0; i < count; ++i) {
        int players = 2 + i;
        sf::RectangleShape button;
        button.setSize({btnW, btnH});
        button.setFillColor(DARK_BUTTON);
        button.setOutlineColor(GOLD_COLOR);
        button.setOutlineThickness(3);
        float x = marginX + i*(btnW + spacing);
        button.setPosition(x, btnY);
        playerButtons.push_back(button);

        sf::Text text;
        text.setFont(font);
        text.setString(std::to_string(players));
        text.setCharacterSize(32);
        text.setFillColor(GOLD_COLOR);
        auto bb = button.getGlobalBounds();
        auto lb = text.getLocalBounds();
        text.setPosition(
            bb.left + (bb.width  - lb.width)  * 0.5f - lb.left,
            bb.top  + (bb.height - lb.height) * 0.5f - lb.top
        );
        playerTexts.push_back(text);
    }

   
    continueButton.setSize({200.f, 60.f});
    continueButton.setFillColor(DARK_BUTTON);
    continueButton.setOutlineColor(GOLD_COLOR);
    continueButton.setOutlineThickness(3);
    continueButton.setPosition((windowSize.x - 200.f)*0.5f, btnY - 40.f - 60.f);
    continueText.setFont(font);
    continueText.setString("Continue");
    continueText.setCharacterSize(28);
    continueText.setFillColor(GOLD_COLOR);
    {
        auto cb = continueButton.getGlobalBounds();
        auto lb = continueText.getLocalBounds();
        continueText.setPosition(
            cb.left + (cb.width  - lb.width)  * 0.5f - lb.left,
            cb.top  + (cb.height - lb.height) * 0.5f - lb.top
        );
    }

   
    backButton.setSize({100.f, 40.f});
    backButton.setFillColor(DARK_BUTTON);
    backButton.setOutlineColor(GOLD_COLOR);
    backButton.setOutlineThickness(2);
    backButton.setPosition(20.f, 20.f);
    backText.setFont(font);
    backText.setString("Back");
    backText.setCharacterSize(20);
    backText.setFillColor(GOLD_COLOR);
    {
        auto bb2 = backButton.getGlobalBounds();
        auto lb2 = backText.getLocalBounds();
        backText.setPosition(
            bb2.left + (bb2.width  - lb2.width)  * 0.5f - lb2.left,
            bb2.top  + (bb2.height - lb2.height) * 0.5f - lb2.top
        );
    }
}

void SelectPlayersGUI::handleEvent(const sf::Event& event, GameState& state) {
    if (event.type == sf::Event::MouseButtonPressed && event.mouseButton.button == sf::Mouse::Left) {
        auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
   
        for (size_t i = 0; i < playerButtons.size(); ++i) {
            if (playerButtons[i].getGlobalBounds().contains(mousePos)) {
                selectedPlayers = int(i) + 2;
            }
        }
      
        if (continueButton.getGlobalBounds().contains(mousePos) && selectedPlayers > 0) {
            state = GameState::InGame; 
        }
        
        if (backButton.getGlobalBounds().contains(mousePos)) {
            state = GameState::MainMenu;
        }
    }
}

void SelectPlayersGUI::update() {
   
    sf::Vector2f mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    bool over = false;
    for (auto& btn : playerButtons) {
        if (btn.getGlobalBounds().contains(mousePos)) { over = true; break; }
    }
    if (!over && continueButton.getGlobalBounds().contains(mousePos)) over = true;
    if (!over && backButton.getGlobalBounds().contains(mousePos)) over = true;
    window.setMouseCursor(over ? handCursor : arrowCursor);
}

void SelectPlayersGUI::render() {
    window.draw(backgroundSprite);
    window.draw(title);
    for (size_t i = 0; i < playerButtons.size(); ++i) {
        bool sel = (int(i) + 2 == selectedPlayers);
        playerButtons[i].setFillColor(sel ? GOLD_COLOR : DARK_BUTTON);
        playerButtons[i].setOutlineColor(sel ? sf::Color::White : GOLD_COLOR);
        window.draw(playerButtons[i]);
        window.draw(playerTexts[i]);
    }
    window.draw(continueButton);
    window.draw(continueText);
    window.draw(backButton);
    window.draw(backText);
}

