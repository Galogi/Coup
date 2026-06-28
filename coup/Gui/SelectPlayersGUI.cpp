/**
 * @file SelectPlayersGUI.cpp
 * @author Gal Maymon
 */
#include "SelectPlayersGUI.hpp"
#include <iostream>

SelectPlayersGUI::SelectPlayersGUI(sf::RenderWindow& win)
: window(win),
  backgroundSprite(backgroundTexture),
  title(font),
  continueText(font),
  backText(font)
{

    arrowCursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Arrow);
    handCursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Hand);


    if (!font.openFromFile("arial-font/arial.ttf")) {
        std::cerr << "Failed to load font!" << std::endl;
        exit(1);
    }

  
    if (!backgroundTexture.loadFromFile("Gui/select_players_background.png")) {
        std::cerr << "Failed to load background!" << std::endl;
        exit(1);
    }
    backgroundSprite.setTexture(backgroundTexture, true);
    auto windowSize  = window.getSize();
    auto textureSize = backgroundTexture.getSize();
    scaleX = float(windowSize.x) / textureSize.x;
    scaleY = float(windowSize.y) / textureSize.y;
    backgroundSprite.setScale({scaleX, scaleY});


    title.setString("Select Number of Players");
    title.setCharacterSize(36);
    title.setFillColor(sf::Color::White);
    {
        auto tb = title.getLocalBounds();
        title.setPosition({(windowSize.x - tb.size.x) * 0.5f - tb.position.x, 50.f});
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
        button.setPosition({x, btnY});
        playerButtons.push_back(button);

        sf::Text text(font);
        text.setString(std::to_string(players));
        text.setCharacterSize(32);
        text.setFillColor(GOLD_COLOR);
        auto bb = button.getGlobalBounds();
        auto lb = text.getLocalBounds();
        text.setPosition(
            {bb.position.x + (bb.size.x  - lb.size.x)  * 0.5f - lb.position.x,
             bb.position.y + (bb.size.y - lb.size.y) * 0.5f - lb.position.y}
        );
        playerTexts.push_back(text);
    }

   
    continueButton.setSize({200.f, 60.f});
    continueButton.setFillColor(DARK_BUTTON);
    continueButton.setOutlineColor(GOLD_COLOR);
    continueButton.setOutlineThickness(3);
    continueButton.setPosition({(windowSize.x - 200.f)*0.5f, btnY - 40.f - 60.f});
    continueText.setString("Continue");
    continueText.setCharacterSize(28);
    continueText.setFillColor(GOLD_COLOR);
    {
        auto cb = continueButton.getGlobalBounds();
        auto lb = continueText.getLocalBounds();
        continueText.setPosition(
            {cb.position.x + (cb.size.x  - lb.size.x)  * 0.5f - lb.position.x,
             cb.position.y + (cb.size.y - lb.size.y) * 0.5f - lb.position.y}
        );
    }

   
    backButton.setSize({100.f, 40.f});
    backButton.setFillColor(DARK_BUTTON);
    backButton.setOutlineColor(GOLD_COLOR);
    backButton.setOutlineThickness(2);
    backButton.setPosition({20.f, 20.f});
    backText.setString("Back");
    backText.setCharacterSize(20);
    backText.setFillColor(GOLD_COLOR);
    {
        auto bb2 = backButton.getGlobalBounds();
        auto lb2 = backText.getLocalBounds();
        backText.setPosition(
            {bb2.position.x + (bb2.size.x  - lb2.size.x)  * 0.5f - lb2.position.x,
             bb2.position.y + (bb2.size.y - lb2.size.y) * 0.5f - lb2.position.y}
        );
    }
}

void SelectPlayersGUI::handleEvent(const sf::Event& event, GameState& state) {
    if (const auto* mouseButton = event.getIf<sf::Event::MouseButtonPressed>();
        mouseButton && mouseButton->button == sf::Mouse::Button::Left) {
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
    if (over) {
        if (handCursor) window.setMouseCursor(*handCursor);
    } else {
        if (arrowCursor) window.setMouseCursor(*arrowCursor);
    }
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

