/**
 * @file Role.hpp
 * @brief Enumeration of roles in the Coup-inspired game.
 *
 * This enum defines all possible roles that a card or player can have.
 * It is used throughout the game logic and card definitions.
 *
 * @author Gal Maymon
 */

#pragma once

/**
 * @enum Role
 * @brief Represents the available roles in the game.
 */
enum class Role {
    Governor,   /**< Governor role: Enhanced tax, blocks Tax. */
    Spy,        /**< Spy role: Peek and disable Arrest. */
    Baron,      /**< Baron role: Invest coins, Sanction refund. */
    General,    /**< General role: Blocks Coup, Arrest refund. */
    Judge,      /**< Judge role: Cancels Bribe, sanctions cost extra. */
    Merchant    /**< Merchant role: Bonus income if ≥3 coins. */
};
