#ifndef OPTIONSMENU_H
#define OPTIONSMENU_H

#include "level.h"
#include <QWidget>
#include <QSlider>
#include <QVBoxLayout>
#include <QLabel>
#include <QObject>

/**
 * @brief The OptionsMenu class provides a widget for configuring game options.
 */
class OptionsMenu : public QWidget
{
    Q_OBJECT

public:
    /**
     * @brief Constructor for OptionsMenu class.
     * @param parent The parent QWidget.
     */
    OptionsMenu(QWidget *parent = nullptr);

    /**
     * @brief Overridden paint event handler to draw the background image.
     * @param event Paint event object.
     */
    void paintEvent(QPaintEvent *event) override;

private:
    QPixmap background; ///< Background image for the options menu.
    QSlider *musicVolumeSlider; ///< Slider for adjusting music volume.
    QSlider *soundEffectsVolumeSlider; ///< Slider for adjusting sound effects volume.
    Level *itsLevel; ///< Pointer to the current game level.
};

#endif // OPTIONSMENU_H
