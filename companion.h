#ifndef COMPANION_H
#define COMPANION_H

#include "character.h"
#include "flashbackobject.h"
#include "maincharacter.h"
#include <cmath>

using namespace std;

/**
 * @brief Class representing a companion character in the game.
 *
 * Inherits from the Character class.
 */
class Companion
{
    QRect itsCompanion;
    bool itsJump = 0; /**< Flag indicating whether the avatar is currently jumping. */
    bool itsRight = false; /**< Flag indicating whether the avatar is moving right. */
    bool itsLeft = false; /**< Flag indicating whether the avatar is moving left. */
    int itsXSpeed; ///< Character's speed in the X direction
    int itsYSpeed; ///< Character's speed in the Y direction
    int groundLevel;
    MainCharacter* mainCharacter; ///< Référence au personnage principal
    int time = 0;

public:
    /**
     * @brief Constructor to initialize the companion.
     *
     * @param aX Initial X position of the companion
     * @param aY Initial Y position of the companion
     * @param aWidth Width of the companion
     * @param aHeight Height of the companion
     */
    Companion(int aX, int aY, int aWidth, int aHeight, MainCharacter* mainCharacter);

    /**
     * @brief Destructor for the companion.
     */
    ~Companion();

    /**
     * @brief Detects flashback objects in the game.
     *
     * @param objects List of flashback objects present in the game
     * @return True if an object is detected, false otherwise
     */
    bool detectObject(list<FlashbackObject *>* objects);

    /**
     * @brief Updates the companion's position.
     *
     * @param obstacles List of obstacles present in the game
     */
    void updatePosition(list<Obstacle *>* obstacles, std::list<FlashbackObject *> *objects);

    /**
     * @brief Enables or disables the movement of the Companion to the right.
     *
     * @param enable True to enable, false to disable
     */
    void moveRight(bool enable);

    /**
     * @brief Enables or disables the movement of the Companion to the left.
     *
     * @param enable True to enable, false to disable
     */
    void moveLeft(bool enable);

    /**
     * @brief Getter for the flag indicating whether the Companion is moving right.
     *
     * @return True if moving right, false otherwise
     */
    bool getItsRight();

    /**
     * @brief Getter for the flag indicating whether the Companion is moving left.
     *
     * @return True if moving left, false otherwise
     */
    bool getItsLeft();

    /**
     * @brief Initiates a jump action for the Companion.
     *
     * @param enable True to enable jumping, false to disable
     */
    void jump(bool enable);

    /**
     * @brief Gets the companion's previous direction.
     *
     * @return True if the previous direction was to the right, false otherwise
     */
    bool getPreviousDirection();

    QRect getRect();
};

#endif // COMPANION_H
