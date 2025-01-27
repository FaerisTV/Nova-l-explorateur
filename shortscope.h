#ifndef SHORTSCOPE_H
#define SHORTSCOPE_H

#include <list>
#include "character.h"
#include "maincharacter.h"

/**
 * @brief The ShortScope class represents a character with short-range attack capability.
 *
 * Inherits from the Character class.
 */
class ShortScope : public Character
{
    bool previousDirection = false; /**< Flag indicating the previous movement direction. */

public:
    /**
     * @brief Constructor to initialize a ShortScope object.
     *
     * @param aX Initial X position of the ShortScope
     * @param aY Initial Y position of the ShortScope
     * @param aWidth Width of the ShortScope
     * @param aHeight Height of the ShortScope
     */
    ShortScope(int aX, int aY, int aWidth, int aHeight, int type);

    /**
     * @brief Updates the position of the ShortScope.
     *
     * @param obstacles List of obstacles present in the game
     */
    void updatePosition(list<Obstacle *>* obstacles);

    /**
     * @brief Performs an attack action using the ShortScope.
     */
    void attack();

    /**
     * @brief Gets the previous movement direction of the ShortScope.
     *
     * @return True if the previous direction was to the right, false otherwise
     */
    bool getPreviousDirection();
};

#endif // SHORTSCOPE_H
