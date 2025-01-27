/**
 * @file gui.h
 * @brief Definition of the GUI class.
 */

#ifndef GUI_H
#define GUI_H

#include <QLabel>
#include <QWidget>
#include <QPainter>
#include <QKeyEvent>
#include <QTimer>
#include <QPixmap>
#include <QMap>
#include <QString>
#include <QStackedLayout>
#include <cstdlib>
#include <ctime>
#include "game.h"
#include "optionsmenu.h"
#include "pausemenu.h"

/**
 * @brief Class representing the graphical user interface (GUI) for the game.
 *
 * Inherits from QWidget to provide a custom GUI for the game.
 */
class GUI : public QWidget
{
    Q_OBJECT

    Game* itsGame; /**< Pointer to the game object. */
    QTimer* itsTimer; /**< Pointer to the timer for updating the GUI. */
    QPainter painter; /**< Painter object used for rendering graphics. */
    bool keySpacePressed = false; /**< Flag indicating whether the space key is pressed. */
    bool keyUpPressed = false; /**< Flag indicating whether the up key is pressed. */
    int counterDrawMainCharacter = 0; /**< Counter for drawing the main character. */
    int counterDrawEnemies = 0; /**< Counter for drawing enemies. */
    int counterAttack = 0; /**< Counter for attack animations. */
    int counterCompanion = 0; /**< Counter for drawing the companion. */
    int gameOver = 0; /**< Game over state. */
    bool previousDirectionRightMC = false; /**< Flag indicating the previous direction of the main character. */
    QPixmap backgroundPixmap; /**< Pixmap for the background image. */
    QPixmap gameOverPixmap; /**< Pixmap for the game over screen. */
    QPixmap doorPixmap; /**< Pixmap for the door image. */
    QMap<QString, QPixmap> characterPixmaps; /**< Map of character image file names to QPixmaps. */
    QMap<QString, QPixmap> backgroundPixmaps; /**< Map of background image file names to QPixmaps. */
    QMap<QString, QPixmap> elementPixmaps; /**< Map of element image file names to QPixmaps. */
    QLabel* itsFlashbackBackground; /**< Pointer to the flashback background label. */
    QLabel* itsFlashbackText; /**< Pointer to the flashback text label. */
    QLabel* gameOverLabel; /**< Label for displaying the game over message. */
    QRect restartButtonRect; /**< Rectangle representing the restart game button. */
    bool isPaused; /**< Flag indicating whether the game is paused. */
    PauseMenu *pauseMenu; /**< Pointer to the pause menu object. */
    OptionsMenu *optionsMenu; /**< Pointer to the options menu object. */
    int attackFrameCounter; /**< Counter for attack animation frames. */
    bool isAttacking; /**< Flag indicating whether the main character is currently attacking. */
    QVector<QPixmap> loadingPixmaps; /**< Vector of loading animation frames. */
    QMap<QString, QPixmap> doorPixmaps; /**< Map of door image file names to QPixmaps. */
    bool isLoading; /**< Flag indicating whether a loading animation is in progress. */
    int frameIndex; /**< Index of the current frame in the loading animation. */
    QTimer* loadingTimer; /**< Timer for controlling the loading animation. */
    int frameCounter = 0; /**< Counter for frame updates. */
    bool firstLoad; /**< Flag indicating whether it's the first load of the game. */
    bool actionInProgress; /**< Flag indicating whether an action is currently in progress. */

public:
    /**
     * @brief Constructor to initialize the GUI.
     *
     * @param aGame Pointer to the game object.
     * @param parent Parent widget, default is nullptr.
     */
    GUI(Game* aGame, QWidget *parent = nullptr);

    /**
     * @brief Destructor to clean up resources.
     */
    ~GUI();

protected:
    /**
     * @brief Event handler for painting the GUI.
     *
     * @param event Paint event.
     */
    void paintEvent(QPaintEvent *event) override;

    /**
     * @brief Event handler for key press events.
     *
     * @param event Key event.
     */
    void keyPressEvent(QKeyEvent *event) override;

    /**
     * @brief Event handler for key release events.
     *
     * @param event Key event.
     */
    void keyReleaseEvent(QKeyEvent *event) override;

    /**
     * @brief Event handler for mouse press events.
     *
     * @param event Mouse event.
     */
    void mousePressEvent(QMouseEvent *event) override;

private:
    /**
     * @brief Loads images used in the GUI.
     */
    void loadImages();

    /**
     * @brief Draws the characters in the game.
     *
     * @param aPainter Pointer to the painter object used for drawing.
     */
    void drawCharacters(QPainter * aPainter);

    /**
     * @brief Draws the main character in the game.
     *
     * @param aPainter Pointer to the painter object used for drawing.
     */
    void drawMainCharacter(QPainter * aPainter);

    /**
     * @brief Draws the obstacles in the game.
     *
     * @param aPainter Pointer to the painter object used for drawing.
     */
    void drawObstacles(QPainter * aPainter);

    /**
     * @brief Draws the boss differents character in the game.
     *
     * @param aPainter Pointer to the painter object used for drawing.
     */
    void drawBoss(QPainter *aPainter);

    /**
     * @brief Draws the companion character in the game.
     *
     * @param aPainter Pointer to the painter object used for drawing.
     */
    void drawCompanion(QPainter * aPainter);

    /**
     * @brief Draws the flashback objects in the game.
     *
     * @param aPainter Pointer to the painter object used for drawing.
     */
    void drawFlashbackObjects(QPainter * aPainter);

    /**
     * @brief Draws the collectible pieces in the game.
     *
     * @param aPainter Pointer to the painter object used for drawing.
     */
    void drawPieces(QPainter * aPainter);

    /**
     * @brief Draws the HUD (Heads-Up Display) in the game.
     *
     * @param aPainter Pointer to the painter object used for drawing.
     */
    void drawHUD(QPainter * aPainter);

    /**
     * @brief Draws the main character's attack animation.
     *
     * @param painter Pointer to the painter object used for drawing.
     */
    void drawAttackMC(QPainter *painter);

    /**
     * @brief Draws the main character in a dead state.
     *
     * @param painter Pointer to the painter object used for drawing.
     */
    void drawDeadMainCharacter(QPainter *painter);

    /**
     * @brief Displays the game over screen.
     */
    void displayGameOverScreen();

    /**
     * @brief Updates the background image.
     */
    void updateBackground();

    /**
     * @brief Draws the door in the game.
     *
     * @param aPainter Pointer to the painter object used for drawing.
     */
    void drawDoor(QPainter *aPainter);

    /**
     * @brief Restarts the game.
     */
    void restartGame();

    /**
     * @brief Handles the action to continue the game.
     */
    void handleContinueGame();

    /**
     * @brief Shows the options menu.
     */
    void showOptionsMenu();

private slots:
    /**
     * @brief Slot for drawing flashback text.
     *
     * @param aText The text to display in the flashback.
     */
    void drawFlashbackText(QString aText);

    /**
     * @brief Slot for hiding flashback text.
     */
    void hideFlashbackText();
};

#endif // GUI_H
