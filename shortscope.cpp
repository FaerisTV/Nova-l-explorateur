/**
 * @file shortscope.cpp
 * @brief Implementation of the ShortScope class methods.
 */

#include "shortscope.h"

/**
 * @brief Constructor for ShortScope class.
 * @param aX The x-coordinate of the character.
 * @param aY The y-coordinate of the character.
 * @param aWidth The width of the character.
 * @param aHeight The height of the character.
 * @param type The type of the character.
 */
ShortScope::ShortScope(int aX, int aY, int aWidth, int aHeight, int type)
    : Character(aX, aY, aWidth, aHeight, type)
{
    itsXSpeed = 1; // Initialize horizontal speed
}

/**
 * @brief Updates the position of the character based on obstacles.
 * @param obstacles A pointer to a list of obstacles to check against.
 *
 * This function checks if there is an obstacle below the character and changes its movement direction accordingly.
 * It also handles collisions with obstacles to avoid getting stuck.
 */
void ShortScope::updatePosition(std::list<Obstacle *>* obstacles)
{
    // Check if there is an obstacle below
    bool obstacleBelow = false;
    QRect fictiveCharacter = itsCharacter;
    fictiveCharacter.translate(itsXSpeed * 60, itsCharacter.height() / 4 + 1); // One pixel below the character

    for (Obstacle* obstacle : *obstacles)
    {
        if (fictiveCharacter.intersects(obstacle->getRect()))
        {
            obstacleBelow = true;
            break;
        }
    }

    // Change direction if no obstacle below
    if (!obstacleBelow)
    {
        itsXSpeed = -itsXSpeed;
        previousDirection = !previousDirection;
    }

    // Create a fictive rectangle for the new position
    QRect newCharacterRect = itsCharacter;
    newCharacterRect.translate(itsXSpeed, 0);

    for (Obstacle* obstacle : *obstacles)
    {
        if (newCharacterRect.intersects(obstacle->getRect()))
        {
            // Reverse direction in case of collision
            itsXSpeed = -itsXSpeed;
            previousDirection = !previousDirection;
            newCharacterRect.translate(2 * itsXSpeed, 0); // Adjust position to avoid blocking
            break;
        }
    }
    itsCharacter = newCharacterRect; // Update character's position
}

/**
 * @brief Initiates an attack action.
 * Currently commented out as the implementation is not provided.
 */
void ShortScope::attack()
{

}

/**
 * @brief Returns the previous movement direction of the character.
 * @return true if the previous direction was right, false if left.
 */
bool ShortScope::getPreviousDirection()
{
    return previousDirection;
}
