#ifndef MAINCHARACTER_H
#define MAINCHARACTER_H

#include "character.h"
#include <QDateTime>
#include <list>

/**
 * @brief The MainCharacter class represents the main character in the game.
 *
 * Inherits from the Character class.
 */
class MainCharacter : public Character
{
    bool itsJump = 0; /**< Flag indicating whether the avatar is currently jumping. */
    bool itsRight = false; /**< Flag indicating whether the avatar is moving right. */
    int itsType  = 0;
    bool itsLeft = false; /**< Flag indicating whether the avatar is moving left. */
    int itsPieceNb = 0; /**< Number of collectible pieces collected by the main character. */
    bool itsPreviousDirection = false;
    int itsFlashBackObjectNb = 0; /**< Number of flashback objects collected by the main character. */
    bool itsInvulnerable = false; /**< Flag indicating whether the main character is invulnerable. */
    QDateTime lastHitTime; /**< Timestamp of the last hit taken by the main character. */
    QDateTime collisionStartTime; /**< Timestamp when the collision starts. */

public:
    /**
     * @brief Constructor to initialize a MainCharacter object.
     *
     * @param aX Initial X position of the MainCharacter
     * @param aY Initial Y position of the MainCharacter
     * @param aWidth Width of the MainCharacter
     * @param aHeight Height of the MainCharacter
     */
    MainCharacter(int aX, int aY, int aWidth, int aHeight);

    /**
     * @brief Destructor to clean up resources.
     */
    virtual ~MainCharacter();

    /**
     * @brief Updates the position of the MainCharacter.
     *
     * @param obstacles List of obstacles present in the game
     */
    void updatePosition(list<Obstacle *>* obstacles);

    /**
     * @brief Enables or disables the movement of the MainCharacter to the right.
     *
     * @param enable True to enable, false to disable
     */
    void moveRight(bool enable);

    /**
     * @brief Enables or disables the movement of the MainCharacter to the left.
     *
     * @param enable True to enable, false to disable
     */
    void moveLeft(bool enable);

    /**
     * @brief Initiates a jump action for the MainCharacter.
     *
     * @param enable True to enable jumping, false to disable
     */
    void jump(bool enable);

    /**
     * @brief Performs an attack action using the MainCharacter.
     */
    void attack();

    /**
     * @brief Increases the count of collectible pieces collected by the MainCharacter.
     */
    void addPiece();

    /**
     * @brief Getter for the number of collectible pieces collected by the MainCharacter.
     *
     * @return Number of collectible pieces
     */
    int getItsPieceNb();

    /**
     * @brief Getter for the flag indicating whether the MainCharacter is moving right.
     *
     * @return True if moving right, false otherwise
     */
    bool getItsRight();

    /**
     * @brief Getter for the flag indicating whether the MainCharacter is moving left.
     *
     * @return True if moving left, false otherwise
     */
    bool getItsLeft();

    /**
     * @brief Getter for the previous movement direction of the MainCharacter.
     *
     * @return True if previous direction was right, false if left
     */
    bool getPreviousDirection();

    bool setPreviousDirection(bool isleft);

    /**
     * @brief Getter for the number of flashback objects collected by the MainCharacter.
     *
     * @return Number of flashback objects collected
     */
    int getItsFlashbackObjectNb();

    /**
     * @brief Sets the invulnerability state of the MainCharacter.
     *
     * @param state True to set as invulnerable, false otherwise
     */
    void setInvulnerable(bool state);

    /**
     * @brief Checks if the MainCharacter is currently invulnerable.
     *
     * @return True if invulnerable, false otherwise
     */
    bool checkInvulnerability();

    /**
     * @brief Getter for the timestamp of the last hit taken by the MainCharacter.
     *
     * @return Timestamp of the last hit
     */
    const QDateTime& getLastHitTime() const;

    /**
     * @brief Sets the timestamp of the last hit taken by the MainCharacter.
     *
     * @param time Timestamp of the last hit
     */
    void setLastHitTime(const QDateTime& time);

    /**
     * @brief Marks the start of a collision with an obstacle or enemy.
     */
    void startCollision();

    /**
     * @brief Marks the end of a collision with an obstacle or enemy.
     */
    void endCollision();

    /**
     * @brief Checks if the duration of collision is within the specified limit.
     *
     * @return True if collision duration is within limit, false otherwise
     */
    bool checkCollisionDuration();

    bool isCollisionActive; /**< Flag indicating whether collision is currently active. */

    void addFlashbackObject();
};


#endif // MAINCHARACTER_H
