#include "Enemy.h"

#include <cmath>

Enemy::Enemy(Map* m, float speed, int size, QVector< QPair<int, int> > patrolRoute, int aggroRange, int deaggroRange, Animator anim)
    : Character (m, speed, size, patrolRoute[0].first, patrolRoute[0].second, anim)
{
    this->patrolRoute = patrolRoute;
    this->aggroRange = aggroRange;
    this->deaggroRange = deaggroRange;
}

void Enemy::update(int deltaT){
    Character::update(deltaT);

    QPair<int, int> playerPos = world->getPlayerPos();

    float dist = sqrt(pow(playerPos.first - getI(),2) + pow(playerPos.second - getJ(), 2));

    if(dist < aggroRange)
        setDestination(playerPos.first, playerPos.second);
}
