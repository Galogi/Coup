/**
 * @file JudgePlayer.hpp
 * @brief Declares the JudgePlayer class, representing the Judge role in the game.
 *
 * The JudgePlayer can block bribery attempts, penalizing themselves with 4 coins
 * while disabling the bribe ability of the target player. Inherits from Player
 * and overrides behavior specific to the Judge role.
 *
 * @author Gal Maymon
 */

#pragma once
#include "Player.hpp"
#include "../cards/JudgeCard.hpp"

class JudgePlayer : public Player {
private:
    JudgeCard card;

public:
    JudgePlayer(const std::string& name)
        : Player(name), card() {}

    Role getRole() const override {
        return Role::Judge;
    }

    const Card& getCard() const override {
        return card;
    }

    
    void blockBribe(Player& target)  {
       
        changeCoins(-4);
        target.blockBribeForTurns();
    }

    

};
