/**
 * @file GovernorPlayer.hpp
 * @brief Declares the GovernorPlayer class, representing the Governor role in the game.
 *
 * The GovernorPlayer class allows the player to collect tax (3 coins) each turn,
 * and block other players from taxing. The class extends Player and overrides
 * relevant role-based behavior.
 *
 * @author Gal Maymon
 */

#pragma once
#include "Player.hpp"
#include "../cards/GovernorCard.hpp"

class GovernorPlayer : public Player {
private:
    GovernorCard card;

public:
    GovernorPlayer(const std::string& name)
        : Player(name), card() {}

    Role getRole() const override {
        return Role::Governor;
    }

    const Card& getCard() const override {
        return card;
    }

    void tax() override {
        if (taxBlockTurns > 0) {
            std::cout << "[Governor] Tax blocked.\n";
            taxBlockTurns = 0;
            return;
        }
        changeCoins(3); 
        std::cout << "[Governor] Collected 3 coins via tax.\n";
    }
	void blockTax(Player& target) {
    
    target.blockTaxForTurns(); 
    
 }
};
