/**
 * @file JudgeCard.hpp
 * @brief Declaration of the JudgeCard class derived from Card.
 *
 * This file defines the JudgeCard class which represents the role card
 * for the Judge role in the Coup-inspired game. It inherits from the Card
 * base class and provides its specific type string.
 *
 * @author Gal Maymon
 */

#pragma once
#include "Card.hpp"

/**
 * @class JudgeCard
 * @brief Represents a Judge role card.
 *
 * Inherits from Card and provides identification as a JudgeCard.
 */
class JudgeCard : public Card {
public:
    /**
     * @brief Constructs a JudgeCard object.
     *
     * Initializes the card with Role::Judge.
     */
    JudgeCard() : Card(Role::Judge) {}

    /**
     * @brief Gets the type of the card.
     * @return A string indicating this is a "JudgeCard".
     */
    std::string getType() const override { return "JudgeCard"; }
};
