#include "Enemy.h"
#include "Player.h"

#include <cmath>
#include <QDebug>

Enemy::Enemy(Map* m, float speed, int size, QVector< QPair<int, int> > patrolRoute, int aggroRange, int deaggroRange, Animator anim)
    : Character (m, speed, size, patrolRoute[0].first, patrolRoute[0].second, anim)
{
    this->patrolRoute = patrolRoute;
    this->aggroRange = aggroRange;
    this->deaggroRange = deaggroRange;
    patrolPos = 0;
}

void Enemy::update(int deltaT){
    Character::update(deltaT);

    Player* player = world->getPlayer();

    float dist = sqrt(pow(player->getI() - getI(),2) + pow(player->getJ() - getJ(), 2));

    // ovde treba umesto koren iz 2, attack range
    if(dist < aggroRange && dist > sqrt(2))
        target = player;
    else {
        target = nullptr;
        if(getI() == patrolRoute[patrolPos].first && getJ() == patrolRoute[patrolPos].second)
            if(++patrolPos == patrolRoute.size())
                patrolPos = 0;
        if(getI() != patrolRoute[patrolPos].first || getJ() != patrolRoute[patrolPos].second)
            setDestination(patrolRoute[patrolPos].first, patrolRoute[patrolPos].second);
    }

    if(target != nullptr)
        setDestination(target->getI(), target->getJ());
}

void Enemy::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->button() != Qt::MouseButton::RightButton)
        return;

    Player* player = world->getPlayer();
    player->setTarget(this);
}
