/**
 * @file obstacle.cpp
 * @brief Implementation of the Obstacle class methods.
 */

#include "obstacle.h"

/**
 * @brief Constructor for Obstacle class.
 * @param aX The x-coordinate of the obstacle.
 * @param aY The y-coordinate of the obstacle.
 * @param aWidth The width of the obstacle.
 * @param aHeight The height of the obstacle.
 */
Obstacle::Obstacle(int aX, int aY, int aWidth, int aHeight)
    : itsObstacle(aX, aY, aWidth, aHeight)
{}

/**
 * @brief Returns the rectangle representing the obstacle's dimensions and position.
 * @return QRect object representing the obstacle's rectangle.
 */
QRect Obstacle::getRect()
{
    return itsObstacle;
}
