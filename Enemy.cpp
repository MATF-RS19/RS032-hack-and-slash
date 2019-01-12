#include "Enemy.h"
#include "Player.h"

#include <cmath>
#include <QDebug>

Enemy::Enemy(Map* m, int health, float speed, int size, QVector< QPair<int, int> > patrolRoute, int aggroRange, int deaggroRange, Animator anim, QVector<Spell*> spells)
    : Character (m, health, speed, size, patrolRoute[0].first, patrolRoute[0].second, anim, spells)
{
    this->patrolRoute = patrolRoute;
    this->aggroRange = aggroRange;
    this->deaggroRange = deaggroRange;
    patrolPos = 0;
}

void Enemy::update(int deltaT){
    if(charState == dead){
        world->destroyEnemy(this);
        return;
    }

    Character::update(deltaT);

    Player* player = world->getPlayer();

    float dist = float(sqrt(pow(player->getI() - getI(),2) + pow(player->getJ() - getJ(), 2)));

    if(dist < aggroRange)
        target = player;
    else if(dist > deaggroRange)
        target = nullptr;

    if(!target){
        if(getI() == patrolRoute[patrolPos].first && getJ() == patrolRoute[patrolPos].second)
            if(++patrolPos == patrolRoute.size())
                patrolPos = 0;
        if(getI() != patrolRoute[patrolPos].first || getJ() != patrolRoute[patrolPos].second)
            setDestination(patrolRoute[patrolPos].first, patrolRoute[patrolPos].second);
    }
}

void Enemy::mousePressEvent(QGraphicsSceneMouseEvent *event){
    if(event->button() != Qt::MouseButton::RightButton)
        return;

    Player* player = world->getPlayer();
    if(world->getInputState() == Map::InputState::normal)
        player->setTarget(this);
    if(world->getInputState() == Map::InputState::targetCharacter) {
        player->Character::cast(world->getInputSpell(), this);
        world->setInputState(Map::InputState::normal, 0);
    }
}
