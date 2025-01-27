#ifndef FLASHBACKOBJECT_H
#define FLASHBACKOBJECT_H

#include <QRect>

/**
 * @brief Class representing a flashback object in the game.
 */
class FlashbackObject
{
    const QString itsNb;
    const QString itsText;
    QRect itsFlashbackObject; ///< Rectangle representing the dimensions and position of the flashback object

public:
    /**
     * @brief Constructor to initialize the flashback object.
     *
     * @param aX Initial X position of the flashback object
     * @param aY Initial Y position of the flashback object
     * @param aWidth Width of the flashback object
     * @param aHeight Height of the flashback object
     */
    FlashbackObject(int aX, int aY, int aWidth, int aHeight, QString aNb, QString aText);

    /**
     * @brief Returns the rectangle representing the flashback object.
     *
     * @return Rectangle of type QRect representing the flashback object
     */
    QRect getRect();

    QString getItsNb();
    
    QString getItsText();
};

#endif // FLASHBACKOBJECT_H
