/**
 * @file GeneralPlayer.hpp
 * @brief Defines the GeneralPlayer class, representing the General role in the game.
 *
 * The GeneralPlayer class allows a player to block a Coup against an ally
 * by spending 5 coins. This role is defensive and strategic, offering protection
 * to other players in exchange for resources.
 *
 * @author Gal Maymon
 */


#pragma once
#include "Player.hpp"
#include "../cards/GeneralCard.hpp"

class GeneralPlayer : public Player {
private:
    GeneralCard card;

public:
    GeneralPlayer(const std::string& name)
        : Player(name), card() {}

    Role getRole() const override {
        return Role::General;
    }

    const Card& getCard() const override {
        return card;
    }
	
	

	void BlockCoup(Player& target) {
		if (coins < 5) {
			throw std::runtime_error("Not enough coins to perform Coup block for ally");
		}

		std::cout << "[General] Blocking coup for ally: " << target.getName() << "\n";
		changeCoins(-5); 
		target.addCoupBlockFromAlly(); 
	}
};
