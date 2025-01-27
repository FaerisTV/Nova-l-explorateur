#ifndef LAUNCHMENU_H
#define LAUNCHMENU_H

#include <QWidget>
#include <QPixmap>
#include <QRect>

/**
 * @brief The LaunchMenu class represents the menu displayed when the game is launched.
 *
 * Inherits from QWidget to provide a custom user interface for launching the game.
 */
class LaunchMenu : public QWidget {
    Q_OBJECT

public:
    /**
     * @brief Constructor to initialize the launch menu.
     *
     * @param parent Pointer to the parent widget, default is nullptr
     */
    LaunchMenu(QWidget *parent = nullptr);

signals:
    /**
     * @brief Signal emitted when the user requests to start a new game.
     */
    void startGameRequested();

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
    QRect startButtonRect; ///< Rectangle representing the start game button
    QRect optionButtonRect; ///< Rectangle representing the options button
    QRect loadButtonRect; ///< Rectangle representing the load game button

    /**
     * @brief Handles the click event for the start game button.
     */
    void handleStartButtonClick();

    /**
     * @brief Handles the click event for the load game button.
     */
    void handleLoadButtonClick();

    /**
     * @brief Handles the click event for the options button.
     */
    void handleOptionButtonClick();

    /**
     * @brief Handles the click event for the quit button.
     */
    void handleQuitButtonClick();
};

#endif // LAUNCHMENU_H
