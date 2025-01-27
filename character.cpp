#include "character.h"

/**
 * @brief Constructor of the Character class.
 *
 * Initializes a Character object with the given parameters.
 *
 * @param aX Initial X position of the character.
 * @param aY Initial Y position of the character.
 * @param aWidth Width of the character.
 * @param aHeight Height of the character.
 * @param type Type of the character.
 */
Character::Character(int aX, int aY, int aWidth, int aHeight, int type)
    : itsCharacter(aX, aY, aWidth, aHeight), itsType(type)
{}

/**
 * @brief Gets the rectangle representing the dimensions and position of the character.
 *
 * @return A QRect object representing the character.
 */
QRect Character::getRect()
{
    return itsCharacter;
}

/**
 * @brief Gets the hit points (HP) of the character.
 *
 * @return Current hit points of the character.
 */
int Character::getItsHP()
{
    return itsHP;
}

/**
 * @brief Sets the hit points (HP) of the character.
 *
 * @param hp New hit points of the character.
 */
void Character::setItsHP(int hp)
{
    itsHP = hp;
}

/**
 * @brief Checks if the character is dead.
 *
 * @return True if the character is dead, false otherwise.
 */
bool Character::getItsDead()
{
    return itsDead;
}

/**
 * @brief Gets the speed in the X direction of the character.
 *
 * @return X-speed of the character.
 */
int Character::getItsXSpeed()
{
    return itsXSpeed;
}

/**
 * @brief Sets the dead state of the character.
 *
 * @param state New dead state of the character.
 */
void Character::setItsDead(bool state)
{
    itsDead = state;
}

/**
 * @brief Gets the type of the character.
 *
 * @return Type of the character.
 */
int Character::getType()
{
    return itsType;
}
