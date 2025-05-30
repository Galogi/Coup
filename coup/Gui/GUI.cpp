/**
 * @file GUI.cpp
 * @author Gal Maymon
 */
#include "GUI.hpp"
#include <iostream>


MainMenuGUI::MainMenuGUI(sf::RenderWindow& win)
: window(win)
{
   
    if (!backgroundTexture.loadFromFile("Gui/menu_background.png")) {
        std::cerr << "Failed to load background!\n"; exit(1);
    }
    backgroundSprite.setTexture(backgroundTexture);
    auto ws = window.getSize(), ts = backgroundTexture.getSize();
    scaleX = float(ws.x)/ts.x; scaleY = float(ws.y)/ts.y;
    backgroundSprite.setScale(scaleX, scaleY);


    if (!font.loadFromFile("arial-font/arial.ttf")) {
        std::cerr << "Failed to load font!\n"; exit(1);
    }

 
    arrowCursor.loadFromSystem(sf::Cursor::Arrow);
    handCursor.loadFromSystem(sf::Cursor::Hand);


    startButtonBounds = { 300*scaleX, 835*scaleY, 420*scaleX, 100*scaleY };
    exitButtonBounds  = { 390*scaleX, 990*scaleY, 240*scaleX,  70*scaleY };


    startOverlay.setSize({startButtonBounds.width, startButtonBounds.height});
    startOverlay.setPosition(startButtonBounds.left, startButtonBounds.top);
    startOverlay.setFillColor({0,0,0,80});

    exitOverlay.setSize({exitButtonBounds.width, exitButtonBounds.height});
    exitOverlay.setPosition(exitButtonBounds.left, exitButtonBounds.top);
    exitOverlay.setFillColor({0,0,0,80});

    feedback.setFont(font);
    feedback.setCharacterSize(24);
    feedback.setFillColor(sf::Color::Red);
    feedback.setPosition(50, 1050);
}

void MainMenuGUI::handleEvent(const sf::Event& event, GameState& state) {
    if (event.type == sf::Event::MouseButtonPressed
     && event.mouseButton.button == sf::Mouse::Left)
    {
        auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
        if (startButtonBounds.contains(mousePos)) {
            feedback.setString("Start clicked!");
           
            state = GameState::SelectPlayers;
        }
        else if (exitButtonBounds.contains(mousePos)) {
            window.close();
        }
    }
}

void MainMenuGUI::update() {
    auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    if (startButtonBounds.contains(mousePos) || exitButtonBounds.contains(mousePos))
        window.setMouseCursor(handCursor);
    else
        window.setMouseCursor(arrowCursor);
}

void MainMenuGUI::render() {
    window.draw(backgroundSprite);

    auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
        if (startButtonBounds.contains(mousePos)) window.draw(startOverlay);
        if (exitButtonBounds.contains(mousePos))  window.draw(exitOverlay);
    }

    window.draw(feedback);
}
