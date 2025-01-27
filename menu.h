#ifndef MENU_H
#define MENU_H

#include <QPushButton>

/**
 * @brief The Menu class represents the main menu of the game.
 */
class Menu
{
    QPushButton itsOptionsButton; /**< Button for accessing options. */
    QPushButton itsQuitButton; /**< Button for quitting the game. */
    const QString itsLogoFile; /**< File path for the logo image. */

public:
    /**
     * @brief Constructor to initialize the Menu.
     */
    Menu();

    /**
     * @brief Displays the options menu.
     */
    void options();

    /**
     * @brief Quits the game.
     */
    void quit();
};

#endif // MENU_H
