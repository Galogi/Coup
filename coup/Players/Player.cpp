/**
 * @file Player.cpp
 * @brief Implementation of the base Player class for the Coup-inspired card game.
 *
 * This file implements the common logic for all players, including actions like
 * gather, tax, bribe, arrest, sanction, and coup. It also includes logic for
 * blocking specific actions and handling coin updates and elimination.
 *
 * Specialized player behavior is implemented in subclasses such as SpyPlayer, 
 * BaronPlayer, etc.
 *
 * @author Gal Maymon
 */

#include "Player.hpp"

Player::Player(const std::string& name) : name(name) {}

const std::string& Player::getName() const {
    return name;
}

Role Player::getRole() const {
    throw std::logic_error("getRole() not implemented in base Player");
}

const Card& Player::getCard() const {
    throw std::logic_error("getCard() not implemented in base Player");
}

void Player::changeCoins(int delta) {
    if (coins + delta < 0) {
        throw std::runtime_error("Not enough coins");
    }
    coins += delta;
}

void Player::gather() {
    changeCoins(1);
}

void Player::tax() {
    if (taxBlockTurns > 0) {
        std::cout << "[INFO] Blocked from performing tax for this turn.\n";
        taxBlockTurns = 0;
        return;
    }
    changeCoins(2);
}

void Player::bribe() {
    changeCoins(-4);
}

void Player::arrest(Player& target) {
    if (arrestBlockTurns > 0) {
        std::cout << "[INFO] Arrest blocked due to previous Spy action.\n";
        arrestBlockTurns = 0;
        return;
    }

    if (target.getRole() == Role::General) {
        std::cout << "[INFO] Cannot arrest a General!\n";
        return;
    }

     if (target.getRole() == Role::Merchant) {
        std::cout << "[INFO] Lost 2 coins to bank!\n";
        target.changeCoins(-2);
        return;
    }

    

    target.changeCoins(-1);
    changeCoins(1);
}


void Player::sanction(Player& target) {
    if (coins < 3) {
        throw std::runtime_error("Not enough coins to perform sanction");
    }

    target.blockTaxForTurns();
    target.blockGatherForTurns();

    
    if (target.getRole() == Role::Judge) {
        changeCoins(-1);
       
    }
    if (target.getRole() == Role::Baron) {
        target.changeCoins(1);
       
    }

    changeCoins(-3);
}


void Player::coup(Player& target) {
    if (coins < 7) {
        throw std::runtime_error("Not enough coins to perform coup");
    }

    if (target.coupBlockTurns > 0) {
        std::cout << "[INFO] Coup blocked! Target loses block, attacker pays 1 coin.\n";
        target.coupBlockTurns -= 1;
        changeCoins(-7);
        return;
    }

    std::cout << "[INFO] " << target.getName() << " has been eliminated by coup.\n";
    changeCoins(-7);
    target.eliminate();
}





