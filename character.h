#ifndef CHARACTER_H
#define CHARACTER_H

#include "obstacle.h"
#include <list>

using namespace std;

/**
 * @brief Class representing a character in the game.
 */
class Character
{
protected:
    QRect itsCharacter; ///< Represents the character's dimensions and position
    int itsXSpeed; ///< Character's speed in the X direction
    int itsYSpeed; ///< Character's speed in the Y direction
    int itsHP = 3; ///< Character's health points, initialized to 3
    int itsDamage; ///< Damage the character can inflict
    std::list<QString> itsImages; ///< List of images associated with the character
    bool itsDead = false; ///< Character's state, false means alive
    int itsType;

public:
    /**
     * @brief Constructor to initialize the character.
     *
     * @param aX Initial X position of the character
     * @param aY Initial Y position of the character
     * @param aWidth Width of the character
     * @param aHeight Height of the character
     */
    Character(int aX, int aY, int aWidth, int aHeight, int type);

    /**
     * @brief Updates the character's position.
     *
     * @param obstacles List of obstacles present in the game
     */
    virtual void updatePosition(list<Obstacle *>* obstacles) = 0;

    /**
     * @brief Performs an attack.
     */
    virtual void attack() = 0;

    /**
     * @brief Gets the character's previous direction.
     *
     * @return True if the previous direction was to the right, false otherwise
     */
    virtual bool getPreviousDirection() = 0;

    /**
     * @brief Returns the rectangle representing the character.
     *
     * @return Rectangle of type QRect representing the character
     */
    QRect getRect();

    /**
     * @brief Returns the character's current health points.
     *
     * @return Number of health points
     */
    int getItsHP();

    /**
     * @brief Sets the character's health points.
     *
     * @param hp Number of health points to set
     */
    void setItsHP(int hp);

    int getItsXSpeed();

    /**
     * @brief Returns the character's state (alive or dead).
     *
     * @return True if the character is dead, false otherwise
     */
    bool getItsDead();

    /**
     * @brief Sets the character's state (alive or dead).
     *
     * @param state State to set for the character (true for dead, false for alive)
     */
    void setItsDead(bool state);

    int getType();
};

#endif // CHARACTER_H
