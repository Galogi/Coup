/**
 * @file GUI.cpp
 * @author Gal Maymon
 */
#include "GUI.hpp"
#include <iostream>


MainMenuGUI::MainMenuGUI(sf::RenderWindow& win)
: window(win),
  backgroundSprite(backgroundTexture),
  feedback(font)
{
   
    if (!backgroundTexture.loadFromFile("Gui/menu_background.png")) {
        std::cerr << "Failed to load background!\n"; exit(1);
    }
    backgroundSprite.setTexture(backgroundTexture, true);
    auto ws = window.getSize(), ts = backgroundTexture.getSize();
    scaleX = float(ws.x)/ts.x; scaleY = float(ws.y)/ts.y;
    backgroundSprite.setScale({scaleX, scaleY});


    if (!font.openFromFile("arial-font/arial.ttf")) {
        std::cerr << "Failed to load font!\n"; exit(1);
    }

 
    arrowCursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Arrow);
    handCursor = sf::Cursor::createFromSystem(sf::Cursor::Type::Hand);


    startButtonBounds = sf::FloatRect({300*scaleX, 835*scaleY}, {420*scaleX, 100*scaleY});
    exitButtonBounds  = sf::FloatRect({390*scaleX, 990*scaleY}, {240*scaleX,  70*scaleY});


    startOverlay.setSize(startButtonBounds.size);
    startOverlay.setPosition(startButtonBounds.position);
    startOverlay.setFillColor({0,0,0,80});

    exitOverlay.setSize(exitButtonBounds.size);
    exitOverlay.setPosition(exitButtonBounds.position);
    exitOverlay.setFillColor({0,0,0,80});

    feedback.setCharacterSize(24);
    feedback.setFillColor(sf::Color::Red);
    feedback.setPosition({50.f, 1050.f});
}

void MainMenuGUI::handleEvent(const sf::Event& event, GameState& state) {
    if (const auto* mouseButton = event.getIf<sf::Event::MouseButtonPressed>();
        mouseButton && mouseButton->button == sf::Mouse::Button::Left)
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
    if (startButtonBounds.contains(mousePos) || exitButtonBounds.contains(mousePos)) {
        if (handCursor) window.setMouseCursor(*handCursor);
    } else {
        if (arrowCursor) window.setMouseCursor(*arrowCursor);
    }
}

void MainMenuGUI::render() {
    window.draw(backgroundSprite);

    auto mousePos = window.mapPixelToCoords(sf::Mouse::getPosition(window));
    if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
        if (startButtonBounds.contains(mousePos)) window.draw(startOverlay);
        if (exitButtonBounds.contains(mousePos))  window.draw(exitOverlay);
    }

    window.draw(feedback);
}
