/**
 * @file gameScreen.hpp
 * @author Gal Maymon
 */

#pragma once

#include <SFML/Graphics.hpp>
#include "GUI.hpp"
#include "SelectPlayersGUI.hpp"
#include "GameScreenGUI.hpp"
#include "GameState.hpp"
#include "../Players/Player.hpp"
#include "../cards/Card.hpp"
#include "../Logic/GameLogic.hpp"
#include "../Players/PlayerFactory.hpp"
#include <vector>
#include <random>
#include <memory>


class LogicGame {
public:
    
    void run(sf::RenderWindow& window);
};
