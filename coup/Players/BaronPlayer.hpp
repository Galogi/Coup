/**
 * @file BaronPlayer.hpp
 * @brief Defines the BaronPlayer class, representing the Baron role in the game.
 *
 * The BaronPlayer class implements the special behavior of a player with the Baron role.
 * The Baron can invest 3 coins to gain 6, and receives a coin as compensation when sanctioned.
 *
 * @author Gal Maymon
 */

#pragma once
#include "Player.hpp"
#include "../cards/BaronCard.hpp"

class BaronPlayer : public Player {
private:
    BaronCard card;

public:
    BaronPlayer(const std::string& name)
        : Player(name), card() {}

    Role getRole() const override {
        return Role::Baron;
    }

    const Card& getCard() const override {
        return card;
    }

    void Invest()  {
        if (coins < 3) {
            throw std::runtime_error("Not enough coins to invest (bribe)");
        }
        std::cout << "[Baron] Invested 3 coins and gained 6.\n";
        changeCoins(-3);
        changeCoins(6);
    }

    

    void blocksanctionForTurns() override {
	changeCoins(1);
	blockTaxForTurns(),blockGatherForTurns(); 
       
    }
};
