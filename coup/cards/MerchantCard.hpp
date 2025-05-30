/**
 * @file MerchantCard.hpp
 * @brief Declaration of the MerchantCard class derived from Card.
 *
 * This file defines the MerchantCard class which represents the role card
 * for the Merchant role in the Coup-inspired game. It inherits from the Card
 * base class and provides its specific type string.
 *
 * @author Gal Maymon
 */

#pragma once
#include "Card.hpp"

/**
 * @class MerchantCard
 * @brief Represents a Merchant role card.
 *
 * Inherits from Card and provides identification as a MerchantCard.
 */
class MerchantCard : public Card {
public:
    /**
     * @brief Constructs a MerchantCard object.
     *
     * Initializes the card with Role::Merchant.
     */
    MerchantCard() : Card(Role::Merchant) {}

    /**
     * @brief Gets the type of the card.
     * @return A string indicating this is a "MerchantCard".
     */
    std::string getType() const override { return "MerchantCard"; }
};
