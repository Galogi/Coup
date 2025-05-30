/**
 * @file BaronCard.hpp
 * @brief Declaration of the BaronCard class, which represents the Baron role's card in the game.
 * 
 * The BaronCard class inherits from the base Card class and sets its role to Role::Baron.
 * It provides the role identifier and allows the game logic and GUI to recognize the card as a Baron card.
 * 
 * @author Gal Maymon
 */

#pragma once
#include "Card.hpp"

/**
 * @class BaronCard
 * @brief Represents the card for the Baron role in the game.
 */
class BaronCard : public Card {
public:
    /**
     * @brief Constructor that initializes the card with Role::Baron.
     */
    BaronCard() : Card(Role::Baron) {}

    /**
     * @brief Returns the type of the card as a string.
     * @return A string representing the card type: "BaronCard".
     */
    std::string getType() const override { return "BaronCard"; }
};
