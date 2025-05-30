/**
 * @file GovernorCard.hpp
 * @brief Declaration of the GovernorCard class derived from Card.
 *
 * This file defines the GovernorCard class which represents the role card
 * for the Governor role in the Coup-inspired game. It inherits from the Card
 * base class and provides its specific type string.
 *
 * @author Gal Maymon
 */

#pragma once
#include "Card.hpp"

/**
 * @class GovernorCard
 * @brief Represents a Governor role card.
 *
 * Inherits from Card and provides identification as a GovernorCard.
 */
class GovernorCard : public Card {
public:
    /**
     * @brief Constructs a GovernorCard object.
     *
     * Initializes the card with Role::Governor.
     */
    GovernorCard() : Card(Role::Governor) {}

    /**
     * @brief Gets the type of the card.
     * @return A string indicating this is a "GovernorCard".
     */
    std::string getType() const override { return "GovernorCard"; }
};
