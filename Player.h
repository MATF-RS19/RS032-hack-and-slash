#ifndef PLAYER_H
#define PLAYER_H

#include <QGraphicsSceneMouseEvent>
#include <QGraphicsRectItem>

#include "Character.h"
#include "Camera.h"

class Player : public Character{
public:
    Player(Map* m, int health, float speed, int size, int x, int y, Animator anim, QVector<Spell*> spells) : Character(m, health, speed, size, x, y, anim, spells) {}
    void update(int deltaT) override;
    void cast(int i);
};


#endif // PLAYER_H
