#ifndef FINALBOSS_H
#define FINALBOSS_H

#include "character.h"
#include <list>
#include <QRect>

/**
 * @brief Class representing the final boss in the game.
 *
 * Inherits from the Character class.
 */
class FinalBoss : public Character
{
    bool isAttacking = false;
    bool isArmored = false;
    bool itsPreviousDirection = false;
public:
    /**
     * @brief Constructor to initialize the final boss.
     *
     * @param aX Initial X position of the boss
     * @param aY Initial Y position of the boss
     * @param aWidth Width of the boss
     * @param aHeight Height of the boss
     */
    FinalBoss(int aX, int aY, int aWidth, int aHeight, int type = 0);
    void attack() override;
    void updatePosition(std::list<Obstacle *>* obstacles) override;
    bool getIsAttacking();
    bool getPreviousDirection() override;
    void setIsAttacking(bool attack);
};

#endif // FINALBOSS_H
