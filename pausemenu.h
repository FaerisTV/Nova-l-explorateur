#ifndef PAUSEMENU_H
#define PAUSEMENU_H

#include <QWidget>
#include <QPixmap>
#include <QRect>
#include <QPainter>
#include <QMouseEvent>
#include <QApplication>


/**
 * @brief The PauseMenu class represents the pause menu of the game.
 *
 * Inherits from the Menu class.
 */
class PauseMenu : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor to initialize the pause menu.
     *
     * @param parent Pointer to the parent widget, default is nullptr
     */
    PauseMenu(QWidget *parent = nullptr);

signals:
    /**
     * @brief Signal emitted when the user requests to start a new game.
     */
    void continueGameRequested();

    /**
     * @brief Signal emitted when the user requests to load a saved game.
     */
    void loadGameRequested();

    void optionsRequested();

protected:
    /**
     * @brief Event handler for painting the launch menu.
     *
     * @param event Paint event
     */
    void paintEvent(QPaintEvent *event) override;

    /**
     * @brief Event handler for handling mouse press events.
     *
     * @param event Mouse event
     */
    void mousePressEvent(QMouseEvent *event) override;

private:
    QPixmap background; ///< Background image for the launch menu
    QRect continueButtonRect; ///< Rectangle representing the start game button
    QRect optionButtonRect; ///< Rectangle representing the options button
    QRect saveButtonRect; ///< Rectangle representing the load game button
    QRect quitButtonRect; ///< Rectangle representing the quit game button

    /**
     * @brief Handles the click event for the start game button.
     */
    void handleContinueButtonClick();

    /**
     * @brief Handles the click event for the load game button.
     */
    void handleSaveButtonClick();

    /**
     * @brief Handles the click event for the options button.
     */
    void handleOptionButtonClick();

    /**
     * @brief Handles the click event for the quit button.
     */
    void handleQuitButtonClick();
};

#endif // PAUSEMENU_H
