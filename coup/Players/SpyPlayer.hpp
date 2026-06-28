/**
 * @file SpyPlayer.hpp
 * @brief Defines the SpyPlayer class, representing the Spy role in the game.
 *
 * SpyPlayer extends the base Player class and provides special behavior
 * unique to the Spy role, including the ability to peek at a player's coins
 * and block their next arrest attempt. It uses a SpyCard to represent its identity.
 *
 * @author Gal Maymon
 */

#pragma once
#include "Player.hpp"
#include "../cards/SpyCard.hpp"

class SpyPlayer : public Player {
private:
    SpyCard card;

public:
    SpyPlayer(const std::string& name)
        : Player(name), card() {}

    Role getRole() const override {
        return Role::Spy;
    }

    const Card& getCard() const override {
        return card;
    }

    
    void peekAndBlock(Player& target) {
        if (target.isEliminated()) {
            return;
        }

        target.blockArrestForTurns(); 
    }
};
