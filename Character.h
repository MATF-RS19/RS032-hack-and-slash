#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsPixmapItem>
#include <QVector2D>
#include <QPair>
#include <QVector>

#include "Map.h"
#include "Animator.h"

class Camera;

class Character : public QGraphicsPixmapItem{
public:
    Character(Map* world, int health, float speed, int size, int coordI, int coordJ, Animator animator);
    virtual void update(int deltaT);
    int getI();
    int getJ();
    int getSize();
    void setDestination(int i, int j);
    void setTarget(Character* target);
    Character* getTarget();
    void orient();
    void attack();
    void takeDmg(int dmg);

protected:
    Map* world;

    QVector2D worldCoords;
    QVector2D nextCellCoords;
    float movementSpeed;
    int orientation;

    int mapI, mapJ;         // koordinate polja matrice
    int destI, destJ;       // tamo gde treba doci


    int size;               // broj kvadrat
    enum State{
        moving,
        ready,
        attacking,
        casting,
        attacked,
        dead
    };
    State charState;

    Animator animator;

    Character *target = nullptr;
    float attackRange;
    float attackCooldown;
    float attackTimer;

    int health;
    int attackDmg;
};


#endif // CHARACTER_H
