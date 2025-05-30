/**
 * @file PlayerFactory.hpp
 * @brief Declares a factory function to create Player instances based on their role.
 *
 * This header provides the interface for creating different specialized Player objects
 * (e.g., GovernorPlayer, SpyPlayer, etc.) using a given player name and role enum.
 * It supports the dynamic creation of polymorphic player instances during game setup.
 *
 * @author Gal Maymon
 */

#pragma once
#include <memory>
#include <string>
#include "Player.hpp"
#include "GeneralPlayer.hpp"
#include "SpyPlayer.hpp"
#include "GovernorPlayer.hpp"
#include "BaronPlayer.hpp"
#include "JudgePlayer.hpp"
#include "MerchantPlayer.hpp"
#include "../cards/Role.hpp" 

std::unique_ptr<Player> createPlayerFromRole(const std::string& name, Role r);
