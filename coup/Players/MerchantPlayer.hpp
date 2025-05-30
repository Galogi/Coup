/**
 * @file MerchantPlayer.hpp
 * @brief Declares the MerchantPlayer class representing the Merchant role in the game.
 *
 * This class defines the Merchant role. Merchant players may receive a coin
 * bonus automatically at the start of their turn if they have more than 3 coins.
 * The logic for the bonus is handled in the GameLogic class.
 *
 * Inherits from Player and provides the specific role and card.
 *
 * @author Gal Maymon
 */

#pragma once
#include "Player.hpp"
#include "../cards/MerchantCard.hpp"

class MerchantPlayer : public Player {
private:
    MerchantCard card;

public:
    MerchantPlayer(const std::string& name)
        : Player(name), card() {}

    Role getRole() const override {
        return Role::Merchant;
    }

    const Card& getCard() const override {
        return card;
    }

   
};
