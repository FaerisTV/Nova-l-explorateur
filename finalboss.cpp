#include "finalboss.h"
#include <cstdlib>
#include <ctime>
#include <QTransform>

/**
 * @brief Constructor of the FinalBoss class.
 *
 * Initializes a FinalBoss object with the given parameters.
 *
 * @param aX Initial X position of the final boss.
 * @param aY Initial Y position of the final boss.
 * @param aWidth Width of the final boss.
 * @param aHeight Height of the final boss.
 * @param type Type of the character.
 */
FinalBoss::FinalBoss(int aX, int aY, int aWidth, int aHeight, int type)
    : Character(aX, aY, aWidth, aHeight, type)
{
    itsHP = 32;  // Assuming the final boss has more hit points
    itsXSpeed = 2;
}

/**
 * @brief Attack method of the final boss. Empty implementation.
 */
void FinalBoss::attack() {}

/**
 * @brief Updates the position of the final boss based on obstacles.
 *
 * @param obstacles List of obstacles in the game.
 */
void FinalBoss::updatePosition(std::list<Obstacle *>* obstacles)
{
    if(itsHP > 0)
    {
        QRect newCharacterRect = itsCharacter;
        newCharacterRect.translate(itsXSpeed, 0);

        for (Obstacle* obstacle : *obstacles)
        {
            if (newCharacterRect.intersects(obstacle->getRect()))
            {
                // Reverse direction upon collision
                itsXSpeed = -itsXSpeed;
                itsPreviousDirection = !itsPreviousDirection;
                newCharacterRect.translate(2 * itsXSpeed, 0); // Adjust position to avoid sticking
                break;
            }
        }
        itsCharacter = newCharacterRect;
    }
    else
    {
        itsCharacter.translate(2000, -200);
    }
}

/**
 * @brief Gets the previous direction of the final boss.
 *
 * @return True if the previous direction was right, false otherwise.
 */
bool FinalBoss::getPreviousDirection()
{
    return itsPreviousDirection;
}
