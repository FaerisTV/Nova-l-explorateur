#include "companion.h"

/**
 * @brief Constructor of the Companion class.
 *
 * Initializes a Companion object with the given parameters.
 *
 * @param aX Initial X position of the companion.
 * @param aY Initial Y position of the companion.
 * @param aWidth Width of the companion.
 * @param aHeight Height of the companion.
 * @param mainCharacter Pointer to the main character.
 */
Companion::Companion(int aX, int aY, int aWidth, int aHeight, MainCharacter *mainCharacter)
    : itsCompanion(aX, aY, aWidth, aHeight), groundLevel(aY), mainCharacter(mainCharacter)
{}

/**
 * @brief Destructor of the Companion class.
 */
Companion::~Companion() {}

/**
 * @brief Updates the position of the companion based on obstacles and flashback objects.
 *
 * @param obstacles List of obstacles in the game.
 * @param objects List of flashback objects in the game.
 */
void Companion::updatePosition(std::list<Obstacle *> *obstacles, std::list<FlashbackObject *> *objects)
{
    // Position of the main character
    QRect mainCharRect = mainCharacter->getRect();

    int marginX = 60;
    int marginY = 60;
    // Set the target position of the companion to stay within the top-left square of the main character
    int targetX = mainCharRect.left() - marginX;
    int targetY = mainCharRect.top() - marginY;

    // Check for objects within a 200 pixel radius and adjust the target position accordingly
    bool objectDetected = false;
    for (FlashbackObject* object : *objects)
    {
        QRect objectRect = object->getRect();
        int distanceX = abs(itsCompanion.center().x() - objectRect.center().x());
        int distanceY = abs(itsCompanion.center().y() - objectRect.center().y());

        // If an object is detected within a 500 pixel distance, set the target to move towards that object
        if (distanceX <= 500 && distanceY <= 500)
        {
            targetX = objectRect.left() - itsCompanion.width();
            targetY = objectRect.top() - itsCompanion.height();
            objectDetected = true;
            break;
        }
    }

    // Calculate speeds to move towards the new position
    if (objectDetected)
    {
        int deltaX = targetX - itsCompanion.left();
        int deltaY = targetY - itsCompanion.top();

        if (abs(deltaX) > 10)
        {
            itsXSpeed = (deltaX > 0) ? 4 : -10;
        }
        else
        {
            itsXSpeed = deltaX;
        }

        if (abs(deltaY) > 10)
        {
            itsYSpeed = (deltaY > 0) ? 4 : -10;
        }
        else
        {
            itsYSpeed = deltaY;
        }
    }
    else
    {
        itsXSpeed = targetX - itsCompanion.left();
        itsYSpeed = targetY - itsCompanion.top();
    }

    // Limit the vertical speed to prevent too rapid movements
    itsYSpeed = std::min(itsYSpeed, 10);

    bool obstacleDetected = false;
    int maxObstacleTop = INT_MIN; // Keep track of the highest height of all encountered obstacles

    for (Obstacle* obstacle : *obstacles)
    {
        QRect obstacleRect = obstacle->getRect();
        QRect nextPosition = itsCompanion.translated(itsXSpeed, itsYSpeed);

        // Check if there will be a collision at the next position
        if (nextPosition.intersects(obstacleRect))
        {
            obstacleDetected = true;

            // If a collision is detected, adjust the vertical movement to dodge the obstacle
            if (itsCompanion.bottom() <= obstacleRect.top() && itsCompanion.top() >= groundLevel)
            {
                // If there is an obstacle ahead but the companion is on the ground, it jumps
                itsYSpeed = -17; // Initialize jump speed
                itsJump = true;
            }
            else if (itsCompanion.bottom() > obstacleRect.top() && itsCompanion.top() < groundLevel)
            {
                // If there is an obstacle ahead and the companion is in the air, it goes up
                itsYSpeed = obstacleRect.top() - itsCompanion.bottom() - 1;
            }

            // Update the maximum height of encountered obstacle
            maxObstacleTop = std::max(maxObstacleTop, obstacleRect.top());
        }
    }

    // If an obstacle is detected ahead and the companion is above the obstacle, stay above the obstacle
    if (obstacleDetected && itsCompanion.top() < maxObstacleTop)
    {
        itsCompanion.moveBottom(maxObstacleTop); // Place the companion above the obstacle
        itsYSpeed = 0; // Stop vertical movement
    }

    // Add Y floating effect
    int floatAmplitude = 12; // Amplitude of the floating effect
    float floatFrequency = 0.05; // Frequency of the floating effect

    // Calculate floating offset
    int floatOffset = static_cast<int>(floatAmplitude * sin(floatFrequency * time));

    // Apply the movement to the companion
    itsCompanion.translate(itsXSpeed, itsYSpeed + floatOffset);

    // Prevent the companion from falling below groundLevel
    if (itsCompanion.bottom() > groundLevel)
    {
        itsCompanion.moveBottom(groundLevel);
        itsYSpeed = 0; // Stop falling
    }
    time++;
}

/**
 * @brief Detects the presence of an object within a 500 pixel radius.
 *
 * @param objects List of flashback objects in the game.
 * @return True if an object is detected, false otherwise.
 */
bool Companion::detectObject(std::list<FlashbackObject *> *objects)
{
    // Iterate through all objects in the list
    for (FlashbackObject* object : *objects)
    {
        QRect objectRect = object->getRect();
        int distanceX = std::abs(itsCompanion.center().x() - objectRect.center().x());
        int distanceY = std::abs(itsCompanion.center().y() - objectRect.center().y());

        // Check if an object is within a 500 pixel distance
        if (distanceX <= 500 && distanceY <= 500)
        {
            return true; // Object detected
        }
    }

    return false; // No object detected
}

/**
 * @brief Enables or disables moving right.
 *
 * @param enable True to enable movement, false to disable.
 */
void Companion::moveRight(bool enable)
{
    itsRight = enable;
}

/**
 * @brief Enables or disables moving left.
 *
 * @param enable True to enable movement, false to disable.
 */
void Companion::moveLeft(bool enable)
{
    itsLeft = enable;
}

/**
 * @brief Checks if the companion is moving right.
 *
 * @return True if the companion is moving right, false otherwise.
 */
bool Companion::getItsRight()
{
    return itsRight;
}

/**
 * @brief Checks if the companion is moving left.
 *
 * @return True if the companion is moving left, false otherwise.
 */
bool Companion::getItsLeft()
{
    return itsLeft;
}

/**
 * @brief Makes the companion jump if enabled and at ground level.
 *
 * @param enable True to make the companion jump, false otherwise.
 */
void Companion::jump(bool enable)
{
    // Allow jumping only if the character is at ground level
    if (enable && itsCompanion.bottom() == groundLevel)
    {
        itsYSpeed = -17; // Initialize jump speed
        itsJump = true;
    }
}

/**
 * @brief Gets the previous direction of the companion. Empty implementation.
 *
 * @return Always false.
 */
bool Companion::getPreviousDirection()
{
    return false;
}

/**
 * @brief Gets the rectangle representing the dimensions and position of the companion.
 *
 * @return A QRect object representing the companion.
 */
QRect Companion::getRect()
{
    return itsCompanion;
}
