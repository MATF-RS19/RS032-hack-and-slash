#ifndef ENEMY_H
#define ENEMY_H

#include <QPair>

#include "Character.h"

class Enemy: public Character{
public:
    Enemy(Map* m, float speed, int size, QVector< QPair<int, int> > patrolRoute, int aggroRange, int deaggroRange, Animator anim);
    void update(int deltaT);
    bool isPlayerInRange();

private:
    int aggroRange;
    int deaggroRange;
    QVector< QPair<int, int> > patrolRoute;
};

#endif // ENEMY_H
