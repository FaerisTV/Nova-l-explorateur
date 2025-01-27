#include "classicboss.h"
#include <cstdlib>
#include <ctime>
#include <QTransform>

/**
 * @brief Constructor of the ClassicBoss class.
 *
 * Initializes a ClassicBoss object with the given parameters.
 *
 * @param aX Initial X position of the boss.
 * @param aY Initial Y position of the boss.
 * @param aWidth Width of the boss.
 * @param aHeight Height of the boss.
 */
ClassicBoss::ClassicBoss(int aX, int aY, int aWidth, int aHeight)
    : Character(aX, aY, aWidth, aHeight, 0)
{
    itsSummoning = new std::list<QRect*>();
    itsHP = 12;
}

/**
 * @brief Executes the boss's attack based on its phase.
 */
void ClassicBoss::attack() {
    if (!isAttacking && itsPhase == 1)
    {
        isSwordVertical = true;
        // If not already attacking, start the attack sequence
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        for (int i = 0; i < 6; ++i){
            QRect* sword = new QRect(100 + i * 180, 50, 70, 70);
            itsSummoning->push_back(sword);
        }
        isAttacking = true;
    }

    if (!isAttacking && itsPhase == 2)
    {
        isSwordVertical = false;
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        for (int i = 0; i < 2; ++i)
        {
            QRect* sword = new QRect(1030, (std::rand() % (450 - 290 + 1) + 290) + i * 90, 70, 70);
            itsSummoning->push_back(sword);
        }
        isAttacking = true;
    }
    if (!isAttacking && itsPhase == 3)
    {
        isSwordVertical = true;
        // If not already attacking, start the attack sequence
        std::srand(static_cast<unsigned int>(std::time(nullptr)));
        for (int i = 0; i < 6; ++i){
            QRect* sword = new QRect(150 + i * 180, 50, 70, 70);
            itsSummoning->push_back(sword);
        }
        isAttacking = true;
    }
    else
    {
        if(itsPhase == 1)
        {
            for (QRect* sword : *itsSummoning)
            {
                QTransform transform;
                QRectF rotatedSword = transform.mapRect(*sword);
                rotatedSword.translate(0, 1.7);
                *sword = rotatedSword.toRect();
            }
        }
        else if(itsPhase == 2)
        {
            for (QRect* sword : *itsSummoning)
            {
                QTransform transform;
                transform.rotate(0.0);
                QRectF rotatedSword = transform.mapRect(*sword);
                rotatedSword.translate(-3, 0);
                *sword = rotatedSword.toRect();
            }
        }
        else if(itsPhase == 3)
        {
            for (QRect* sword : *itsSummoning)
            {
                QTransform transform;
                QRectF rotatedSword = transform.mapRect(*sword);
                rotatedSword.translate(0, 1.7);
                *sword = rotatedSword.toRect();
            }
        }
    }
}

/**
 * @brief Gets the list of QRect objects representing the attacks summoned by the boss.
 *
 * @return Pointer to the list of QRects of the summons.
 */
std::list<QRect*> *ClassicBoss::getItsSummoning() {
    return itsSummoning;
}

/**
 * @brief Checks if the boss is currently attacking.
 *
 * @return True if the boss is attacking, false otherwise.
 */
bool ClassicBoss::getIsAttacking()
{
    return isAttacking;
}

/**
 * @brief Checks if the sword is vertical.
 *
 * @return True if the sword is vertical, false otherwise.
 */
bool ClassicBoss::getIsSwordVertical()
{
    return isSwordVertical;
}

/**
 * @brief Sets the attack state of the boss.
 *
 * @param attack New attack state of the boss.
 */
void ClassicBoss::setIsAttacking(bool attack)
{
    isAttacking = attack;
}

/**
 * @brief Gets the current phase of the boss.
 *
 * @return Current phase of the boss.
 */
int ClassicBoss::getItsPhase()
{
    return itsPhase;
}

/**
 * @brief Sets the phase of the boss.
 *
 * @param phase New phase of the boss.
 */
void ClassicBoss::setItsPhase(int phase)
{
    itsPhase = phase;
}

/**
 * @brief Updates the boss's position. Empty implementation.
 *
 * @param obstacles List of obstacles.
 */
void ClassicBoss::updatePosition(std::list<Obstacle *>* obstacles)
{
    // Do nothing, empty function
}

/**
 * @brief Gets the previous direction of the boss. Empty implementation.
 *
 * @return Always false.
 */
bool ClassicBoss::getPreviousDirection()
{
    return false;
}
