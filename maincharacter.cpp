#include "maincharacter.h"

/**
 * @brief Constructor for MainCharacter class.
 *
 * Initializes the main character with position and default attributes.
 *
 * @param aX X-coordinate of the character's initial position.
 * @param aY Y-coordinate of the character's initial position.
 * @param aWidth Width of the character's collision box.
 * @param aHeight Height of the character's collision box.
 */
MainCharacter::MainCharacter(int aX, int aY, int aWidth, int aHeight)
    : Character(aX, aY, aWidth, aHeight, MainCharacter::itsType)
{
    itsHP = 6;
    itsInvulnerable = false;
}

/**
 * @brief Destructor for MainCharacter class.
 */
MainCharacter::~MainCharacter(){}

/**
 * @brief Updates the position of the main character based on its speed and obstacles.
 *
 * Checks for collisions with obstacles and adjusts position accordingly.
 *
 * @param obstacles List of obstacles in the level.
 */
void MainCharacter::updatePosition(list<Obstacle *>* obstacles)
{
    int speedFactor = 3;
    itsXSpeed = speedFactor * (itsRight - itsLeft);

    itsYSpeed += 1;

    itsYSpeed = std::min(itsYSpeed, 10);

    for (Obstacle* obstacle : *obstacles)
    {
        QRect fictiveCharacter = itsCharacter;
        fictiveCharacter.translate(itsXSpeed, itsYSpeed);

        QRect intersection = fictiveCharacter.intersected(obstacle->getRect());
        while (!intersection.isEmpty())
        {
            if (std::abs(itsYSpeed / intersection.height()) >= std::abs(itsXSpeed / intersection.width()))
            {
                if (itsYSpeed > 0)
                {
                    if (itsJump)
                    {
                        itsYSpeed -= 17;
                    }
                    else
                    {
                        itsYSpeed -= intersection.height();
                    }
                }
                else if (itsYSpeed < 0)
                    itsYSpeed += intersection.height();
            }
            else
            {
                if (itsXSpeed > 0)
                    itsXSpeed -= intersection.width();
                else if (itsXSpeed < 0)
                    itsXSpeed += intersection.width();
            }

            fictiveCharacter = itsCharacter;
            fictiveCharacter.translate(itsXSpeed, itsYSpeed);

            intersection = fictiveCharacter.intersected(obstacle->getRect());
        }
    }

    itsCharacter.translate(itsXSpeed, itsYSpeed);
}

/**
 * @brief Sets the movement direction to right or stops it.
 *
 * @param enable True to move right, false to stop.
 */
void MainCharacter::moveRight(bool enable)
{
    itsRight = enable;
}

/**
 * @brief Sets the movement direction to left or stops it.
 *
 * @param enable True to move left, false to stop.
 */
void MainCharacter::moveLeft(bool enable)
{
    itsLeft = enable;
}

/**
 * @brief Sets the jumping action of the character.
 *
 * @param enable True to initiate a jump, false otherwise.
 */
void MainCharacter::jump(bool enable)
{
    itsJump = enable;
}

/**
 * @brief Placeholder for attack action.
 *
 * Currently does nothing. To be implemented.
 */
void MainCharacter::attack()
{
    // To be implemented
}

/**
 * @brief Increases the number of collected pieces and potentially restores HP.
 */
void MainCharacter::addPiece()
{
    itsPieceNb++;
    itsPieceNb %= 10;
    if (itsPieceNb == 0)
    {
        itsHP += 1;
    }
    if (itsHP > 6)
    {
        itsHP = 6;
    }
}

/**
 * @brief Increases the number of collected flashback objects.
 */
void MainCharacter::addFlashbackObject()
{
    itsFlashBackObjectNb++;
}

/**
 * @brief Getter for the flag indicating movement to the right.
 *
 * @return bool True if moving right, false otherwise.
 */
bool MainCharacter::getItsRight()
{
    return itsRight;
}

/**
 * @brief Getter for the flag indicating movement to the left.
 *
 * @return bool True if moving left, false otherwise.
 */
bool MainCharacter::getItsLeft()
{
    return itsLeft;
}

/**
 * @brief Getter for the previous movement direction.
 *
 * @return bool True if previously left, false if right.
 */
bool MainCharacter::getPreviousDirection()
{
    return itsPreviousDirection;
}

/**
 * @brief Setter for the previous movement direction.
 *
 * @param isleft True if the previous direction was left, false if right.
 */
bool MainCharacter::setPreviousDirection(bool isleft)
{
    itsPreviousDirection = isleft;
}

/**
 * @brief Getter for the number of flashback objects collected.
 *
 * @return int Number of flashback objects collected.
 */
int MainCharacter::getItsFlashbackObjectNb()
{
    return itsFlashBackObjectNb;
}

/**
 * @brief Getter for the number of pieces collected.
 *
 * @return int Number of pieces collected.
 */
int MainCharacter::getItsPieceNb()
{
    return itsPieceNb;
}

/**
 * @brief Sets the invulnerability state of the character.
 *
 * @param state True to set invulnerable, false otherwise.
 */
void MainCharacter::setInvulnerable(bool state)
{
    itsInvulnerable = state;
    lastHitTime = QDateTime::currentDateTime();
}

/**
 * @brief Checks if the character is currently invulnerable and updates its state if necessary.
 *
 * @return bool True if invulnerable, false otherwise.
 */
bool MainCharacter::checkInvulnerability()
{
    if (itsInvulnerable)
    {
        qint64 msSinceLastHit = lastHitTime.msecsTo(QDateTime::currentDateTime());
        if (msSinceLastHit > 1000)
        {
            itsInvulnerable = false;
        }
    }
    return itsInvulnerable;
}

/**
 * @brief Sets the time of the last hit received by the character.
 *
 * @param time QDateTime representing the time of the last hit.
 */
void MainCharacter::setLastHitTime(const QDateTime& time)
{
    lastHitTime = time;
}

/**
 * @brief Getter for the time of the last hit received by the character.
 *
 * @return const QDateTime& QDateTime object representing the time of the last hit.
 */
const QDateTime& MainCharacter::getLastHitTime() const
{
    return lastHitTime;
}

/**
 * @brief Starts the collision detection process.
 */
void MainCharacter::startCollision()
{
    if (!isCollisionActive) {
        collisionStartTime = QDateTime::currentDateTime();
        isCollisionActive = true;
    }
}

/**
 * @brief Ends the collision detection process.
 */
void MainCharacter::endCollision()
{
    isCollisionActive = false;
}

/**
 * @brief Checks if the collision duration has reached its limit.
 *
 * @return bool True if collision duration limit exceeded, false otherwise.
 */
bool MainCharacter::checkCollisionDuration()
{
    if (isCollisionActive && collisionStartTime.msecsTo(QDateTime::currentDateTime()) >= 400)
    {
        endCollision();
        return true;
    }
    return false;
}
