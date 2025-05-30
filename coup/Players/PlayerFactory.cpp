/**
 * @file PlayerFactory.cpp
 * @brief Implements factory function for creating player objects based on roles.
 *
 * This file defines the createPlayerFromRole function, which generates
 * instances of different player types (Governor, Spy, Baron, etc.)
 * according to the specified role. It is used during the game setup
 * phase to assign a card (and thus a role) to each player.
 *
 * @author Gal Maymon
 */

#include "PlayerFactory.hpp"


std::unique_ptr<Player> createPlayerFromRole(const std::string& name, Role r) {
    switch (r) {
        case Role::Governor: return std::make_unique<GovernorPlayer>(name);
        case Role::Spy:      return std::make_unique<SpyPlayer>(name);
        case Role::Baron:    return std::make_unique<BaronPlayer>(name);
        case Role::General:  return std::make_unique<GeneralPlayer>(name);
        case Role::Judge:    return std::make_unique<JudgePlayer>(name);
        case Role::Merchant: return std::make_unique<MerchantPlayer>(name);
        default:
            throw std::runtime_error("Unknown role");
    }
}
