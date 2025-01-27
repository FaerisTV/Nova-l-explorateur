#include "door.h"

/**
 * @brief Constructor of the Door class.
 *
 * Initializes a Door object with the given parameters.
 *
 * @param x X position of the door.
 * @param y Y position of the door.
 * @param width Width of the door.
 * @param height Height of the door.
 */
Door::Door(int x, int y, int width, int height) : rect(x, y, width, height) {}

/**
 * @brief Gets the rectangle representing the dimensions and position of the door.
 *
 * @return A QRect object representing the door.
 */
QRect Door::getRect() const {
    return rect;
}
