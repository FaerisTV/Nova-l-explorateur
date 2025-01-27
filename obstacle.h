#ifndef OBSTACLE_H
#define OBSTACLE_H

#include <QRect>

/**
 * @brief The Obstacle class represents an obstacle in the game.
 */
class Obstacle
{
    QRect itsObstacle; /**< Rectangle representing the obstacle's position and size. */

public:
    /**
     * @brief Constructor to initialize an obstacle.
     *
     * @param aX Initial X position of the obstacle
     * @param aY Initial Y position of the obstacle
     * @param aWidth Width of the obstacle
     * @param aHeight Height of the obstacle
     */
    Obstacle(int aX, int aY, int aWidth, int aHeight);

    /**
     * @brief Gets the rectangle representing the obstacle.
     *
     * @return QRect object representing the obstacle's position and size
     */
    QRect getRect();
};

#endif // OBSTACLE_H
