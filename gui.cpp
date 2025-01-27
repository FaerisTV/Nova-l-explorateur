#include "gui.h"

/**
     * @brief Constructor to initialize the GUI.
     *
     * @param aGame Pointer to the game object.
     * @param parent Parent widget, default is nullptr.
*/
GUI::GUI(Game* aGame, QWidget *parent) : QWidget(parent), itsGame(aGame)
{
    setFixedSize(1280, 720);

    itsTimer = new QTimer(this);
    connect(itsTimer, SIGNAL(timeout()), this, SLOT(update()));
    itsTimer->start(30); // Mise à jour toutes les 5 millisecondes

    // Initialisation du générateur de nombres aléatoires
    srand(static_cast<unsigned int>(time(nullptr)));

    loadImages(); // Charger toutes les images nécessaires pour l'animation

    gameOverLabel = new QLabel(this);
    gameOverLabel->setAlignment(Qt::AlignCenter);
    gameOverLabel->hide();

    pauseMenu = new PauseMenu(this); // Vous pouvez également utiliser un parent approprié ici
    pauseMenu->hide(); // Masquer le menu de pause au démarrage

    optionsMenu = new OptionsMenu(this); // Vous pouvez également utiliser un parent approprié ici
    optionsMenu->hide(); // Masquer le menu de pause au démarrage

    isLoading = false; // Initialisation de l'état de chargement
    frameIndex = 0;
    itsFlashbackBackground = new QLabel(this);
    itsFlashbackBackground->setAlignment(Qt::AlignCenter);
    itsFlashbackBackground->hide();

    itsFlashbackText = new QLabel(this);
    itsFlashbackText->setAlignment(Qt::AlignCenter);
    itsFlashbackText->setStyleSheet("color: blue; font-size: 24px; padding: 10px;");
    itsFlashbackText->hide();

    // Connecter le signal continueGameRequested du pauseMenu à la fonction handleContinueGame de GUI
    connect(pauseMenu, &PauseMenu::continueGameRequested, this, &GUI::handleContinueGame);
    
    connect(pauseMenu, &PauseMenu::optionsRequested, this, &GUI::showOptionsMenu);
    connect(itsGame, &Game::gameOverScreenRequested, this, &GUI::displayGameOverScreen);
    connect(itsGame, &Game::objectCollected, this, &GUI::drawFlashbackText);
}
/**
     * @brief Destructor to clean up resources.
*/
GUI::~GUI()
{
    delete itsTimer;
    delete itsFlashbackText;
    delete itsFlashbackBackground;
    delete gameOverLabel;
}
/**
     * @brief Loads images used in the GUI.
*/
void GUI::loadImages()
{
    backgroundPixmaps["level_0"] = QPixmap(":/map/assets/map/map0.png");
    backgroundPixmaps["level_1"] = QPixmap(":/map/assets/map/map1.png");
    backgroundPixmaps["boss_1"] = QPixmap(":/map/assets/map/boss1.png");
    backgroundPixmaps["level_2"] = QPixmap(":/map/assets/map/map2.png");
    backgroundPixmaps["boss_2"] = QPixmap(":/map/assets/map/boss2.png");
    backgroundPixmaps["level_3"] = QPixmap(":/map/assets/map/map3.png");
    backgroundPixmaps["boss_3"] = QPixmap(":/map/assets/map/boss3.png");

    
    if(itsGame->getItsLevel()->getItsEnemyType() == "ws")
    {
        // Chargement des images pour les animations du personnage principal
        characterPixmaps["main_walk1"] = QPixmap(":/déplacements/assets/nova/nova_middle_age/walk/nova_middle_age_walk1.png");
        characterPixmaps["main_walk2"] = QPixmap(":/déplacements/assets/nova/nova_middle_age/walk/nova_middle_age_walk2.png");
        characterPixmaps["main_walk3"] = QPixmap(":/déplacements/assets/nova/nova_middle_age/walk/nova_middle_age_walk3.png");
        characterPixmaps["main_walk1_reversed"] = QPixmap(":/déplacements/assets/nova/nova_middle_age/walk/nova_middle_age_walk1_reversed.png");
        characterPixmaps["main_walk2_reversed"] = QPixmap(":/déplacements/assets/nova/nova_middle_age/walk/nova_middle_age_walk2_reversed.png");
        characterPixmaps["main_walk3_reversed"] = QPixmap(":/déplacements/assets/nova/nova_middle_age/walk/nova_middle_age_walk3_reversed.png");

        // Chargement des images pour les ennemis
        characterPixmaps["skeleton_walk1"] = QPixmap(":/déplacements/assets/ennemy/skeleton/skeleton_walk1.png");
        characterPixmaps["skeleton_walk2"] = QPixmap(":/déplacements/assets/ennemy/skeleton/skeleton_walk2.png");
        characterPixmaps["skeleton_walk3"] = QPixmap(":/déplacements/assets/ennemy/skeleton/skeleton_walk3.png");
        characterPixmaps["skeleton_walk1_reversed"] = QPixmap(":/déplacements/assets/ennemy/skeleton/skeleton_walk1_reversed.png");
        characterPixmaps["skeleton_walk2_reversed"] = QPixmap(":/déplacements/assets/ennemy/skeleton/skeleton_walk2_reversed.png");
        characterPixmaps["skeleton_walk3_reversed"] = QPixmap(":/déplacements/assets/ennemy/skeleton/skeleton_walk3_reversed.png");

        characterPixmaps["wolf_walk1"] = QPixmap(":/déplacements/assets/ennemy/wicked_wolf/wolf_run_1.png");
        characterPixmaps["wolf_walk2"] = QPixmap(":/déplacements/assets/ennemy/wicked_wolf/wolf_run_2.png");
        characterPixmaps["wolf_walk3"] = QPixmap(":/déplacements/assets/ennemy/wicked_wolf/wolf_run_3.png");
        characterPixmaps["wolf_walk1_reversed"] = QPixmap(":/déplacements/assets/ennemy/wicked_wolf/wolf_run_1_reversed.png");
        characterPixmaps["wolf_walk2_reversed"] = QPixmap(":/déplacements/assets/ennemy/wicked_wolf/wolf_run_2_reversed.png");
        characterPixmaps["wolf_walk3_reversed"] = QPixmap(":/déplacements/assets/ennemy/wicked_wolf/wolf_run_3_reversed.png");

        // Chargement des images d'attaques du personnage principal
        characterPixmaps["main_sword_attack1"] = QPixmap(":/attacks/assets/nova/nova_middle_age/attack/main_sword_attack1.png");
        characterPixmaps["main_sword_attack2"] = QPixmap(":/attacks/assets/nova/nova_middle_age/attack/main_sword_attack2.png");
        characterPixmaps["main_sword_attack3"] = QPixmap(":/attacks/assets/nova/nova_middle_age/attack/main_sword_attack3.png");
        characterPixmaps["main_sword_attack3_reversed"] = QPixmap(":/attacks/assets/nova/nova_middle_age/attack/main_sword_attack1_reversed.png");
        characterPixmaps["main_sword_attack2_reversed"] = QPixmap(":/attacks/assets/nova/nova_middle_age/attack/main_sword_attack2_reversed.png");
        characterPixmaps["main_sword_attack3_reversed"] = QPixmap(":/attacks/assets/nova/nova_middle_age/attack/main_sword_attack3_reversed.png");

        // Chargement des images de morts
        characterPixmaps["main_dead"] = QPixmap(":/dead/assets/nova/nova_dead.png");
    }
    if(itsGame->getItsLevel()->getItsEnemyType() == "cs")
    {
        // Chargement des images pour les animations du personnage principal
        characterPixmaps["main_walk1"] = QPixmap(":/déplacements/assets/nova/nova_modern_time/walk/nova_modern_time_walk1.png");
        characterPixmaps["main_walk2"] = QPixmap(":/déplacements/assets/nova/nova_modern_time/walk/nova_modern_time_walk2.png");
        characterPixmaps["main_walk3"] = QPixmap(":/déplacements/assets/nova/nova_modern_time/walk/nova_modern_time_walk3.png");
        characterPixmaps["main_walk1_reversed"] = QPixmap(":/déplacements/assets/nova/nova_modern_time/walk/nova_modern_time_walk1_reversed.png");
        characterPixmaps["main_walk2_reversed"] = QPixmap(":/déplacements/assets/nova/nova_modern_time/walk/nova_modern_time_walk2_reversed.png");
        characterPixmaps["main_walk3_reversed"] = QPixmap(":/déplacements/assets/nova/nova_modern_time/walk/nova_modern_time_walk3_reversed.png");

        // Chargement des images pour les ennemis
        characterPixmaps["soldier_walk1"] = QPixmap(":/déplacements/assets/ennemy/soldier/walk/soldier_walk_1.png");
        characterPixmaps["soldier_walk2"] = QPixmap(":/déplacements/assets/ennemy/soldier/walk/soldier_walk_2.png");
        characterPixmaps["soldier_walk3"] = QPixmap(":/déplacements/assets/ennemy/soldier/walk/soldier_walk_3.png");
        characterPixmaps["soldier_walk1_reversed"] = QPixmap(":/déplacements/assets/ennemy/soldier/walk/soldier_walk_1_reversed.png");
        characterPixmaps["soldier_walk2_reversed"] = QPixmap(":/déplacements/assets/ennemy/soldier/walk/soldier_walk_2_reversed.png");
        characterPixmaps["soldier_walk3_reversed"] = QPixmap(":/déplacements/assets/ennemy/soldier/walk/soldier_walk_3_reversed.png");

        characterPixmaps["canon_walk1"] = QPixmap(":/déplacements/assets/ennemy/canon/walk/canon_walk_1.png");
        characterPixmaps["canon_walk2"] = QPixmap(":/déplacements/assets/ennemy/canon/walk/canon_walk_2.png");
        characterPixmaps["canon_walk3"] = QPixmap(":/déplacements/assets/ennemy/canon/walk/canon_walk_1.png");
        characterPixmaps["canon_walk1_reversed"] = QPixmap(":/déplacements/assets/ennemy/canon/walk/canon_walk_1_reversed.png");
        characterPixmaps["canon_walk2_reversed"] = QPixmap(":/déplacements/assets/ennemy/canon/walk/canon_walk_2_reversed.png");
        characterPixmaps["canon_walk3_reversed"] = QPixmap(":/déplacements/assets/ennemy/canon/walk/canon_walk_1_reversed.png");

        // Chargement des images d'attaques du personnage principal
        characterPixmaps["main_sword_attack1"] = QPixmap(":/attacks/assets/nova/nova_modern_time/attack/nova_modern_time_attack1.png");
        characterPixmaps["main_sword_attack2"] = QPixmap(":/attacks/assets/nova/nova_modern_time/attack/nova_modern_time_attack2.png");
        characterPixmaps["main_sword_attack3"] = QPixmap(":/attacks/assets/nova/nova_modern_time/attack/nova_modern_time_attack3.png");
        characterPixmaps["main_sword_attack1_reversed"] = QPixmap(":/attacks/assets/nova/nova_modern_time/attack/nova_modern_time_attack1_reversed.png");
        characterPixmaps["main_sword_attack2_reversed"] = QPixmap(":/attacks/assets/nova/nova_modern_time/attack/nova_modern_time_attack2_reversed.png");
        characterPixmaps["main_sword_attack3_reversed"] = QPixmap(":/attacks/assets/nova/nova_modern_time/attack/nova_modern_time_attack3_reversed.png");

        // Chargement des images de morts
        characterPixmaps["main_dead"] = QPixmap(":/dead/assets/nova/nova_dead.png");
    }
    if(itsGame->getItsLevel()->getItsEnemyType() == "nt")
    {
        // Chargement des images pour les animations du personnage principal
        characterPixmaps["main_walk1"] = QPixmap(":/déplacements/assets/nova/nova_futurist/walk/nova_futurist_walk1.png");
        characterPixmaps["main_walk2"] = QPixmap(":/déplacements/assets/nova/nova_futurist/walk/nova_futurist_walk2.png");
        characterPixmaps["main_walk3"] = QPixmap(":/déplacements/assets/nova/nova_futurist/walk/nova_futurist_walk3.png");
        characterPixmaps["main_walk1_reversed"] = QPixmap(":/déplacements/assets/nova/nova_futurist/walk/nova_futurist_walk1_reversed.png");
        characterPixmaps["main_walk2_reversed"] = QPixmap(":/déplacements/assets/nova/nova_futurist/walk/nova_futurist_walk2_reversed.png");
        characterPixmaps["main_walk3_reversed"] = QPixmap(":/déplacements/assets/nova/nova_futurist/walk/nova_futurist_walk3_reversed.png");

        // Chargement des images pour les ennemis
        characterPixmaps["nautilus_walk1"] = QPixmap(":/déplacements/assets/ennemy/nautilus/walk/nautilus_walk_1.png");
        characterPixmaps["nautilus_walk2"] = QPixmap(":/déplacements/assets/ennemy/nautilus/walk/nautilus_walk_2.png");
        characterPixmaps["nautilus_walk3"] = QPixmap(":/déplacements/assets/ennemy/nautilus/walk/nautilus_walk_3.png");
        characterPixmaps["nautilus_walk1_reversed"] = QPixmap(":/déplacements/assets/ennemy/nautilus/walk/nautilus_walk_1_reversed.png");
        characterPixmaps["nautilus_walk2_reversed"] = QPixmap(":/déplacements/assets/ennemy/nautilus/walk/nautilus_walk_2_reversed.png");
        characterPixmaps["nautilus_walk3_reversed"] = QPixmap(":/déplacements/assets/ennemy/nautilus/walk/nautilus_walk_3_reversed.png");

        characterPixmaps["turret_walk1"] = QPixmap(":/déplacements/assets/ennemy/turret/walk/turret_walk1_reversed.png");
        characterPixmaps["turret_walk2"] = QPixmap(":/déplacements/assets/ennemy/turret/walk/turret_walk2_reversed.png");
        characterPixmaps["turret_walk3"] = QPixmap(":/déplacements/assets/ennemy/turret/walk/turret_walk3_reversed.png");
        characterPixmaps["turret_walk1_reversed"] = QPixmap(":/déplacements/assets/ennemy/turret/walk/turret_walk1.png");
        characterPixmaps["turret_walk2_reversed"] = QPixmap(":/déplacements/assets/ennemy/turret/walk/turret_walk2.png");
        characterPixmaps["turret_walk3_reversed"] = QPixmap(":/déplacements/assets/ennemy/turret/walk/turret_walk3.png");

        // Chargement des images d'attaques du personnage principal
        characterPixmaps["main_sword_attack1"] = QPixmap(":/attacks/assets/nova/nova_futurist/attack/nova_futurist_attack1.png");
        characterPixmaps["main_sword_attack2"] = QPixmap(":/attacks/assets/nova/nova_futurist/attack/nova_futurist_attack1.png");
        characterPixmaps["main_sword_attack3"] = QPixmap(":/attacks/assets/nova/nova_futurist/attack/nova_futurist_attack1.png");
        characterPixmaps["main_sword_attack1_reversed"] = QPixmap(":/attacks/assets/nova/nova_futurist/attack/nova_futurist_attack1_reversed.png");
        characterPixmaps["main_sword_attack2_reversed"] = QPixmap(":/attacks/assets/nova/nova_futurist/attack/nova_futurist_attack2_reversed.png");
        characterPixmaps["main_sword_attack3_reversed"] = QPixmap(":/attacks/assets/nova/nova_futurist/attack/nova_futurist_attack3_reversed.png");

        // Chargement des images de morts
        characterPixmaps["main_dead"] = QPixmap(":/dead/assets/nova/nova_dead.png");
    }

    // Chargement des images pour les animations du companion
    characterPixmaps["companion_walk1"] = QPixmap(":/déplacements/assets/sparkle/sparke_fly_1.png"); //mouvement vers la droite
    characterPixmaps["companion_walk2"] = QPixmap(":/déplacements/assets/sparkle/sparkle_fly_2.png"); //mouvement vers la droite
    characterPixmaps["companion_walk1_reversed"] = QPixmap(":/déplacements/assets/sparkle/sparkle_fly_1_reversed.png");
    characterPixmaps["companion_walk2_reversed"] = QPixmap(":/déplacements/assets/sparkle/sparkle_fly_2_reversed.png");

    // Chargement des images des boss
    characterPixmaps["chevalry"] = QPixmap(":/attacks/assets/ennemy/chevalry/chevalry.png");
    characterPixmaps["chevalry_dead"] = QPixmap(":/attacks/assets/ennemy/chevalry/chevalry_dead.png");
    characterPixmaps["sword_vertical"] = QPixmap(":/attacks/assets/ennemy/chevalry/sword_vertical.png");
    characterPixmaps["sword_horizontal"] = QPixmap(":/attacks/assets/ennemy/chevalry/sword_horizontal.png");
    characterPixmaps["ghost_fly_1_reversed"] = QPixmap(":/déplacements/assets/ennemy/ghost/ghost_fly_1_reversed.png");
    characterPixmaps["ghost_dead"] = QPixmap(":/déplacements/assets/ennemy/ghost/ghost_dead.png");
    characterPixmaps["ghost_fly_2_reversed"] = QPixmap(":/déplacements/assets/ennemy/ghost/ghost_fly_2_reversed.png");
    characterPixmaps["little_fantome_walk_1"] = QPixmap(":/déplacements/assets/ennemy/ghost/little_fantome_walk_1.png");
    characterPixmaps["little_fantome_walk_2"] = QPixmap(":/déplacements/assets/ennemy/ghost/little_fantome_walk_2.png");

    characterPixmaps["asterios_walk1"] = QPixmap(":/déplacements/assets/asterios/walk/asterios_walk2.png");
    characterPixmaps["asterios_walk2"] = QPixmap(":/déplacements/assets/asterios/walk/asterios_walk3.png");
    characterPixmaps["asterios_walk1_reversed"] = QPixmap(":/déplacements/assets/asterios/walk/asterios_walk2_reversed.png");
    characterPixmaps["asterios_walk2_reversed"] = QPixmap(":/déplacements/assets/asterios/walk/asterios_walk3_reversed.png");
    characterPixmaps["asterios_with_armor_walk1"] = QPixmap(":/déplacements/assets/asterios/walk/asterios_with_armor_walk2.png");
    characterPixmaps["asterios_with_armor_walk2"] = QPixmap(":/déplacements/assets/asterios/walk/asterios_with_armor_walk3.png");
    characterPixmaps["asterios_with_armor_walk1_reversed"] = QPixmap(":/déplacements/assets/asterios/walk/asterios_with_armor_walk2_reversed.png");
    characterPixmaps["asterios_with_armor_walk2_reversed"] = QPixmap(":/déplacements/assets/asterios/walk/asterios_with_armor_walk3_reversed.png");

    // Chargement des images de pieces
    elementPixmaps["pieces1"] = QPixmap(":/hud/assets/hud_elements/piece/piece.png");
    elementPixmaps["victory"] = QPixmap(":/hud/assets/game_style/victory.png");

    doorPixmaps["door_1"] = QPixmap(":/door/assets/door/door1.png");
    doorPixmaps["door_2"] = QPixmap(":/door/assets/door/door2.png");
    doorPixmaps["door_3"] = QPixmap(":/door/assets/door/door3.png");
    doorPixmaps["portal_1"] = QPixmap(":/portal/assets/portal/portail1.png");
    doorPixmaps["portal_2"] = QPixmap(":/portal/assets/portal/portail2.png");

    loadingPixmaps.append(QPixmap(":/ile/assets/ile/ile1.png"));
    loadingPixmaps.append(QPixmap(":/ile/assets/ile/ile2.png"));
    loadingPixmaps.append(QPixmap(":/ile/assets/ile/ile3.png"));
    loadingPixmaps.append(QPixmap(":/ile/assets/ile/ile4.png"));
    loadingPixmaps.append(QPixmap(":/ile/assets/ile/ile5.png"));
    loadingPixmaps.append(QPixmap(":/ile/assets/ile/ile6.png"));
    loadingPixmaps.append(QPixmap(":/ile/assets/ile/ile7.png"));
    loadingPixmaps.append(QPixmap(":/ile/assets/ile/ile8.png"));
    loadingPixmaps.append(QPixmap(":/ile/assets/ile/ile9.png"));
    loadingPixmaps.append(QPixmap(":/ile/assets/ile/ile10.png"));
    loadingPixmaps.append(QPixmap(":/ile/assets/ile/ile11.png"));
    loadingPixmaps.append(QPixmap(":/ile/assets/ile/ile12.png"));
    loadingPixmaps.append(QPixmap(":/ile/assets/ile/ile13.png"));
    loadingPixmaps.append(QPixmap(":/ile/assets/ile/ile14.png"));
    loadingPixmaps.append(QPixmap(":/ile/assets/ile/ile15.png"));
    loadingPixmaps.append(QPixmap(":/ile/assets/ile/ile16.png"));
    loadingPixmaps.append(QPixmap(":/ile/assets/ile/ile17.png"));
    loadingPixmaps.append(QPixmap(":/ile/assets/ile/ile18.png"));
    loadingPixmaps.append(QPixmap(":/ile/assets/ile/ile19.png"));
    loadingPixmaps.append(QPixmap(":/ile/assets/ile/ile20.png"));
    loadingPixmaps.append(QPixmap(":/ile/assets/ile/ile21.png"));


    // Chargement des images de pieces, d'objets et autres
    elementPixmaps["pieces1"] = QPixmap(":/hud/assets/hud_elements/piece/piece.png");

    elementPixmaps["lvl0_object1"] = QPixmap(":/object/assets/object/lvl0_object1.png");

    elementPixmaps["lvl1_object1"] = QPixmap(":/object/assets/object/lvl1_object1.png");
    elementPixmaps["lvl1_object2"] = QPixmap(":/object/assets/object/lvl1_object2.png");
    elementPixmaps["lvl1_object3"] = QPixmap(":/object/assets/object/lvl1_object3.png");

    elementPixmaps["lvl2_object1"] = QPixmap(":/object/assets/object/lvl2_object1.png");
    elementPixmaps["lvl2_object2"] = QPixmap(":/object/assets/object/lvl2_object2.png");
    elementPixmaps["lvl2_object3"] = QPixmap(":/object/assets/object/lvl2_object3.png");

    elementPixmaps["lvl3_object1"] = QPixmap(":/object/assets/object/lvl3_object1.png");
    elementPixmaps["lvl3_object2"] = QPixmap(":/object/assets/object/lvl3_object2.png");
    elementPixmaps["lvl3_object3"] = QPixmap(":/object/assets/object/lvl3_object3.png");

    elementPixmaps["text_background"] = QPixmap(":/menu/assets/game_style/text_background.png");
}
/**
     * @brief Event handler for painting the GUI.
     *
     * @param event Paint event.
*/
void GUI::paintEvent(QPaintEvent *event)
{
    Q_UNUSED(event);
    QPainter painter(this);

    itsGame->onDoorCollision();

    int positionX = itsGame->getItsLevel()->getItsMainCharacter()->getRect().center().x();
    if (positionX > itsGame->getItsLevel()->getItsLevelWidth() - width()/2)
    {
        painter.translate(-itsGame->getItsLevel()->getItsLevelWidth() + width(), 0);
    }
    else if (positionX > width()/2)
    {
        painter.translate(-positionX + width()/2, 0);
    }

    updateBackground(); // Mettre à jour l'image de fond en fonction du niveau

    int levelNumber = itsGame->getItsLevel()->getItsNb();

    if (levelNumber == 1 || levelNumber == 3 || levelNumber == 5)
    {
        painter.drawPixmap(0, 0, 8000, 720, backgroundPixmap);
    }
    else if (levelNumber == 2 || levelNumber == 4|| levelNumber == 6)
    {
        painter.drawPixmap(0, 0, 1280, 720, backgroundPixmap);
    }
    else if (levelNumber == 0)
    {
        painter.drawPixmap(0, 0, 3840, 720, backgroundPixmap);
    }

    drawObstacles(&painter);
    drawPieces(&painter);
    drawFlashbackObjects(&painter);
    drawDoor(&painter);
    drawCharacters(&painter);

    drawHUD(&painter);
    drawBoss(&painter);

    if (itsGame->getItsDead())
    {
        drawDeadMainCharacter(&painter);
    }
    else if (isAttacking)
    {
        drawAttackMC(&painter);
    }
    else
    {
        drawMainCharacter(&painter);
    }
    
    drawCompanion(&painter);
    

    if (isLoading) {
        painter.fillRect(rect(), Qt::black);
        int frameWidth = loadingPixmaps[0].width(); // Largeur de chaque image de la séquence
        int frameHeight = loadingPixmaps[0].height(); // Hauteur de chaque image de la séquence
        int x = (width() - frameWidth) / 2;
        int y = (height() - frameHeight) / 2;

        // Calculer l'index de l'image à afficher
        int index = 0;

        if (levelNumber == 2)
        {
            index = ((frameIndex) % 7) + 7;
        }
        else if (levelNumber == 4)
        {
            index = (frameIndex % 7) + 14;
        }

        QPixmap currentFrame = loadingPixmaps.at(index);

        // Dessiner l'image actuelle
        painter.drawPixmap(x, y, currentFrame);
    }


}


/**
     * @brief Event handler for key press events.
     *
     * @param event Key event.
*/
void GUI::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape)
    {
        // Inversez l'état de la pause
        isPaused = !isPaused;

        // Si le jeu est en pause, affichez le menu de pause
        if (isPaused)
        {
            itsGame->setIsPaused(true);
            itsGame->getItsTimer()->stop();
            pauseMenu->show(); // Remplacez "pauseMenu" par votre nom d'objet de menu de pause
        }
        else // Sinon, cachez le menu de pause
        {
            pauseMenu->hide(); // Remplacez "pauseMenu" par votre nom d'objet de menu de pause
        }
    }
    if (event->key() == Qt::Key_Left)
    {
        itsGame->getItsLevel()->getItsMainCharacter()->setPreviousDirection(true);
        itsGame->getItsLevel()->getItsMainCharacter()->moveLeft(true);
        itsGame->getItsLevel()->getItsCompanion()->moveLeft(true);
    }
    else if (event->key() == Qt::Key_Right)
    {
        itsGame->getItsLevel()->getItsMainCharacter()->setPreviousDirection(false);
        itsGame->getItsLevel()->getItsMainCharacter()->moveRight(true);
        itsGame->getItsLevel()->getItsCompanion()->moveRight(true);
    }
    else if (event->key() == Qt::Key_Up)
    {
        itsGame->getItsLevel()->getItsMainCharacter()->jump(true);
        itsGame->getItsLevel()->getItsCompanion()->jump(true);
    }

    else if (event->key() == Qt::Key_Down)
    {
        itsGame->onDoorCollision(); // Vérifie la collision avec la porte

        if (itsGame->playerIsNearDoor)
        {
            itsTimer->stop(); // Arrêter le timer principal

            int currentLevel = itsGame->getItsLevel()->getItsNb();
            int nextLevel = currentLevel + 1;

            // Vérifier si l'animation de chargement doit être déclenchée
            if ((currentLevel == 2 && nextLevel == 3) || (currentLevel == 4 && nextLevel == 5))
            {
                // Activer le mode de chargement
                isLoading = true;

                // Utiliser un QTimer pour l'animation de chargement
                QTimer* loadingTimer = new QTimer(this);
                connect(loadingTimer, &QTimer::timeout, this, [=]() {
                    // Incrémenter l'index de l'image
                    frameIndex = (frameIndex + 1) % loadingPixmaps.size();
                    // Redessiner l'écran
                    update();
                });
                loadingTimer->start(500); // Intervalle de l'animation (en millisecondes)

                // Charger le niveau suivant après un délai fixe
                QTimer::singleShot(3500, [this, loadingTimer]() {
                    itsGame->loadNextLevel();
                    loadImages();
                    isLoading = false; // Désactiver le mode de chargement
                    itsTimer->start(); // Redémarrer le timer principal
                    frameIndex = 0;
                    loadingTimer->stop(); // Arrêter le QTimer de l'animation de chargement
                    loadingTimer->deleteLater(); // Supprimer le QTimer
                    actionInProgress = true;
                });
            }
            else
            {
                // Charger directement le niveau suivant sans animation de chargement
                itsGame->loadNextLevel();
            }
        }
    }
    else if (event->key() == Qt::Key_Space)
    {
        itsGame->attackMC();
        attackFrameCounter = 0;
    }
}

/**
     * @brief Event handler for key release events.
     *
     * @param event Key event.
*/
void GUI::keyReleaseEvent(QKeyEvent *event)
{
    if(event->key() == Qt::Key_Escape)
    {
        if(pauseMenu->isHidden())
        {
            itsGame->setIsPaused(false);
        }
    }
    if (event->key() == Qt::Key_Left)
    {
        itsGame->getItsLevel()->getItsMainCharacter()->moveLeft(false);
        itsGame->getItsLevel()->getItsCompanion()->moveLeft(false);
    }
    else if (event->key() == Qt::Key_Right)
    {
        itsGame->getItsLevel()->getItsMainCharacter()->moveRight(false);
        itsGame->getItsLevel()->getItsCompanion()->moveRight(false);
    }
    else if (event->key() == Qt::Key_Up)
    {
        itsGame->getItsLevel()->getItsMainCharacter()->jump(false);
        itsGame->getItsLevel()->getItsCompanion()->jump(false);
    }

    if (event->key() == Qt::Key_Space)
    {
        itsGame->attackMC();
        counterAttack = 1;
    }
}

/**
     * @brief Event handler for mouse press events.
     *
     * @param event Mouse event.
*/
void GUI::mousePressEvent(QMouseEvent *event)
{
    QPoint clickPosition = event->pos();
    if (restartButtonRect.contains(clickPosition))
    {
        restartGame();
    }
}

/**
     * @brief Draws the main character in the game.
     *
     * @param aPainter Pointer to the painter object used for drawing.
*/
void GUI::drawMainCharacter(QPainter *aPainter)
{
    QString key;
    counterDrawMainCharacter = (counterDrawMainCharacter + 1) % 6; // Animation de 6 frames
    if(itsGame->getItsLevel()->getItsMainCharacter()->getItsRight())
    {
        key = "main_walk" + QString::number((counterDrawMainCharacter / 2) + 1) + "_reversed";
        previousDirectionRightMC = true;
    }
    else if(itsGame->getItsLevel()->getItsMainCharacter()->getItsLeft())
    {
        key = "main_walk" + QString::number((counterDrawMainCharacter / 2) + 1);
        previousDirectionRightMC = false;
    }
    else
    {
        if(!previousDirectionRightMC)
        {
            key = "main_walk1_reversed";
        }
        if(previousDirectionRightMC)
        {
            key = "main_walk1";
        }
    }
    aPainter->drawPixmap(itsGame->getItsLevel()->getItsMainCharacter()->getRect(), characterPixmaps[key]);
}

/**
     * @brief Draws the companion character in the game.
     *
     * @param aPainter Pointer to the painter object used for drawing
     */
void GUI::drawCompanion(QPainter * aPainter)
{
    QString key;
    counterCompanion = (counterCompanion + 1) % 6; // Animation de 6 frames
    if(itsGame->getItsLevel()->getItsCompanion()->getItsLeft())
    {
        key = "companion_walk" + QString::number((counterCompanion / 3) + 1) + "_reversed";
        previousDirectionRightMC = true;
    }
    else if(itsGame->getItsLevel()->getItsMainCharacter()->getItsRight())
    {
        key = "companion_walk" + QString::number((counterCompanion / 3) + 1);
        previousDirectionRightMC = false;
    }
    else
    {
        if(previousDirectionRightMC)
        {
            key = "companion_walk1_reversed";
        }
        if(!previousDirectionRightMC)
        {
            key = "companion_walk1";
        }
    }
    aPainter->drawPixmap(itsGame->getItsLevel()->getItsCompanion()->getRect(), characterPixmaps[key]);
}
/**
     * @brief Draws the characters in the game.
     *
     * @param aPainter Pointer to the painter object used for drawing.
*/
void GUI::drawCharacters(QPainter *aPainter)
{
    if(itsGame->getItsLevel()->getItsEnemyType() == "ws" or itsGame->getItsLevel()->getItsFinalBoss() != nullptr)
    {
        counterDrawEnemies = (counterDrawEnemies + 1) % 9;

        QString key;
        QString enemyType;
        for (Character* character : *itsGame->getItsLevel()->getItsEnemies())
        {
            if (character->getItsDead() == false)
            {
                if (character->getType() == 1) // Squelette
                {
                    enemyType = "skeleton";
                }
                if (character->getType() == 2) // Loup
                {
                    enemyType = "wolf";
                }
                if (character->getPreviousDirection())
                {
                    key = enemyType + "_walk" + QString::number((counterDrawEnemies / 3) + 1);
                }
                else if(!character->getPreviousDirection())
                {
                    key = enemyType + "_walk" + QString::number((counterDrawEnemies / 3) + 1) + "_reversed";
                }
                aPainter->drawPixmap(character->getRect(), characterPixmaps[key]);
            }
        }
    }
    else if(itsGame->getItsLevel()->getItsEnemyType() == "cs")
    {
        counterDrawEnemies = (counterDrawEnemies + 1) % 9;

        QString key;
        QString enemyType;

        for (Character* character : *itsGame->getItsLevel()->getItsEnemies())
        {
            if (character->getItsDead() == false)
            {
                if (character->getType() == 1) // Soldat
                {
                    enemyType = "soldier";
                }
                if (character->getType() == 2) // Canon
                {
                    enemyType = "canon";
                }
                if (!character->getPreviousDirection())
                {
                    key = enemyType + "_walk" + QString::number((counterDrawEnemies / 3) + 1);
                }
                else if(character->getPreviousDirection())
                {
                    key = enemyType + "_walk" + QString::number((counterDrawEnemies / 3) + 1) + "_reversed";
                }

                aPainter->drawPixmap(character->getRect(), characterPixmaps[key]);
            }
        }
    }
    else if(itsGame->getItsLevel()->getItsEnemyType() == "nt")
    {
        counterDrawEnemies = (counterDrawEnemies + 1) % 9;

        QString key;
        QString enemyType;

        for (Character* character : *itsGame->getItsLevel()->getItsEnemies())
        {
            if (character->getItsDead() == false)
            {
                if (character->getType() == 1) // Nautilus
                {
                    enemyType = "nautilus";
                }
                if (character->getType() == 2) // Turret
                {
                    enemyType = "turret";
                }
                if (character->getPreviousDirection())
                {
                    key = enemyType + "_walk" + QString::number((counterDrawEnemies / 3) + 1);
                }
                else if(!character->getPreviousDirection())
                {
                    key = enemyType + "_walk" + QString::number((counterDrawEnemies / 3) + 1) + "_reversed";
                }

                aPainter->drawPixmap(character->getRect(), characterPixmaps[key]);
            }
        }
    }
}
/**
     * @brief Draws the collectible pieces in the game.
     *
     * @param aPainter Pointer to the painter object used for drawing.
*/
void GUI::drawPieces(QPainter * aPainter)
{
    for (Piece* piece : *itsGame->getItsLevel()->getItsPieces())
    {
        aPainter->drawPixmap(piece->getRect(), elementPixmaps["pieces1"]);
    }
}
/**
     * @brief Draws the flashback objects in the game.
     *
     * @param aPainter Pointer to the painter object used for drawing.
*/
void GUI::drawFlashbackObjects(QPainter * aPainter)
{
    for (FlashbackObject* object : *itsGame->getItsLevel()->getItsFlashbackObjects())
    {
        QString key = "lvl"+QString::number(itsGame->getItsLevel()->getItsHUDNb())+"_object"+object->getItsNb();
        aPainter->drawPixmap(object->getRect(), elementPixmaps[key]);
    }
}
/**
     * @brief Draws the collision of obstacles in the game.
     *
     * @param aPainter Pointer to the painter object used for drawing.
*/
void GUI::drawObstacles(QPainter *aPainter)
{
    for (Obstacle* obstacle : *itsGame->getItsLevel()->getItsObstacles())
    {
        aPainter->setPen(Qt::transparent);
        aPainter->setBrush(Qt::transparent); // Modifiez la couleur selon votre design
        aPainter->drawRect(obstacle->getRect());
    }
}

/**
     * @brief Draws the HUD (Heads-Up Display) in the game.
     *
     * @param aPainter Pointer to the painter object used for drawing.
*/
void GUI::drawHUD(QPainter * aPainter)
{

    QPixmap pieceNb(":/hud/assets/hud_elements/font/"+QString::number(itsGame->getItsLevel()->getItsMainCharacter()->getItsPieceNb())+"_font.png");
    QPixmap piece(":/hud/assets/hud_elements/piece/piece.png");

    QPixmap heart1, heart2, heart3;
    switch (itsGame->getItsLevel()->getItsMainCharacter()->getItsHP())
    {
    case 1:
        heart1 = QPixmap(":/hud/assets/hud_elements/heart/heart_half.png");
        heart2 = QPixmap(":/hud/assets/hud_elements/heart/heart_empty.png");
        heart3 = QPixmap(":/hud/assets/hud_elements/heart/heart_empty.png");
        break;
    case 2:
        heart1 = QPixmap(":/hud/assets/hud_elements/heart/heart_full.png");
        heart2 = QPixmap(":/hud/assets/hud_elements/heart/heart_empty.png");
        heart3 = QPixmap(":/hud/assets/hud_elements/heart/heart_empty.png");
        break;
    case 3:
        heart1 = QPixmap(":/hud/assets/hud_elements/heart/heart_full.png");
        heart2 = QPixmap(":/hud/assets/hud_elements/heart/heart_half.png");
        heart3 = QPixmap(":/hud/assets/hud_elements/heart/heart_empty.png");
        break;
    case 4:
        heart1 = QPixmap(":/hud/assets/hud_elements/heart/heart_full.png");
        heart2 = QPixmap(":/hud/assets/hud_elements/heart/heart_full.png");
        heart3 = QPixmap(":/hud/assets/hud_elements/heart/heart_empty.png");
        break;
    case 5:
        heart1 = QPixmap(":/hud/assets/hud_elements/heart/heart_full.png");
        heart2 = QPixmap(":/hud/assets/hud_elements/heart/heart_full.png");
        heart3 = QPixmap(":/hud/assets/hud_elements/heart/heart_half.png");
        break;
    case 6:
        heart1 = QPixmap(":/hud/assets/hud_elements/heart/heart_full.png");
        heart2 = QPixmap(":/hud/assets/hud_elements/heart/heart_full.png");
        heart3 = QPixmap(":/hud/assets/hud_elements/heart/heart_full.png");
        break;
    default:
        heart1 = QPixmap(":/hud/assets/hud_elements/heart/heart_empty.png");
        heart2 = QPixmap(":/hud/assets/hud_elements/heart/heart_empty.png");
        heart3 = QPixmap(":/hud/assets/hud_elements/heart/heart_empty.png");
        break;
    }

    QPixmap slash(":/hud/assets/hud_elements/font/slash.png");
    QPixmap nbObject(":/hud/assets/hud_elements/font/"+QString::number(itsGame->getItsLevel()->getItsMainCharacter()->getItsFlashbackObjectNb())+"_font.png");
    QPixmap nbObjectTotal(":/hud/assets/hud_elements/font/"+QString::number(itsGame->getItsLevel()->getItsFlashbackObjectNb())+"_font.png");

    QPixmap nbLvl(":/hud/assets/hud_elements/font/"+QString::number(itsGame->getItsLevel()->getItsHUDNb())+"_font.png");
    QPixmap lvl(":/hud/assets/hud_elements/font/lvl.png");


    int fontSize = 40;
    int pieceSize = 50;
    int heartSize = 55;
    int lvlWidth = fontSize*3 + 10;

    int pieceNbOffsetX = 30;
    int pieceOffsetX = 80;
    int pieceNbOffsetY = 100;
    int pieceOffsetY = 95;

    int heart1OffsetX = 30;
    int heart2OffsetX = 90;
    int heart3OffsetX = 150;
    int heartOffsetY = 30;

    int slashOffsetX = width()/2 - fontSize/2;
    int nbObjectOffsetX = slashOffsetX - fontSize;
    int nbObjectTotalOffsetX = slashOffsetX + fontSize;

    int nbLvlOffsetX = width() - fontSize - 30;
    int lvlOffsetX = nbLvlOffsetX - lvlWidth - 10;

    int fontOffsetY = 35;

    int positionX = itsGame->getItsLevel()->getItsMainCharacter()->getRect().center().x();
    int levelWidth = itsGame->getItsLevel()->getItsLevelWidth();
    int globalOffset;

    if (positionX > levelWidth - width()/2)
    {
        globalOffset = levelWidth - width();
    }
    else if (positionX > width()/2)
    {
        globalOffset = positionX - width()/2;
    }
    else
    {
        globalOffset = 0;
    }

    // Display of pieces number
    aPainter->drawPixmap(globalOffset + pieceNbOffsetX, pieceNbOffsetY, fontSize, fontSize, pieceNb);
    aPainter->drawPixmap(globalOffset + pieceOffsetX, pieceOffsetY, pieceSize, pieceSize, piece);

    // Display of health
    aPainter->drawPixmap(globalOffset + heart1OffsetX, heartOffsetY, heartSize, heartSize, heart1);
    aPainter->drawPixmap(globalOffset + heart2OffsetX, heartOffsetY, heartSize, heartSize, heart2);
    aPainter->drawPixmap(globalOffset + heart3OffsetX, heartOffsetY, heartSize, heartSize, heart3);

    // Display of objects number
    aPainter->drawPixmap(globalOffset + slashOffsetX, fontOffsetY, fontSize, fontSize, slash);
    aPainter->drawPixmap(globalOffset + nbObjectOffsetX, fontOffsetY, fontSize, fontSize, nbObject);
    aPainter->drawPixmap(globalOffset + nbObjectTotalOffsetX, fontOffsetY, fontSize, fontSize, nbObjectTotal);

    // Display of level number
    aPainter->drawPixmap(globalOffset + nbLvlOffsetX, fontOffsetY, fontSize, fontSize, nbLvl);
    aPainter->drawPixmap(globalOffset + lvlOffsetX, fontOffsetY, lvlWidth, fontSize, lvl);
}
/**
     * @brief Draws the main character's attack animation.
     *
     * @param painter Pointer to the painter object used for drawing.
*/
void GUI::drawAttackMC(QPainter *aPainter)
{
    QString key;

    // Calculer l'index de la frame actuelle
    int frameIndex = attackFrameCounter / 2 + 1;

    switch (frameIndex)
    {
    case 0:
        key = "main_sword_attack1";
        break;
    case 1:
        key = "main_sword_attack2";
        break;
    case 2:
        key = "main_sword_attack3";
        break;
    case 3:
        key = "main_sword_attack4";
        break;
    default:
        isAttacking = false; // Arrêter l'animation après la dernière frame
        attackFrameCounter = 0; // Réinitialiser le compteur pour la prochaine attaque
        return;
        aPainter->drawPixmap(itsGame->getItsLevel()->getItsMainCharacter()->getRect(), characterPixmaps[key]);
        counterAttack = 0;
    }

    if (!itsGame->getItsLevel()->getItsMainCharacter()->getPreviousDirection())
    {
        key += "_reversed";
        key = "main_sword_attack1_reversed";
        aPainter->drawPixmap(itsGame->getItsLevel()->getItsMainCharacter()->getRect(), characterPixmaps[key]);
        key = "main_sword_attack2_reversed";
        aPainter->drawPixmap(itsGame->getItsLevel()->getItsMainCharacter()->getRect(), characterPixmaps[key]);
        key = "main_sword_attack3_reversed";
        aPainter->drawPixmap(itsGame->getItsLevel()->getItsMainCharacter()->getRect(), characterPixmaps[key]);
        counterAttack = 0;
    }
    if (frameIndex == 3)
    {
        isAttacking = false;
        attackFrameCounter = 0;
    }

    aPainter->drawPixmap(itsGame->getItsLevel()->getItsMainCharacter()->getRect(), characterPixmaps[key]);

    attackFrameCounter++;


}



/**
     * @brief Draws the main character in the dead state.
     *
     * @param painter Pointer to the painter object used for drawing.
*/
void GUI::drawDeadMainCharacter(QPainter *aPainter)
{
    QString key;
    key = "main_dead";
    aPainter->drawPixmap(itsGame->getItsLevel()->getItsMainCharacter()->getRect(), characterPixmaps[key]);
}
/**
     * @brief Draws the differents boss character in the game.
     *
     * @param aPainter Pointer to the painter object used for drawing.
*/
void GUI::drawBoss(QPainter *aPainter)
{

        // Déclaration de la variable flyingAnimation comme static
        static bool walkingAnimation = false;
        static bool flyingAnimation = false;
        static int animationCounter = 0;
        const int animationDelay = 10; // Délai en nombre de frames entre chaque changement d'image

        if(itsGame->getItsLevel()->getItsFinalBoss() != nullptr && itsGame->getItsLevel()->getItsFinalBoss()->getItsHP() >0 )
        {
            if (itsGame->getItsLevel()->getItsFinalBoss()->getItsHP() > 16)
            {
                QString key = walkingAnimation ? "asterios_walk1" : "asterios_walk2";
                if (!itsGame->getItsLevel()->getItsFinalBoss()->getPreviousDirection())
                {
                    key = walkingAnimation ? "asterios_walk1_reversed" : "asterios_walk2_reversed";
                }
                aPainter->drawPixmap(itsGame->getItsLevel()->getItsFinalBoss()->getRect(), characterPixmaps[key]);
            }
            else
            {
                QString key = walkingAnimation ? "asterios_with_armor_walk1" : "asterios_with_armor_walk2";
                if (!itsGame->getItsLevel()->getItsFinalBoss()->getPreviousDirection())
                {
                    key = walkingAnimation ? "asterios_with_armor_walk1_reversed" : "asterios_with_armor_walk2_reversed";
                }
                aPainter->drawPixmap(itsGame->getItsLevel()->getItsFinalBoss()->getRect(), characterPixmaps[key]);
            }

            if (animationCounter >= animationDelay)
            {
                walkingAnimation = !walkingAnimation;
                animationCounter = 0;
            }
            else
            {
                animationCounter++;
            }
        }
        if(itsGame->getItsLevel()->getItsFinalBoss() != nullptr && itsGame->getItsLevel()->getItsFinalBoss()->getItsHP() <=0)
        {
            QRect targetRect(0, 0, 1280, 720);
            aPainter->drawPixmap(targetRect, elementPixmaps["victory"]);
        }
        if(itsGame->getItsLevel()->getItsBoss() != nullptr)
        {
        if (itsGame->getItsLevel()->getItsBoss()->getItsHP() <= 0 && itsGame->getItsLevel()->getItsNb() == 2)
        {
            aPainter->drawPixmap(itsGame->getItsLevel()->getItsBoss()->getRect(), characterPixmaps["chevalry_dead"]);
        }
        else if (itsGame->getItsLevel()->getItsBoss()->getItsHP() <= 0 && itsGame->getItsLevel()->getItsNb() == 4)
        {
            aPainter->drawPixmap(itsGame->getItsLevel()->getItsBoss()->getRect(), characterPixmaps["ghost_dead"]);
        }
        else
        {
            if (itsGame->getItsLevel()->getItsNb() == 2)
            {
                aPainter->drawPixmap(itsGame->getItsLevel()->getItsBoss()->getRect(), characterPixmaps["chevalry"]);
            }
            else
            {
                if (animationCounter >= animationDelay)
                {
                    // Alternance entre deux images pour l'animation de vol
                    QString key = flyingAnimation ? "ghost_fly_1_reversed" : "ghost_fly_2_reversed";
                    aPainter->drawPixmap(itsGame->getItsLevel()->getItsBoss()->getRect(), characterPixmaps[key]);
                    flyingAnimation = !flyingAnimation; // Inverser pour alterner les images à chaque appel
                    animationCounter = 0; // Réinitialiser le compteur après chaque changement d'image
                }
                else
                {
                    // Si le délai n'est pas encore écoulé, dessiner l'image actuelle sans changement
                    QString key = flyingAnimation ? "ghost_fly_1_reversed" : "ghost_fly_2_reversed";
                    aPainter->drawPixmap(itsGame->getItsLevel()->getItsBoss()->getRect(), characterPixmaps[key]);
                    animationCounter++; // Incrémenter le compteur
                }
            }

            // Affichage de la barre de vie
            aPainter->setBrush(QBrush(Qt::gray));
            aPainter->drawRect(360, 120, 600, 20);
            // Dessiner la barre de vie en rouge
            aPainter->setBrush(QBrush(Qt::red));
            aPainter->drawRect(360, 120, static_cast<int>((static_cast<float>(itsGame->getItsLevel()->getItsBoss()->getItsHP()) / 12) * 600), 20);
        }

        // Affichage des attaques du boss
        for (QRect* summoning : *(itsGame->getItsLevel()->getItsBoss()->getItsSummoning()))
        {
            if (itsGame->getItsLevel()->getItsNb() == 2)
            {
                if (itsGame->getItsLevel()->getItsBoss()->getIsSwordVertical())
                {
                    aPainter->drawPixmap(*summoning, characterPixmaps["sword_vertical"]);
                }
                else
                {
                    aPainter->drawPixmap(*summoning, characterPixmaps["sword_horizontal"]);
                }
            }
            else
            {
                if (animationCounter >= animationDelay)
                {
                    // Alternance entre deux images pour l'animation de marche du fantôme
                    QString key = flyingAnimation ? "little_fantome_walk_1" : "little_fantome_walk_2";
                    aPainter->drawPixmap(*summoning, characterPixmaps[key]);
                    flyingAnimation = !flyingAnimation; // Inverser pour alterner les images à chaque appel
                    animationCounter = 0; // Réinitialiser le compteur après chaque changement d'image
                }
                else
                {
                    // Si le délai n'est pas encore écoulé, dessiner l'image actuelle sans changement
                    QString key = flyingAnimation ? "little_fantome_walk_1" : "little_fantome_walk_2";
                    aPainter->drawPixmap(*summoning, characterPixmaps[key]);
                    animationCounter++; // Incrémenter le compteur
                }
            }
        }
    }
}

/**
     * @brief Displays the game-over screen.
*/
void GUI::displayGameOverScreen()
{
    QPixmap gameOver(":/menu/assets/game_style/GameOver169.png");
    gameOver = gameOver.scaled(1280, 720);
    gameOverLabel->resize(1280, 720);
    gameOverLabel->move(0,0);
    gameOverLabel->setPixmap(gameOver);
    restartButtonRect = QRect(560, 520, 180, 50);
    itsFlashbackBackground->hide();
    itsFlashbackText->hide();
    gameOverLabel->show();
    update();
}
/**
     * @brief Updates the background image.
*/
void GUI::updateBackground()
{
    QString imagePath;

    int levelNumber = itsGame->getItsLevel()->getItsNb();

    switch (levelNumber) {
    case 0:
        imagePath = "level_0";
        break;
    case 1:
        itsGame->getItsLevel()->getPlayer()->stop();
        imagePath = "level_1";
        break;
    case 2:
        imagePath = "boss_1";
        itsGame->getItsLevel()->getPlayer()->stop();
        break;
    case 3:
        imagePath = "level_2";
        itsGame->getItsLevel()->getPlayer()->stop();
        break;
    case 4:
        imagePath = "boss_2";
        itsGame->getItsLevel()->getPlayer()->stop();
        break;
    case 5:
        imagePath = "level_3";
        itsGame->getItsLevel()->getPlayer()->stop();
        break;
    case 6:
        imagePath = "boss_3";
        break;
    default:
        // Gérez d'autres cas si nécessaire
        break;
    }

    backgroundPixmap = backgroundPixmaps.value(imagePath);

    update();
}

/**
     * @brief Draws the door in the game.
     *
     * @param aPainter Pointer to the painter object used for drawing.
*/
void GUI::drawDoor(QPainter *aPainter)
{
    QString imagePath;

    int levelNumber = itsGame->getItsLevel()->getItsNb();

    switch (levelNumber) {
    case 0:
        imagePath = "portal_1";
        break;
    case 1:
        imagePath = "door_1";
        break;
    case 2:
        imagePath = "portal_1";
        break;
    case 3:
        imagePath = "door_2";
        break;
    case 4:
        imagePath = "portal_1";
        break;
    case 5:
        imagePath = "door_3";
    default:
        // Gérez d'autres cas si nécessaire
        break;
    }

    QPixmap doorPixmap = doorPixmaps.value(imagePath);

    if (itsGame->getItsLevel()->getItsDoor()) {
        aPainter->drawPixmap(itsGame->getItsLevel()->getItsDoor()->getRect(), doorPixmap);
    }
}
/**
     * @brief Restarts the game.
*/
void GUI::restartGame()
{
    gameOverLabel->hide();
    itsGame->restartLevel(); // Ajoutez cette méthode à votre classe Game pour réinitialiser l'état du jeu
    itsTimer->start();

    // Réinitialiser restartButtonRect pour désactiver le bouton de redémarrage
    restartButtonRect = QRect();
}

/**
     * @brief Handles the action to continue the game.
*/
void GUI::handleContinueGame()
{
    itsGame->setIsPaused(false);
    itsGame->getItsTimer()->start();
    pauseMenu->hide(); // Cacher le menu de pause
}

/**
     * @brief Shows the options menu.
*/
void GUI::showOptionsMenu()
{
    pauseMenu->hide();
    optionsMenu->show();

}

/**
     * @brief Slot for drawing flashback text.
     *
     * @param aText The text to display in the flashback.
*/
void GUI::drawFlashbackText(QString aText)
{
    // Configure and show the background label
    elementPixmaps["text_background"] = elementPixmaps["text_background"].scaled(450, 150);
    itsFlashbackBackground->move(1280/2-450/2, 720/2-150/2);
    itsFlashbackBackground->setPixmap(elementPixmaps["text_background"]);
    itsFlashbackBackground->show();

    // Configure and show the text label
    itsFlashbackText->resize(400, 150);
    itsFlashbackText->move(1280/2-400/2, 720/2-150/2);
    itsFlashbackText->raise();
    itsFlashbackText->setText(aText);
    itsFlashbackText->show();

    // Hide the flashback text after 5 seconds
    QTimer::singleShot(3500, this, [this]() { hideFlashbackText();});
}

/**
     * @brief Slot for hiding flashback text.
*/
void GUI::hideFlashbackText()
{
    itsFlashbackBackground->hide();
    itsFlashbackText->hide();
}
