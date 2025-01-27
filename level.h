#ifndef LEVEL_H
#define LEVEL_H

#include "QtMultimedia/qaudiooutput.h"
#include "QtMultimedia/qmediaplayer.h"
#include <QObject>
#include "character.h"
#include "companion.h"
#include "flashbackobject.h"
#include "shortscope.h"
#include "maincharacter.h"
#include "classicboss.h"
#include "finalboss.h"
#include "companion.h"
#include "piece.h"
#include <QString>
#include <list>
#include <fstream>
#include <sstream>
#include <string>
#include <iostream>
#include "door.h"

using namespace std;

/**
 * @brief The Level class represents a game level.
 */
class Level
{
    // Set the level dimensions
    int itsLevelWidth = 8000; /**< Width of the level. */
    int itsLevelHeight = 720; /**< Height of the level. */
    const QString itsLevelFile; /**< File path for level configuration. */
    const QString itsBackground; /**< Background image for the level. */
    const int itsNb; /**< Number identifier for the level. */
    QString itsEnemyType;
    int itsFlashbackObjectNb = 0;
    list<Obstacle *> *itsObstacles; /**< List of obstacles in the level. */
    list<Piece *> *itsPieces; /**< List of collectible pieces in the level. */
    list<FlashbackObject *> *itsFlashbackObjects; /**< List of flashback objects in the level. */
    list<Character *> *itsEnemies; /**< List of enemies in the level. */
    MainCharacter *itsMainCharacter; /**< Pointer to the main character of the level. */
    Companion *itsCompanion; /**< Pointer to the companion character of the level. */
    Door* itsDoor;
    QMediaPlayer *player;
    QAudioOutput *output;
    ClassicBoss *itsClassicBoss = nullptr;
    FinalBoss *itsFinalBoss = nullptr;
    int itsHUDNb;

public:
    /**
     * @brief Constructor to initialize a level.
     *
     * @param aNumber Level number identifier.
     */
    Level(int aNumber);

    /**
     * @brief Destructor to clean up resources.
     */
    ~Level();

    /**
     * @brief Getter for the list of enemies in the level.
     *
     * @return List of enemies.
     */
    list<Character *> *getItsEnemies();

    /**
     * @brief Getter for the list of obstacles in the level.
     *
     * @return List of obstacles.
     */
    list<Obstacle *> *getItsObstacles() const;

    /**
     * @brief Getter for the list of collectible pieces in the level.
     *
     * @return List of collectible pieces.
     */
    list<Piece *> *getItsPieces() const;

    /**
     * @brief Getter for the list of flashback objects in the level.
     *
     * @return List of flashback objects.
     */
    list<FlashbackObject *> *getItsFlashbackObjects() const;

    int getItsFlashbackObjectNb();

    /**
     * @brief Getter for the main character of the level.
     *
     * @return Pointer to the main character.
     */
    MainCharacter *getItsMainCharacter();

    /**
     * @brief Getter for the companion character of the level.
     *
     * @return Pointer to the companion character.
     */
    Companion *getItsCompanion();

    ClassicBoss *getItsBoss();

    FinalBoss *getItsFinalBoss();

    /**
     * @brief Getter for the width of the level.
     *
     * @return Width of the level.
     */
    int getItsLevelWidth();

    /**
     * @brief Getter for the height of the level.
     *
     * @return Height of the level.
     */
    int getItsLevelHeight();

    /**
     * @brief Setter for the list of enemies in the level.
     *
     * @param enemies List of enemies to set.
     */
    void setItsEnemies(list<Character *> *enemies);

    /**
     * @brief Setter for the list of obstacles in the level.
     *
     * @param obstacles List of obstacles to set.
     */
    void setItsObstacles(list<Obstacle *> *obstacles);

    /**
     * @brief Setter for the list of collectible pieces in the level.
     *
     * @param pieces List of collectible pieces to set.
     */
    void setItsPieces(list<Piece *> *pieces);

    /**
     * @brief Setter for the list of flashback objects in the level.
     *
     * @param flashbackObjects List of flashback objects to set.
     */
    void setItsFlashbackObjects(list<FlashbackObject *> *flashbackObjects);

    /**
     * @brief Setter for the main character of the level.
     *
     * @param mainCharacter Pointer to the main character to set.
     */
    void setItsMainCharacter(MainCharacter *mainCharacter);

    /**
     * @brief Setter for the companion character of the level.
     *
     * @param companion Pointer to the companion character to set.
     */
    void setItsCompanion(Companion *companion);

    /**
     * @brief Setter for the file path of the level configuration.
     *
     * @param aFile File path to set.
     */
    void setItsLevelFile(QString aFile);

    /**
     * @brief Loads the level configuration from the file.
     */
    void loadLevel();
    Door* getItsDoor() const;
    int getItsNb();
    QString getItsEnemyType();
    void setItsEnemyType(QString type);
    //void setSongVolume(int volume);
    void setItsLevelWidth(int width);
    void setItsBoss(ClassicBoss* boss);
    int getItsHUDNb();

    QMediaPlayer *getPlayer();

    void songMuted();

    void songStart();
};

#endif // LEVEL_H
