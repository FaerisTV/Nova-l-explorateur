#include "gui.h"
#include <QApplication>
#include "launchmenu.h"

/**
 * @brief Function to restart music playback.
 *
 * Restarts music playback if the player is in StoppedState.
 *
 * @param player QMediaPlayer instance used for music playback.
 */
void restartMusic(QMediaPlayer *player)
{
    if (player->mediaStatus() == QMediaPlayer::StoppedState)
    {
        player->setPosition(0);
        player->play();
    }
}

/**
 * @brief Main function of the program.
 *
 * Initializes the application and launches the game's startup menu.
 *
 * @param argc Number of arguments passed to the program.
 * @param argv Array of arguments passed to the program.
 * @return int Exit code of the program.
 */
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Game nova;
    GUI myGUI(&nova);
    LaunchMenu menu;

    // Connect startGameRequested signal from LaunchMenu to show GUI and close menu
    QObject::connect(&menu, &LaunchMenu::startGameRequested, [&]()
    {
        myGUI.show();
        menu.close();
    });

    menu.show(); // Show the LaunchMenu

    return a.exec(); // Start Qt event loop
}
