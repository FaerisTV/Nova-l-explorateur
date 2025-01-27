#ifndef DOOR_H
#define DOOR_H

#include <QRect>

/**
 * @brief The Door class represents a door object with a rectangular shape.
 */
class Door {
public:
    /**
     * @brief Constructor for Door class.
     * @param x The x-coordinate of the door.
     * @param y The y-coordinate of the door.
     * @param width The width of the door.
     * @param height The height of the door.
     */
    Door(int x, int y, int width, int height);

    /**
     * @brief Returns the rectangle representing the door's dimensions and position.
     * @return QRect object representing the door's rectangle.
     */
    QRect getRect() const;

private:
    QRect rect; ///< Rectangle representing the door's dimensions and position.
};

#endif // DOOR_H
