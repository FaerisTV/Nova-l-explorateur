#ifndef PROJECTILE_H
#define PROJECTILE_H

#include "obstacle.h"
#include <list>
#include <QRect>

using namespace std;

/**
 * @brief The Projectile class represents a projectile in the game.
 */
class Projectile
{
    QRect itsProjectile; /**< Rectangle representing the projectile's position and size. */

public:
    /**
     * @brief Constructor to initialize a projectile.
     *
     * @param aX Initial X position of the projectile
     * @param aY Initial Y position of the projectile
     * @param aWidth Width of the projectile
     * @param aHeight Height of the projectile
     */
    Projectile(int aX, int aY, int aWidth, int aHeight);

    /**
     * @brief Updates the position of the projectile.
     *
     * @param obstacles List of obstacles present in the game
     */
    void updatePosition(list<Obstacle *>* obstacles);

    /**
     * @brief Gets the rectangle representing the projectile.
     *
     * @return QRect object representing the projectile's position and size
     */
    QRect getRect();
};

#endif // PROJECTILE_H
