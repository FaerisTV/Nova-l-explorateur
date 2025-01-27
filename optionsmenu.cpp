/**
 * @file OptionsMenu.h
 * @brief Definition of the OptionsMenu class.
 */

#include "OptionsMenu.h"
#include "QPainter"
#include <QDebug>

/**
 * @brief Constructor for OptionsMenu class.
 * @param parent The parent QWidget.
 */
OptionsMenu::OptionsMenu(QWidget *parent)
    : QWidget(parent),
    itsLevel(new Level(1))  // Initialize itsLevel with a Level object
{
    // Change the imagePath below to match the location of your image
    QString imagePath = ":/menu/assets/game_style/optionMenu.png";  // Use absolute path
    background.load(imagePath);  // Load background image

    // Set window size to fit the resized image
    int imageWidth = 1280;  // Desired absolute width
    int imageHeight = 720;   // Desired absolute height
    setFixedSize(imageWidth, imageHeight);

    QVBoxLayout *layout = new QVBoxLayout(this);  // Create vertical layout

    layout->addWidget(musicVolumeSlider);  // Add music volume slider to layout
    layout->addWidget(soundEffectsVolumeSlider);  // Add sound effects volume slider to layout

    musicVolumeSlider = new QSlider(Qt::Horizontal, this);  // Create horizontal music volume slider
    soundEffectsVolumeSlider = new QSlider(Qt::Horizontal, this);  // Create horizontal sound effects volume slider

    // Position and resize the music volume slider
    musicVolumeSlider->setFixedWidth(230);
    musicVolumeSlider->move(540, 365);  // Move to specified position
    musicVolumeSlider->setRange(0, 100);  // Set range from 0 to 100
    musicVolumeSlider->setValue(50);  // Set initial value

    // Position and resize the sound effects volume slider
    soundEffectsVolumeSlider->setFixedWidth(230);
    soundEffectsVolumeSlider->move(540, 510);  // Move to specified position
    soundEffectsVolumeSlider->setRange(0, 100);  // Set range from 0 to 100
    soundEffectsVolumeSlider->setValue(50);  // Set initial value

    // Set stylesheet for sliders
    QString styleSheet = "QSlider::groove:horizontal {"
                         "    height: 12px;"
                         "    width: 460px;"
                         "    background: cyan;"
                         "    margin: 8px;"
                         "    border: 2px solid black;"
                         "    border-radius: 12px;"
                         "}"
                         "QSlider::handle:horizontal {"
                         "    margin: -5px 0;"
                         "    image: url(:/menu/assets/game_style/cursor.png);"
                         "    border-radius: 6px;"
                         "}";
    musicVolumeSlider->setStyleSheet(styleSheet);  // Apply stylesheet to music volume slider
    soundEffectsVolumeSlider->setStyleSheet(styleSheet);  // Apply stylesheet to sound effects volume slider

    // Connect signals to slots (commented out as it's not currently used)
    //connect(musicVolumeSlider, SIGNAL(valueChanged(int)), this, SLOT(onMusicVolumeChanged(int)));
    //connect(soundEffectsVolumeSlider, SIGNAL(valueChanged(int)), this, SLOT(onSoundEffectsVolumeChanged(int)));
}

/**
 * @brief Paint event handler for OptionsMenu.
 * @param event Paint event object.
 */
void OptionsMenu::paintEvent(QPaintEvent *event)
{
    QPainter painter(this);  // Create QPainter for this widget
    QPixmap scaledBackground = background.scaled(1280, 720, Qt::IgnoreAspectRatio, Qt::SmoothTransformation);  // Scale background image
    painter.drawPixmap(0, 0, scaledBackground);  // Draw scaled background pixmap at (0, 0)
}
