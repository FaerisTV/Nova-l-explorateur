#ifndef GAME_H
#define GAME_H

#include <QObject>
#include <QTimer>
#include "level.h"
#include "menu.h"
#include "shortscope.h"
#include <QLabel>

using namespace std;

/**
 * @brief Class representing the main game logic.
 *
 * Inherits from QObject to use Qt's signal and slot mechanism.
 */
class Game : public QObject
{
    Q_OBJECT

    Level * itsLevel; ///< Pointer to the current level in the game
    QTimer *itsTimer; ///< Timer to manage the game loop
    bool itsDead = false; ///< Flag indicating if the player is dead
    bool isPaused = false;

public:
    /**
     * @brief Constructor to initialize the game.
     *
     * @param parent Parent object, default is nullptr
     */
    Game(QObject *parent = nullptr);

    /**
     * @brief Destructor to clean up resources.
     */
    ~Game();

    /**
     * @brief Checks for collisions between the player and other objects.
     */
    void checkPlayerCollisions();

    /**
     * @brief Returns the current level.
     *
     * @return Pointer to the current level
     */
    Level* getItsLevel();

    /**
     * @brief Returns the player's state (alive or dead).
     *
     * @return True if the player is dead, false otherwise
     */
    bool getItsDead();

    /**
     * @brief Initiates an attack by the main character.
     */
    void attackMC();

    void loadNextLevel();

    void restartLevel();

    bool playerIsNearDoor;

    bool getIsPaused();

    void setIsPaused(bool statut);

    QTimer *getItsTimer();

     void onDoorCollision();
private slots:
    /**
     * @brief Main game loop to update game state.
     */
    void gameLoop();

signals:
    /**
     * @brief Signal emitted to request the game over screen.
     */
    void gameOverScreenRequested();
    void objectCollected(QString aText);
};

#endif // GAME_H
