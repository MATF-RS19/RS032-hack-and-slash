#ifndef ENEMY_H
#define ENEMY_H

#include <QPair>
#include <QGraphicsSceneMouseEvent>

#include "Character.h"

class Enemy: public Character{
public:
    Enemy(Map* m, int health, int mana, float attackRange, int attackCooldown, int attackDmg, float speed, int size, QVector< QPair<int, int> > patrolRoute, int aggroRange, int deaggroRange, Animator anim, QVector<Spell*> spells);
    void update(int deltaT) override;
    void mousePressEvent(QGraphicsSceneMouseEvent* event) override;

private:
    int aggroRange;
    int deaggroRange;
    QVector< QPair<int, int> > patrolRoute;
    int patrolPos;
};

#endif // ENEMY_H
