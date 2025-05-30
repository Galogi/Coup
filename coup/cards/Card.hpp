/**
 * @file Card.hpp
 * @brief Declaration of the Card base class.
 *
 * This header defines the abstract base class Card, which is used to represent
 * role cards in the game. It supports getting the card's role, name, and sprite,
 * and ensures that textures are loaded from the appropriate image files.
 *
 * Each specific role (e.g., Governor, Spy) has its own derived Card class.
 *
 * @author Gal Maymon
 */

#pragma once
#include <SFML/Graphics.hpp>
#include <memory>
#include <string>
#include <map>
#include "Role.hpp"

/**
 * @class Card
 * @brief Abstract base class representing a role card in the game.
 */
class Card {
protected:
    Role role;                 ///< Role associated with the card
    sf::Sprite sprite;         ///< Visual sprite for the card
    static std::map<Role, std::shared_ptr<sf::Texture>> textures; ///< Shared texture map

public:
    /**
     * @brief Constructs a Card with a specific role.
     * @param role The role to assign to the card.
     */
    Card(Role role);

    /**
     * @brief Virtual destructor.
     */
    virtual ~Card() = default;

    /**
     * @brief Gets the role of the card.
     * @return Role enum value.
     */
    virtual Role getRole() const;

    /**
     * @brief Gets the name of the card's role.
     * @return Name of the role as a string.
     */
    virtual std::string getName() const;

    /**
     * @brief Gets the sprite associated with the card.
     * @return Constant reference to the SFML sprite.
     */
    virtual const sf::Sprite& getSprite() const;

    /**
     * @brief Pure virtual function to get the card type.
     * @return String describing the type of the card.
     */
    virtual std::string getType() const = 0;

    /**
     * @brief Loads textures for all card roles.
     */
    static void loadAllTextures();

    /**
     * @brief Converts a Role enum to its corresponding string.
     * @param r The Role to convert.
     * @return Name of the role as a string.
     */
    static std::string roleToString(Role r);
};
