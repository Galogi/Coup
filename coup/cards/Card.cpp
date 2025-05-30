/**
 * @file Card.cpp
 * @brief Implementation of the Card class and its texture-loading logic.
 *
 * This file defines the behavior of a Card, which represents a role in the game.
 * It includes loading textures for visual display and returning information about the card.
 *
 * Roles are defined using the Role enum and textures are loaded from the photo_cards folder.
 *
 * @author Gal Maymon
 */

#include "Card.hpp"
#include <stdexcept>

std::map<Role, std::shared_ptr<sf::Texture>> Card::textures;

/**
 * @brief Constructs a Card with the specified role and assigns its texture.
 * @param role The role assigned to this card.
 * @throws std::runtime_error If the texture for the role cannot be loaded.
 */
Card::Card(Role role) : role(role) {
    if (textures.empty()) loadAllTextures();
    sprite.setTexture(*textures[role]);
}

/**
 * @brief Returns the role of this card.
 * @return Role enum value representing the card's role.
 */
Role Card::getRole() const { return role; }

/**
 * @brief Returns the name of the role as a string.
 * @return Role name in string format.
 */
std::string Card::getName() const {
    return roleToString(role);
}

/**
 * @brief Returns the sprite associated with this card.
 * @return Reference to the SFML sprite.
 */
const sf::Sprite& Card::getSprite() const {
    return sprite;
}

/**
 * @brief Loads textures for all roles into a shared texture map.
 * @throws std::runtime_error If any texture fails to load.
 */
void Card::loadAllTextures() {
    for (Role r : { Role::Governor, Role::Spy, Role::Baron, Role::General, Role::Judge, Role::Merchant }) {
        auto tex = std::make_shared<sf::Texture>();
        std::string filename = "cards/photo_cards/" + roleToString(r) + ".jpg";
        if (!tex->loadFromFile(filename)) {
            throw std::runtime_error("Failed to load texture: " + filename);
        }
        textures[r] = tex;
    }
}

/**
 * @brief Converts a Role enum value to its corresponding string.
 * @param r The role to convert.
 * @return String representation of the role.
 */
std::string Card::roleToString(Role r) {
    switch (r) {
        case Role::Governor: return "Governor";
        case Role::Spy: return "Spy";
        case Role::Baron: return "Baron";
        case Role::General: return "General";
        case Role::Judge: return "Judge";
        case Role::Merchant: return "Merchant";
    }
    return "Unknown";
}
