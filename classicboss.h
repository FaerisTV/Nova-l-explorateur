#ifndef CLASSICBOSS_H
#define CLASSICBOSS_H

#include "character.h"

/**
 * @brief Class representing a classic boss in the game.
 *
 * Inherits from the Character class.
 */
class ClassicBoss : public Character
{
    list<QRect *> *itsSummoning;
    bool isAttacking = false;
    bool isSwordVertical = true;
    int itsPhase = 1;
public:
    /**
     * @brief Constructor to initialize the classic boss.
     *
     * @param aX Initial X position of the boss
     * @param aY Initial Y position of the boss
     * @param aWidth Width of the boss
     * @param aHeight Height of the boss
     */
    ClassicBoss(int aX, int aY, int aWidth, int aHeight);

    /**
     * @brief Updates the boss's position.
     *
     * @param obstacles List of obstacles present in the game
     */
    void updatePosition(list<Obstacle *>* obstacles) override;

    /**
     * @brief Performs an attack.
     */
    void attack() override;
    
    list<QRect *>*getItsSummoning();
    bool getPreviousDirection() override;
    bool getIsAttacking();
    int getItsPhase();
    void setItsPhase(int phase);
    bool getIsSwordVertical();
    void setIsAttacking(bool attack);
};

#endif // CLASSICBOSS_H
