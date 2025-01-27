#include "pausemenu.h"


PauseMenu::PauseMenu(QWidget *parent) : QWidget(parent) {

    // Changez le chemin d'accès ci-dessous pour correspondre à l'emplacement de votre image
    QString imagePath = ":/menu/assets/game_style/pauseMenu169.png";  // Utilisez le chemin absolu
    background.load(imagePath);

    // Définissez la taille de la fenêtre pour s'adapter à l'image redimensionnée
    int imageWidth = 1280;  // Largeur absolue souhaitée
    int imageHeight = 720; // Hauteur absolue souhaitée

    setFixedSize(imageWidth, imageHeight);

    // Définissez les zones cliquables des boutons en fonction de la nouvelle taille
    continueButtonRect = QRect(510, 280, 280, 70); // Ajustez ces valeurs
    saveButtonRect = QRect(510, 390, 280, 70); // Ajustez ces valeurs
    optionButtonRect = QRect(510, 480, 280, 70); // Ajustez ces valeurs
    quitButtonRect = QRect(510, 595, 280, 70); // Ajustez ces valeurs
}

void PauseMenu::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);
    QPixmap scaledBackground = background.scaled(1280, 720, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);
    painter.drawPixmap(0, 0, scaledBackground);
}

void PauseMenu::mousePressEvent(QMouseEvent *event)
{
    QPoint clickPosition = event->pos();

    if (continueButtonRect.contains(clickPosition))
    {
        handleContinueButtonClick();
    }
    else if (optionButtonRect.contains(clickPosition))
    {
        handleOptionButtonClick();
    }
    else if (quitButtonRect.contains(clickPosition))
    {
        handleQuitButtonClick();
    }
}

void PauseMenu::handleContinueButtonClick()
{
    emit continueGameRequested();
}

void PauseMenu::handleSaveButtonClick()
{
    QApplication::quit();
}

void PauseMenu::handleOptionButtonClick()
{
    emit optionsRequested();
}

void PauseMenu::handleQuitButtonClick()
{
    QApplication::quit();
}
