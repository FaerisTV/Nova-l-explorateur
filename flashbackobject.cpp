#include "flashbackobject.h"

/**
 * @brief Constructor of the FlashbackObject class.
 *
 * Initializes a FlashbackObject object with the given parameters.
 *
 * @param aX Initial X position of the flashback object.
 * @param aY Initial Y position of the flashback object.
 * @param aWidth Width of the flashback object.
 * @param aHeight Height of the flashback object.
 * @param aNb Number associated with the flashback object.
 * @param aText Text associated with the flashback object.
 */
FlashbackObject::FlashbackObject(int aX, int aY, int aWidth, int aHeight, QString aNb, QString aText)
    : itsNb(aNb), itsText(aText), itsFlashbackObject(aX, aY, aWidth, aHeight)
{}

/**
 * @brief Gets the rectangle representing the dimensions and position of the flashback object.
 *
 * @return A QRect object representing the flashback object.
 */
QRect FlashbackObject::getRect()
{
    return itsFlashbackObject;
}

/**
 * @brief Gets the number associated with the flashback object.
 *
 * @return A QString object representing the number of the flashback object.
 */
QString FlashbackObject::getItsNb()
{
    return itsNb;
}

/**
 * @brief Gets the text associated with the flashback object.
 *
 * @return A QString object representing the text of the flashback object.
 */
QString FlashbackObject::getItsText()
{
    return itsText;
}
