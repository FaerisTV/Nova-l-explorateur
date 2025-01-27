#include "level.h"
#include "optionsmenu.h"
#include <QTextStream>
#include <QDebug>
#include <QFile>
#include <QMediaPlayer>
#include <QAudioOutput>
#include <QObject>

/**
 * @brief Constructor of the Level class.
 *
 * Initializes a level by loading elements from a specific text file associated with the level.
 * Loads main characters, obstacles, enemies, pieces, flashback objects, and bosses based on the level number.
 * Also starts playing a default audio file in a loop.
 *
 * @param aNumber Level number to load.
 */
Level::Level(int aNumber) : itsNb(aNumber), itsMainCharacter(nullptr), itsDoor(nullptr)
{
    itsObstacles = new std::list<Obstacle*>;
    itsEnemies = new std::list<Character*>;
    itsPieces = new std::list<Piece *>;
    itsFlashbackObjects = new list<FlashbackObject *>;

    QString levelFileName;
    if (itsNb == 0)
    {
        levelFileName = ":/level/assets/level/level0.txt";
        setItsLevelWidth(3840);
    }
    else if (itsNb == 2)
    {
        levelFileName = ":/level/assets/level/boss1.txt";
        setItsLevelWidth(1280);
    }
    else if (itsNb == 3)
    {
        levelFileName = ":/level/assets/level/level2.txt";
    }
    else if (itsNb == 4)
    {
        levelFileName = ":/level/assets/level/boss2.txt";
        setItsLevelWidth(1280);
    }
    else if (itsNb == 5)
    {
        levelFileName = ":/level/assets/level/level3.txt";
    }
    else if (itsNb == 6)
    {
        levelFileName = ":/level/assets/level/boss3.txt";
        setItsLevelWidth(1280);
    }
    else
    {
        levelFileName = ":/level/assets/level/level1.txt";
    }

    QFile file(levelFileName);
    if (file.open(QIODevice::ReadOnly | QIODevice::Text))
    {
        QTextStream in(&file);
        while (!in.atEnd()) {
            QString line = in.readLine();
            QStringList parts = line.split(",");
            QString type = parts[0];
            if (type == "MainCharacter")
            {
                int x = parts[1].toInt();
                int y = parts[2].toInt();
                int width = parts[3].toInt();
                int height = parts[4].toInt();
                itsMainCharacter = new MainCharacter(x, y, width, height);
            }
            else if (type == "Companion")
            {
                int x = parts[1].toInt();
                int y = parts[2].toInt();
                int width = parts[3].toInt();
                int height = parts[4].toInt();
                itsCompanion = new Companion(x, y, width, height, itsMainCharacter);
            }
            else if (type == "Obstacle")
            {
                int x = parts[1].toInt();
                int y = parts[2].toInt();
                int width = parts[3].toInt();
                int height = parts[4].toInt();
                itsObstacles->push_back(new Obstacle(x, y, width, height));
            }
            else if (type == "Enemy")
            {
                int x = parts[1].toInt();
                int y = parts[2].toInt();
                int width = parts[3].toInt();
                int height = parts[4].toInt();
                int enemyType = parts[5].toInt();  // Assuming this indicates enemy type
                itsEnemies->push_back(new ShortScope(x, y, width, height, enemyType));
            }
            else if (type == "Piece")
            {
                int x = parts[1].toInt();
                int y = parts[2].toInt();
                int width = parts[3].toInt();
                int height = parts[4].toInt();
                itsPieces->push_back(new Piece(x, y, width, height));
            }
            else if (type == "Door")
            {
                int x = parts[1].toInt();
                int y = parts[2].toInt();
                int width = parts[3].toInt();
                int height = parts[4].toInt();
                itsDoor = new Door(x, y, width, height);
            }
            else if (type == "FlashbackObject")
            {
                int x = parts[1].toInt();
                int y = parts[2].toInt();
                int width = parts[3].toInt();
                int height = parts[4].toInt();
                QString nb = parts[5];
                QString text = parts[6];
                itsFlashbackObjects->push_back(new FlashbackObject(x, y, width, height, nb, text));
            }
            else if (type == "ClassicBoss")
            {
                int x = parts[1].toInt();
                int y = parts[2].toInt();
                int width = parts[3].toInt();
                int height = parts[4].toInt();
                itsClassicBoss = new ClassicBoss(x, y, width, height);
            }
            else if (type == "FinalBoss")
            {
                int x = parts[1].toInt();
                int y = parts[2].toInt();
                int width = parts[3].toInt();
                int height = parts[4].toInt();
                itsFinalBoss = new FinalBoss(x, y, width, height);
            }
            else if (type == "ws" || type == "cs" || type == "nt")
            {
                itsEnemyType = type;
            }
            else
            {
                qDebug() << "Invalid type or incorrect format for line:" << line;
            }
        }
        file.close();
    }
    else
    {
        qDebug() << "Failed to open file" << levelFileName;
    }

    // Create a QMediaPlayer instance
    player = new QMediaPlayer;
    output = new QAudioOutput;

    // Set audio source using URL
    player->setSource(QUrl("qrc:/song/assets/audio/default_song.mp3"));

    player->setAudioOutput(output);
    output->setVolume(1);

    player->setLoops(-1);

    // Start playback
    player->play();

    itsFlashbackObjectNb = itsFlashbackObjects->size();
    itsHUDNb = (itsNb + 1) / 2;
}

/**
 * @brief Destructor of the Level class.
 *
 * Frees dynamically allocated memory for various level elements.
 */
Level::~Level()
{
    delete output;
    delete player;
    delete itsMainCharacter;

    for (Obstacle* obstacle : *itsObstacles)
    {
        delete obstacle;
    }
    delete itsObstacles;

    for (auto it = itsFlashbackObjects->begin(); it != itsFlashbackObjects->end();)
    {
        delete *it;
        it = itsFlashbackObjects->erase(it);
    }
    delete itsFlashbackObjects;

    for (Piece* piece : *itsPieces)
    {
        delete piece;
    }
    delete itsPieces;

    delete itsCompanion;
    delete itsDoor;
    delete itsClassicBoss;
    delete itsFinalBoss;
}

/**
 * @brief Get the list of obstacles in the level.
 *
 * @return std::list<Obstacle*>* List of obstacles.
 */
std::list<Obstacle *> *Level::getItsObstacles() const
{
    return itsObstacles;
}

/**
 * @brief Get the list of pieces in the level.
 *
 * @return std::list<Piece*>* List of pieces.
 */
std::list<Piece *> *Level::getItsPieces() const
{
    return itsPieces;
}

/**
 * @brief Get the list of flashback objects in the level.
 *
 * @return std::list<FlashbackObject*>* List of flashback objects.
 */
std::list<FlashbackObject *> *Level::getItsFlashbackObjects() const
{
    return itsFlashbackObjects;
}

/**
 * @brief Get the number of flashback objects in the level.
 *
 * @return int Number of flashback objects.
 */
int Level::getItsFlashbackObjectNb()
{
    return itsFlashbackObjectNb;
}

/**
 * @brief Get the list of enemies in the level.
 *
 * @return std::list<Character*>* List of enemies.
 */
std::list<Character *> *Level::getItsEnemies()
{
    return itsEnemies;
}

/**
 * @brief Get the companion of the main character in the level.
 *
 * @return Companion* Companion of the main character.
 */
Companion *Level::getItsCompanion()
{
    return itsCompanion;
}

/**
 * @brief Get the main character of the level.
 *
 * @return MainCharacter* Main character of the level.
 */
MainCharacter *Level::getItsMainCharacter()
{
    return itsMainCharacter;
}

/**
 * @brief Get the classic boss of the level, if any.
 *
 * @return ClassicBoss* Classic boss of the level.
 */
ClassicBoss *Level::getItsBoss()
{
    return itsClassicBoss;
}

/**
 * @brief Get the final boss of the level, if any.
 *
 * @return FinalBoss* Final boss of the level.
 */
FinalBoss *Level::getItsFinalBoss()
{
    return itsFinalBoss;
}

/**
 * @brief Set the list of enemies in the level.
 *
 * @param enemies New list of enemies to set.
 */
void Level::setItsEnemies(std::list<Character *> *enemies)
{
    itsEnemies = enemies;
}

/**
 * @brief Set the list of obstacles in the level.
 *
 * @param obstacles New list of obstacles to set.
 */
void Level::setItsObstacles(std::list<Obstacle *> *obstacles)
{
    itsObstacles = obstacles;
}

/**
 * @brief Set the list of pieces in the level.
 *
 * @param pieces New list of pieces to set.
 */
void Level::setItsPieces(std::list<Piece *> *pieces)
{
    itsPieces = pieces;
}

/**
 * @brief Set the list of flashback objects in the level.
 *
 * @param flashbackObjects New list of flashback objects to set.
 */
void Level::setItsFlashbackObjects(std::list<FlashbackObject *> *flashbackObjects)
{
    itsFlashbackObjects = flashbackObjects;
}

/**
 * @brief Set the main character of the level.
 *
 * @param mainCharacter New main character to set.
 */
void Level::setItsMainCharacter(MainCharacter *mainCharacter)
{
    itsMainCharacter = mainCharacter;
}

/**
 * @brief Set the width of the level.
 *
 * @param width New width of the level to set.
 */
void Level::setItsLevelWidth(int width)
{
    itsLevelWidth = width;
}

/**
 * @brief Set the classic boss of the level.
 *
 * @param boss New classic boss to set.
 */
void Level::setItsBoss(ClassicBoss *boss)
{
    itsClassicBoss = boss;
}

/**
 * @brief Get the width of the level.
 *
 * @return int Width of the level.
 */
int Level::getItsLevelWidth()
{
    return itsLevelWidth;
}

/**
 * @brief Get the height of the level.
 *
 * @return int Height of the level.
 */
int Level::getItsLevelHeight()
{
    return itsLevelHeight;
}

/**
 * @brief Get the door object representing the level's exit.
 *
 * @return Door* Door object representing the level's exit.
 */
Door *Level::getItsDoor() const
{
    return itsDoor;
}

/**
 * @brief Get the level number.
 *
 * @return int Level number.
 */
int Level::getItsNb()
{
    return itsNb;
}

/**
 * @brief Set the enemy type for the level.
 *
 * @param type Enemy type to set.
 */
void Level::setItsEnemyType(QString type)
{
    itsEnemyType = type;
}

/**
 * @brief Get the enemy type for the level.
 *
 * @return QString Enemy type.
 */
QString Level::getItsEnemyType()
{
    return itsEnemyType;
}

/**
 * @brief Get the HUD (Heads-Up Display) number for the level.
 *
 * @return int HUD number.
 */
int Level::getItsHUDNb()
{
    return itsHUDNb;
}

/**
 * @brief Get the QMediaPlayer instance used for level audio playback.
 *
 * @return QMediaPlayer* QMediaPlayer instance for audio playback.
 */
QMediaPlayer *Level::getPlayer()
{
    return player;
}

/**
 * @brief Stop playing the level's song.
 */
void Level::songMuted()
{
    player->stop();
}

/**
 * @brief Start playing the level's song.
 */
void Level::songStart()
{
    player->play();
}
