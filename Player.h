#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>

#include "Character.h"
#include "Camera.h"

class Player : public Character{
public:
    Player(Map* m, int health, int mana, float attackRange, int attackCooldown, int attackDmg, float speed, int size, int x, int y, Animator anim, QVector<Spell*> spells):
        Character(m, health, mana, attackRange, attackCooldown, attackDmg, speed, size, x, y, anim, spells) {}
    void update(int deltaT) override;
    void cast(int i);
private:
    int regenCooldown = 5000;
    int regenTimer = 0;
};


#endif // PLAYER_H
