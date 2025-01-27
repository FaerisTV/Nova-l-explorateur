#include "game.h"

/**
 * @brief Constructor of the Game class.
 *
 * Initializes the game with an initial level and sets up the game timer.
 *
 * @param parent Pointer to the parent object, default is nullptr.
 */
Game::Game(QObject* parent)
    : QObject(parent), itsLevel(new Level(0)), itsDead(false), isPaused(false)
{
    // Set up the game loop timer
    itsTimer = new QTimer(this);
    connect(itsTimer, SIGNAL(timeout()), this, SLOT(gameLoop()));
    itsTimer->start(10); // Start the game loop with a 10 ms interval

    playerIsNearDoor = false;
}

/**
 * @brief Main game loop.
 *
 * Updates characters' positions, checks collisions, and manages attacks.
 * This function is called every time the timer times out.
 */
void Game::gameLoop()
{
    if (itsLevel->getItsBoss() != nullptr)
    {
        itsLevel->getItsBoss()->attack();
    }

    if (!itsDead)
        itsLevel->getItsMainCharacter()->updatePosition(itsLevel->getItsObstacles());

    itsLevel->getItsCompanion()->updatePosition(itsLevel->getItsObstacles(), itsLevel->getItsFlashbackObjects());

    for (Character* character : *itsLevel->getItsEnemies())
    {
        if (character != nullptr)
        {
            character->updatePosition(itsLevel->getItsObstacles());
            //character->attack(itsMainCharacter);
        }
    }

    if (itsLevel->getItsFinalBoss() != nullptr)
    {
        itsLevel->getItsFinalBoss()->updatePosition(itsLevel->getItsObstacles());
    }

    checkPlayerCollisions();
}

/**
 * @brief Destructor of the Game class.
 *
 * Frees allocated memory for the timer and the level.
 */
Game::~Game()
{
    delete itsTimer;
    delete itsLevel;
}

/**
 * @brief Main character's attack function.
 *
 * Checks collisions with enemies and bosses, reducing their respective health.
 * Also adds additional enemies when the final boss loses health.
 */
void Game::attackMC()
{
    QRect extendedHitbox = itsLevel->getItsMainCharacter()->getRect();
    extendedHitbox.setSize(extendedHitbox.size() * 1.2);
    extendedHitbox.moveCenter(itsLevel->getItsMainCharacter()->getRect().center());

    // Check collisions with enemies
    for (auto it = itsLevel->getItsEnemies()->begin(); it != itsLevel->getItsEnemies()->end();)
    {
        Character* character = *it;
        if (extendedHitbox.intersects(character->getRect()))
        {
            character->setItsHP(character->getItsHP() - 1);
            if (character->getItsHP() <= 0)
            {
                it = itsLevel->getItsEnemies()->erase(it);
                character = nullptr;
                itsLevel->getItsMainCharacter()->addPiece();
            }
            else
            {
                ++it;
            }
        }
        else
        {
            ++it;
        }
    }

    // Check collision with boss
    if (itsLevel->getItsBoss() != nullptr && extendedHitbox.intersects(itsLevel->getItsBoss()->getRect()))
    {
        itsLevel->getItsBoss()->setItsHP(itsLevel->getItsBoss()->getItsHP() - 1);
    }

    // Check collision with final boss
    if (itsLevel->getItsFinalBoss() != nullptr && extendedHitbox.intersects(itsLevel->getItsFinalBoss()->getRect()))
    {
        itsLevel->getItsFinalBoss()->setItsHP(itsLevel->getItsFinalBoss()->getItsHP() - 1);

        // Add enemies periodically when final boss loses health
        if (itsLevel->getItsFinalBoss()->getItsHP() <= 0 && itsLevel->getItsFinalBoss()->getItsHP() % 4 == 0)
        {
            std::srand(static_cast<unsigned int>(std::time(nullptr)));
            int x = std::rand() % (1030 - 50 + 1) + 50;
            int y = itsLevel->getItsFinalBoss()->getRect().y();

            ShortScope* newEnemy = new ShortScope(x, y, 100, 115, 1);
            itsLevel->getItsEnemies()->push_back(newEnemy);
        }
    }
}

/**
 * @brief Checks collisions of the player character with various game elements.
 *
 * Checks collisions with enemies, bosses, pieces, flashback objects, and doors.
 * Also manages game over conditions when the player goes out of bounds or loses all health.
 */
void Game::checkPlayerCollisions()
{
    QRect playerHitbox = itsLevel->getItsMainCharacter()->getRect();
    int levelHeight = itsLevel->getItsLevelHeight();

    // Check if player falls out of the screen
    if (playerHitbox.bottom() >= levelHeight + 200)
    {
        itsLevel->getItsMainCharacter()->setItsHP(0);
        emit gameOverScreenRequested();
        itsDead = true;
        return;
    }

    // Check collision with boss and its summonings
    ClassicBoss* boss = itsLevel->getItsBoss();
    if (boss != nullptr)
    {
        auto* summonings = boss->getItsSummoning();
        for (auto it = summonings->begin(); it != summonings->end();)
        {
            QRect* summoning = *it;
            QRect swordHitbox = *summoning;
            swordHitbox.setWidth(swordHitbox.width() / 4.2 - 10);
            swordHitbox.setHeight(swordHitbox.height() / 4 - 10);

            if (swordHitbox.intersects(playerHitbox))
            {
                if (boss->getIsAttacking())
                {
                    itsLevel->getItsMainCharacter()->setItsHP(itsLevel->getItsMainCharacter()->getItsHP() - 1);
                    if (itsLevel->getItsMainCharacter()->getItsHP() <= 0)
                    {
                        emit gameOverScreenRequested();
                        itsDead = true;
                    }
                }
                it = summonings->erase(it);
                delete summoning;
            }
            else if (summoning->y() > 555 || summoning->x() < 5)
            {
                it = summonings->erase(it);
                delete summoning;
                std::srand(static_cast<unsigned int>(std::time(nullptr)));
                boss->setItsPhase(std::rand() % 3 + 1);
                boss->setIsAttacking(false);
            }
            else
            {
                ++it;
            }
        }

        // Delete boss if it's dead and has no summonings left
        if (boss->getItsHP() <= 0 && summonings->empty())
        {
            delete boss;
            itsLevel->setItsBoss(nullptr);
        }
    }

    // Check collision with pieces
    for (auto it = itsLevel->getItsPieces()->begin(); it != itsLevel->getItsPieces()->end();)
    {
        Piece* piece = *it;
        if (playerHitbox.intersects(piece->getRect()))
        {
            itsLevel->getItsMainCharacter()->addPiece();
            it = itsLevel->getItsPieces()->erase(it);
            delete piece;
        }
        else
        {
            ++it;
        }
    }

    // Check collision with flashback objects
    for (auto it = itsLevel->getItsFlashbackObjects()->begin(); it != itsLevel->getItsFlashbackObjects()->end();)
    {
        FlashbackObject* object = *it;
        if (playerHitbox.intersects(object->getRect()))
        {
            itsLevel->getItsMainCharacter()->addFlashbackObject();
            emit objectCollected(object->getItsText());
            it = itsLevel->getItsFlashbackObjects()->erase(it);
            delete object;
        }
        else
        {
            ++it;
        }
    }

    // Check collision with enemies
    bool isAnyCollision = false;
    for (Character* enemy : *itsLevel->getItsEnemies())
    {
        if (playerHitbox.intersects(enemy->getRect()))
        {
            isAnyCollision = true;
            itsLevel->getItsMainCharacter()->startCollision();
            break;
        }
    }

    // Check collision with final boss
    if (itsLevel->getItsFinalBoss() != nullptr && playerHitbox.intersects(itsLevel->getItsFinalBoss()->getRect()))
    {
        isAnyCollision = true;
        itsLevel->getItsMainCharacter()->startCollision();
    }

    // End collision state if no collision detected
    if (!isAnyCollision && itsLevel->getItsMainCharacter()->isCollisionActive)
    {
        itsLevel->getItsMainCharacter()->endCollision();
    }

    // Reduce main character's health if collision state persists
    if (itsLevel->getItsMainCharacter()->checkCollisionDuration())
    {
        itsLevel->getItsMainCharacter()->setItsHP(itsLevel->getItsMainCharacter()->getItsHP() - 1);
        if (itsLevel->getItsMainCharacter()->getItsHP() <= 0)
        {
            emit gameOverScreenRequested();
            itsDead = true;
        }
    }

    // Emit signal for door collision
    if (itsLevel->getItsDoor() && playerHitbox.intersects(itsLevel->getItsDoor()->getRect()))
    {
        emit onDoorCollision();
    }
}

/**
 * @brief Retrieves the current game level.
 *
 * @return Pointer to the current Level object.
 */
Level* Game::getItsLevel()
{
    return itsLevel;
}

/**
 * @brief Retrieves the game "dead" state.
 *
 * @return true if the player is dead, false otherwise.
 */
bool Game::getItsDead()
{
    return itsDead;
}

/**
 * @brief Retrieves the game timer.
 *
 * @return Pointer to the QTimer object used for the game.
 */
QTimer* Game::getItsTimer()
{
    return itsTimer;
}

/**
 * @brief Loads the next level in the game.
 *
 * Deletes the current Level object and loads the next level by incrementing its number.
 * Also resets the player's near door state.
 */
void Game::loadNextLevel()
{
    int nextLevelNumber = itsLevel->getItsNb() + 1;
    delete itsLevel;
    itsLevel = new Level(nextLevelNumber);
    playerIsNearDoor = false;
}

/**
 * @brief Handles collision with the door.
 *
 * Checks if the player is interacting with the door and adjusts the "playerIsNearDoor" state accordingly.
 * Also checks the boss state if the player has enough flashback objects to pass through the door.
 */
void Game::onDoorCollision()
{
    if (itsLevel->getItsDoor())
    {
        QRect playerRect = itsLevel->getItsMainCharacter()->getRect();
        QRect doorRect = itsLevel->getItsDoor()->getRect();

        if (playerRect.intersects(doorRect))
        {
            if (itsLevel->getItsMainCharacter()->getItsFlashbackObjectNb() >= itsLevel->getItsFlashbackObjectNb())
            {
                if (itsLevel->getItsBoss())
                {
                    ClassicBoss* boss = itsLevel->getItsBoss();
                    // Check if boss is still alive
                    if (boss && boss->getItsHP() > 0)
                    {
                        // Do nothing if boss is still alive
                        return;
                    }
                }
                playerIsNearDoor = true;
            }
            else
            {
                playerIsNearDoor = false;
            }
        }
        else
        {
            playerIsNearDoor = false;
        }
    }
}

/**
 * @brief Restarts the current level.
 *
 * Deletes the current Level object and creates a new Level with the initial level number.
 * Also resets the game "dead" state and restarts the game timer.
 */
void Game::restartLevel()
{
    delete itsLevel;
    itsLevel = new Level(1); // or use another level number if needed

    itsDead = false;

    itsTimer->start();
}

/**
 * @brief Checks if the game is paused.
 *
 * @return true if the game is paused, false otherwise.
 */
bool Game::getIsPaused()
{
    return isPaused;
}

/**
 * @brief Sets the game pause state.
 *
 * @param status New pause state to set.
 */
void Game::setIsPaused(bool status)
{
    isPaused = status;
}

