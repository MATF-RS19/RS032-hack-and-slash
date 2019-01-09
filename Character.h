#ifndef CHARACTER_H
#define CHARACTER_H

#include <QGraphicsPixmapItem>
#include <QVector2D>
#include <QPair>
#include <QVector>

#include "Map.h"
#include "Animator.h"
#include "Spell.h"

class Camera;

class Character : public QGraphicsPixmapItem{
public:
    Character(Map* world, int health, float speed, int size, int coordI, int coordJ, Animator animator, QVector<Spell*> spells);
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
    Map* getMap();
    QVector2D getWorldCoords();
    void cast(int i, Character* target);
    void cast(int i, float worldX, float worldY);
    int getMana();
    void drainMana(int amount);

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
    QVector<Spell*> spells;

    float attackRange;
    float attackCooldown;
    float attackTimer;

    int health;
    int maxHealth;
    int mana;
    int maxMana;
    int attackDmg;
};


#endif // CHARACTER_H
