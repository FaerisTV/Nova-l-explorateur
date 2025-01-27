#ifndef LONGSCOPE_H
#define LONGSCOPE_H

#include "character.h"
#include <list>

using namespace std;

class LongScope : public Character
{
    int itsRange;
public:
    LongScope(int aX, int aY, int aWidth, int aHeight);
    void updatePosition(list<Obstacle *>* obstacles);
    void attack();
    bool getPreviousDirection();
};

#endif // LONGSCOPE_H
