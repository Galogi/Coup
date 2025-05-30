/**
 * @file SpyCard.hpp
 * @brief Declaration of the SpyCard class derived from Card.
 *
 * This file defines the SpyCard class which represents the role card
 * for the Spy role in the Coup-inspired game. It inherits from the Card
 * base class and provides its specific type string.
 *
 * @author Gal Maymon
 */

#pragma once
#include "Card.hpp"

/**
 * @class SpyCard
 * @brief Represents a Spy role card.
 *
 * Inherits from Card and provides identification as a SpyCard.
 */
class SpyCard : public Card {
public:
    /**
     * @brief Constructs a SpyCard object.
     *
     * Initializes the card with Role::Spy.
     */
    SpyCard() : Card(Role::Spy) {}

    /**
     * @brief Gets the type of the card.
     * @return A string indicating this is a "SpyCard".
     */
    std::string getType() const override { return "SpyCard"; }
};