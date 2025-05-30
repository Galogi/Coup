/**
 * @file GeneralCard.hpp
 * @brief Declaration of the GeneralCard class derived from Card.
 *
 * This file defines the GeneralCard class which represents the role card
 * for the General role in the Coup-inspired game. It inherits from the Card
 * base class and provides its specific type string.
 *
 * @author Gal Maymon
 */

#pragma once
#include "Card.hpp"

/**
 * @class GeneralCard
 * @brief Represents a General role card.
 *
 * Inherits from Card and provides identification as a GeneralCard.
 */
class GeneralCard : public Card {
public:
    /**
     * @brief Constructs a GeneralCard object.
     *
     * Initializes the card with Role::General.
     */
    GeneralCard() : Card(Role::General) {}

    /**
     * @brief Gets the type of the card.
     * @return A string indicating this is a "GeneralCard".
     */
    std::string getType() const override { return "GeneralCard"; }
};
