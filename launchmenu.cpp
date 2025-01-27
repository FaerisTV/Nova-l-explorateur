#include "LaunchMenu.h"
#include <QPainter>
#include <QMouseEvent>
#include <QDebug>
#include <QApplication>

/**
 * @brief Constructeur de la classe LaunchMenu.
 *
 * Initialise l'interface du menu de lancement avec une image de fond chargée depuis un fichier.
 * Définit la taille de la fenêtre et les zones cliquables des boutons.
 *
 * @param parent Widget parent de l'interface.
 */
LaunchMenu::LaunchMenu(QWidget *parent) : QWidget(parent) {
    // Changez le chemin d'accès ci-dessous pour correspondre à l'emplacement de votre image
    QString imagePath = ":/menu/assets/game_style/gameMenu169.png";  // Utilisez le chemin absolu
    background.load(imagePath);

    // Vérifiez si l'image a été chargée correctement
    if (background.isNull())
    {
        qWarning("Failed to load background image");
    }
    // Définissez la taille de la fenêtre pour s'adapter à l'image redimensionnée
    int imageWidth = 1280;  // Largeur absolue souhaitée
    int imageHeight = 720; // Hauteur absolue souhaitée

    setFixedSize(imageWidth, imageHeight);

    // Définissez les zones cliquables des boutons en fonction de la nouvelle taille
    startButtonRect = QRect(510, 280, 280, 70); // Ajustez ces valeurs
    loadButtonRect = QRect(510, 390, 280, 70); // Ajustez ces valeurs
    optionButtonRect = QRect(510, 480, 280, 70); // Ajustez ces valeurs
    loadButtonRect = QRect(510, 595, 280, 70); // Ajustez ces valeurs
}

/**
 * @brief Redessine l'interface du menu de lancement.
 *
 * @param event Événement de redessin.
 */
void LaunchMenu::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap scaledBackground = background.scaled(1280, 720, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(0, 0, scaledBackground);
}

/**
 * @brief Gère l'événement de clic de la souris.
 *
 * Vérifie la position du clic et déclenche les actions correspondantes pour les boutons.
 *
 * @param event Événement de clic de la souris.
 */
void LaunchMenu::mousePressEvent(QMouseEvent *event) {
    QPoint clickPosition = event->pos();

    if (startButtonRect.contains(clickPosition)) {
        handleStartButtonClick();
    } else if (loadButtonRect.contains(clickPosition)) {
        handleLoadButtonClick();
    }
}

/**
 * @brief Gère le clic sur le bouton "Démarrer".
 *
 * Émet un signal pour démarrer le jeu.
 */
void LaunchMenu::handleStartButtonClick()
{
    emit startGameRequested();
}

/**
 * @brief Gère le clic sur le bouton "Charger".
 *
 * Quitte l'application.
 */
void LaunchMenu::handleLoadButtonClick() {
    QApplication::quit();
}

/**
 * @brief Gère le clic sur le bouton "Options".
 *
 * Émet un signal pour afficher les options du jeu.
 */
void LaunchMenu::handleOptionButtonClick()
{
    emit optionsRequested();
}

/**
 * @brief Gère le clic sur le bouton "Quitter".
 *
 * Quitte l'application.
 */
void LaunchMenu::handleQuitButtonClick()
{
    QApplication::quit();
}
